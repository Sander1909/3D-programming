#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QWheelEvent>

#include <memory>

#include "shader.h"
#include "mainwindow.h"
#include "matrix4x4.h"
#include "triangle.h"
#include "octahedron.h"
#include "texture.h"
#include "vertex.h"
#include "axis.h"
#include "transform.h"

#include "plane.h"
#include <ctime>

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext{0}, mInitialized{false}, mPosition{0.005f}, mRotation{0.1f}, mMainWindow{mainWindow}

{
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    mContext = new QOpenGLContext(this);    //automatically deleted
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = 0;
    }
}

RenderWindow::~RenderWindow()
{
    //    glDeleteVertexArrays( 1, &mBallVAO );
    //    glDeleteBuffers( 1, &vertexBufferObject );

    //should delete all "new" objects - or use unique_ptr / shared_ptr
    //    if (mTextureShaderProgram)
    //        delete mTextureShaderProgram;
    //    if (mColorShaderProgram)
    //        delete mColorShaderProgram;

}

void RenderWindow::init()
{
    srand(time(nullptr));

    //Some general stuff
    if (!mContext->makeCurrent(this)) {
        emit error(tr("makeCurrent() failed"));
        return;
    }

    if (!mInitialized)
        mInitialized = true;

    initializeOpenGLFunctions();
    startOpenGLDebugger();

    //Initialize matrixes
    mMVPmatrix = std::unique_ptr<QMatrix4x4>(new QMatrix4x4);
    mViewMatrix = std::unique_ptr<QMatrix4x4>(new QMatrix4x4);
    mPerspectiveMatrix = std::unique_ptr<QMatrix4x4>(new QMatrix4x4);

    //perspectiv matrixAA
    setPerspectiveMatrix();

    //view matrix
    mViewMatrix->setToIdentity();   //identity();
    mViewMatrix->translate(0.f, -3.f, -10.f);
    mViewMatrix->lookAt(QVector3D(0.f, 10.f, 15.f), QVector3D(0.f, 0.f, 0.f), QVector3D(0.f, 1.f, 0.f));

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);    //enables depth sorting - must use GL_DEPTH_BUFFER_BIT in glClear
    glEnable(GL_CULL_FACE);     //draws only front side of models
    glClearColor(0.2f, 0.2f, 0.2f,1.0f);    //color used in glClear GL_COLOR_BUFFER_BIT

    //Compile shaders:

    std::string texture_vert = gsl::shaderFilePath + "textureshader.vert";
    std::string texture_frag = gsl::shaderFilePath + "textureshader.frag";
    std::string color_vert = gsl::shaderFilePath + "plainvertex.vert";
    std::string color_frag = gsl::shaderFilePath + "plainfragment.frag";

    mTextureShaderProgram = std::unique_ptr<Shader>(new Shader(texture_vert.c_str(), texture_frag.c_str()));
    mColorShaderProgram = std::unique_ptr<Shader>(new Shader(color_vert.c_str(), color_frag.c_str()));

    //make textures

    std::string texture_hund = gsl::assetFilePath + "hund.bmp";
    std::string texture_uvtemplate = gsl::assetFilePath + "uvtemplate.bmp";

    mTexture1 = std::unique_ptr<Texture>(new Texture(texture_hund.c_str()));
    mTexture2 = std::unique_ptr<Texture>(new Texture(texture_uvtemplate.c_str()));

    //Make a plane (floor)
    mPlane1 = std::unique_ptr<SceneObject>(new Plane);
    mPlane1->getTransform()->setPosition(0.f, 0.f, 0.f);
    mPlane1->getTransform()->setRotation(90.f, 0.f, 0.f);
    mPlane1->getTransform()->setScale(14.f, 14.f, 1.f);

    plainShaderAttribs();
    glBindVertexArray(0);

    //Wall 1
    mPlane2 = std::unique_ptr<SceneObject>(new Plane);
    mPlane2->getTransform()->setPosition(7.f, 2.5f, 0.f);
    mPlane2->getTransform()->setRotation(0.f, 90.f, 0.f);
    mPlane2->getTransform()->setScale(14.f, 5.f, 1.f);

    plainShaderAttribs();
    glBindVertexArray(0);

    //Wall 2
    mPlane3 = std::unique_ptr<SceneObject>(new Plane);
    mPlane3->getTransform()->setPosition(0.f, 2.5f, 7.f);
    mPlane3->getTransform()->setRotation(0.f, 0.f, 0.f);
    mPlane3->getTransform()->setScale(14.f, 5.f, 1.f);

    plainShaderAttribs();
    glBindVertexArray(0);

    //Wall 3
    mPlane4 = std::unique_ptr<SceneObject>(new Plane);
    mPlane4->getTransform()->setPosition(-7.f, 2.5f, 0.f);
    mPlane4->getTransform()->setRotation(0.f, -90.f, 0.f);
    mPlane4->getTransform()->setScale(14.f, 5.f, 1.f);

    plainShaderAttribs();
    glBindVertexArray(0);

    //Wall 4
    mPlane5 = std::unique_ptr<SceneObject>(new Plane);
    mPlane5->getTransform()->setPosition(0.f, 2.5f, -7.f);
    mPlane5->getTransform()->setRotation(0.f, 180.f, 0.f);
    mPlane5->getTransform()->setScale(14.f, 5.f, 1.f);

    plainShaderAttribs();
    glBindVertexArray(0);

    //Octahedron 1
    mOctahedron1 = std::unique_ptr<SceneObject>(new Octahedron(1));
    mOctahedron1->getTransform()->setPosition(5.f, 1.f, -5.f);
    mOctahedron1->setMass(5000.f);
    mOctahedron1->setForce(Vec3{rand()%15,0.f,rand()%15});

    plainShaderAttribs();
    glBindVertexArray(0);

    //Octahedron 2
    mOctahedron2 = std::unique_ptr<SceneObject>(new Octahedron(1));
    mOctahedron2->getTransform()->setPosition(-5.f, 1.f, 0.f);
    mOctahedron2->setMass(5000.f);
    mOctahedron2->setForce(Vec3{rand()%15, 0.f, rand()%15});

    plainShaderAttribs();
    glBindVertexArray(0);

    //Make Axis
    mAxis = std::unique_ptr<SceneObject>(new Axis);
    plainShaderAttribs();
    glBindVertexArray( 0 );

    emit ready();   //tell the mainWindow that init is finished
}

//Background--
GLfloat red;
GLfloat green;
GLfloat blue;
//------------

float addForceTimer{0.f};

void RenderWindow::render(float deltaTime)
{
    //--------------------------------disco--------------------------------//
    red += 0.001f;
    green += 0.002f;
    blue += 0.003f;
    glClearColor(fabs(sin(red)), fabs(sin(green)), fabs(sin(blue)), 1.0f);
    if(red > M_PI * 2)
        red = 0.f;
    if(green > M_PI * 2)
        green = 0.f;
    if(blue > M_PI * 2)
        blue = 0.f;
    //---------------------------------------------------------------------//

    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)
    initializeOpenGLFunctions();

    if (mWireframe)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );    //turn on wireframe mode
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );    //turn off wireframe mode
        glDisable(GL_CULL_FACE);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mvpMatrix;   //for use with plainShader
    glUseProgram(mColorShaderProgram->getProgram());

    //Floor:
    glBindVertexArray(mPlane1->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mPlane1->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mPlane1->mNumberOfVertices);
    checkForGLerrors();

    //Wall 1:
    glBindVertexArray(mPlane2->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mPlane2->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mPlane2->mNumberOfVertices);
    checkForGLerrors();

    //Wall 2:
    glBindVertexArray(mPlane3->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mPlane3->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_LINES, 0, mPlane3->mNumberOfVertices);
    checkForGLerrors();

    //Wall 3:
    glBindVertexArray(mPlane4->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mPlane4->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mPlane4->mNumberOfVertices);
    checkForGLerrors();

    //Wall 4:
    glBindVertexArray(mPlane5->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mPlane5->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mPlane5->mNumberOfVertices);
    checkForGLerrors();

    //Octahedron 1:
    glBindVertexArray(mOctahedron1->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mOctahedron1->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mOctahedron1->mNumberOfVertices);
    checkForGLerrors();

    mOctahedron1->applyForces(deltaTime);
    mOctahedron1->wallCollision();

    //Octahedron 2:
    glBindVertexArray(mOctahedron2->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mOctahedron2->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mOctahedron2->mNumberOfVertices);
    checkForGLerrors();

    mOctahedron2->applyForces(deltaTime);
    mOctahedron2->wallCollision();

    addForceTimer += deltaTime;
    if(addForceTimer > 3000.f) //add new force every 3rd sec
    {
        mOctahedron1->setForce(Vec3{rand()%10,0.f,rand()%10});
        mOctahedron2->setForce(Vec3{rand()%10,0.f,rand()%10});
        addForceTimer = 0.f;
    }

    //Oct1 and Oct2 collision
    float distanceToBall = Vec3(mOctahedron1->getTransform()->getPosition() - mOctahedron2->getTransform()->getPosition()).length();
    if(distanceToBall <= 2.f)
    {
        mOctahedron2->setForce(mOctahedron2->getTransform()->getPosition()-mOctahedron1->getTransform()->getPosition());
        mOctahedron1->setForce(mOctahedron1->getForce() - mOctahedron2->getForce());
        mOctahedron2->getTransform()->setPosition(Vec3(mOctahedron2->getTransform()->getPosition() +
                                                      (mOctahedron2->getForce() * (1.1f-(mOctahedron2->getForce().length()/2)))));
        mOctahedron1->getTransform()->setPosition(Vec3(mOctahedron1->getTransform()->getPosition() +
                                                      ((mOctahedron2->getForce() * -1.f) * (1.1f-(mOctahedron2->getForce().length()/2)))));
    }

    //Draw axis
    glBindVertexArray(mAxis->mVAO);
    mvpMatrix = *mPerspectiveMatrix * *mViewMatrix * *(mAxis->getModelMatrix());
    glUniformMatrix4fv( mMVPUniform, 1, GL_FALSE, mvpMatrix.constData());
    glDrawArrays(GL_LINES, 0, mAxis->mNumberOfVertices);
    checkForGLerrors();

    mContext->swapBuffers(this);
}

void RenderWindow::plainShaderAttribs()
{
    // 1rst attribute buffer : vertices
    glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                8 * sizeof( GLfloat ),  // stride
                (GLvoid*)0            // array buffer offset
                );
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                8 * sizeof( GLfloat ),            // stride
                (GLvoid*)( 3 * sizeof( GLfloat ) )   // array buffer offset
                );
    glEnableVertexAttribArray(1);
    // 3rd attribute buffer : uvs
    glVertexAttribPointer(
                2,                                // attribute. No particular reason for 2, but must match the layout in the shader.
                2,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                8 * sizeof( GLfloat ),            // stride
                (GLvoid*)( 6 * sizeof( GLfloat ) )   // array buffer offset
                );
    glEnableVertexAttribArray(2);

    //enable the matrixUniform
    mMVPUniform = glGetUniformLocation( mColorShaderProgram->getProgram(), "matrix" );
}

void RenderWindow::textureShaderAttribs()
{
    // 1rst attribute buffer : vertices
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), (GLvoid*)0 );
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), (GLvoid*)( 3 * sizeof( GLfloat )));
    glEnableVertexAttribArray(1);

    // 3rd attribute buffer : uvs
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), (GLvoid*)( 6 * sizeof( GLfloat )));
    glEnableVertexAttribArray(2);

    //enable the matrixUniform
    mModelMatrixUniform = glGetUniformLocation( mTextureShaderProgram->getProgram(), "mMatrix" );
    mViewMatrixUniform = glGetUniformLocation( mTextureShaderProgram->getProgram(), "vMatrix" );
    mPerspectiveMatrixUniform = glGetUniformLocation( mTextureShaderProgram->getProgram(), "pMatrix" );

    mTextureUniform1 = glGetUniformLocation(mTextureShaderProgram->getProgram(), "textureSampler1");
    mTextureUniform2 = glGetUniformLocation(mTextureShaderProgram->getProgram(), "textureSampler2");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture1->id());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTexture2->id());
}


void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        qDebug() << "Can this system run QOpenGLDebugLogger? :" << format.testOption(QSurfaceFormat::DebugContext);

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);  //will be deleted automatically
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                qDebug() << "Started OpenGL debug logger!";
            //Try to silence some messages that is not critical
            mOpenGLDebugLogger->disableMessages(QOpenGLDebugMessage::AnySource, QOpenGLDebugMessage::AnyType, QOpenGLDebugMessage::NotificationSeverity);
        }
    }
}

void RenderWindow::setWireframe(bool wireframe)
{
    mWireframe = wireframe;
}

void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << message;
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            qDebug() << "glGetError returns " << err;
        }
    }
}

//This function is called from Qt when window is exposed / shown
void RenderWindow::exposeEvent(QExposeEvent *)
{
    if (!mInitialized)
        init();

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    setPerspectiveMatrix();

    if (isExposed())
    {
        mTimer.start(16, this);
        mTimeStart.start();
    }
}

void RenderWindow::setPerspectiveMatrix()
{
    GLfloat nearPlane = 0.1f;
    GLfloat farPlane = 1000.f;
    mPerspectiveMatrix->setToIdentity();
    //mOrtho = true;
    if (mOrtho)
    {
        float scale{0.005f};
        mPerspectiveMatrix->ortho(-width()*scale/2, width()*scale/2, -height()*scale/2 , height()*scale/2, nearPlane, farPlane);
    }
    else
    {
        GLfloat aspectRatio = static_cast<float>(width())/static_cast<float>(height() ?height() : 1); //height never == 0
        GLfloat fieldOfView{45.f};
        mPerspectiveMatrix->perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
    }
}

void RenderWindow::mouseMoveEvent(QMouseEvent *event)
{
    //using mouseXYlast as deltaXY so we don't need extra variables
    mouseXlast = event->pos().x() - mouseXlast;
    mouseYlast = event->pos().y() - mouseYlast;

    //if delta is to big the movement will be jerky
    //Happens if mouse is moved much between presses.
    if (mouseXlast > 40 || mouseYlast > 40 || mouseXlast < -40 || mouseYlast < -40)
    {
        mouseXlast = 0;
        mouseYlast = 0;
    }

    // Rotate camera
    float cameraSpeed{0.05f};

    mViewMatrix->rotate(mouseXlast*cameraSpeed, 0.f, 1.f, 0.f);
    mViewMatrix->rotate(mouseYlast*cameraSpeed, 1.f, 0.f, 0.f);

    //    mCurrentCamera->mTransform->rotate(0.0f, -cameraRotationSpeed*mouseXlast, 0.0f);
    //    mCurrentCamera->mTransform->rotate(-cameraRotationSpeed*mouseYlast, 0.0f, 0.0f);

    mouseXlast = event->pos().x();
    mouseYlast = event->pos().y();
}

void RenderWindow::wheelEvent(QWheelEvent* event)
{
    //http://doc.qt.io/qt-4.8/qwheelevent.html
    int numDegrees = event->delta() / 8;
    float numSteps = numDegrees / 15;

    if (event->orientation() == Qt::Horizontal) {
        mViewMatrix->translate(numSteps, 0.0, 0.0);
    } else {
        mViewMatrix->translate(0.0, 0.0, numSteps);
    }
    event->accept();
}

void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        mMainWindow->statusBar()->showMessage(" AAAA");
    }
    if(event->key() == Qt::Key_S)
    {
        mMainWindow->statusBar()->showMessage(" SSSS");
    }
    if(event->key() == Qt::Key_Escape)
    {
        mMainWindow->close();
    }
}

void RenderWindow::timerEvent(QTimerEvent *)
{
    int msSinceLastFrame = mTimeStart.restart();    //restart() returns ms since last restart.

    render(msSinceLastFrame);

    //The rest here is just to show the frame rate:
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)    //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 60) //once pr 60 frames =  update the message once pr second
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" FrameDraw: " + QString::number(msSinceLastFrame) + " ms");
            frameCount = 0;     //reset to show a new message in 60 frames
        }
    }
}



