#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QBasicTimer>
#include <QTime>

#include <memory>

//#include <constants.h>

class QOpenGLContext;
class Shader;
class MainWindow;
class Triangle;
class Octahedron;
class SceneObject;
class Texture;
class Matrix4x4;
class QMatrix4x4;
class BezierCurve;
class Surface3D;
class AmbientLight;
class Vec3;
class Light;

class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow();
    QOpenGLContext *context() { return mContext; }
    void exposeEvent(QExposeEvent *) override;

    void setWireframe(bool wireframe);

    void disco();

    void compileShadersAndTextures();

    void initializeMatrices();

    AmbientLight* getLight() const;

signals:
    void ready();
    void error(const QString &msg);

private slots:
    void render(float deltaTime);

private:
    void init();

    void startOpenGLDebugger();

    QOpenGLContext *mContext;
    bool mInitialized;
    std::unique_ptr<Shader> mTextureShaderProgram;
    std::unique_ptr<Shader> mColorShaderProgram;

    GLint mModelMatrixUniform;
    GLint mViewMatrixUniform;
    GLint mPerspectiveMatrixUniform;

    GLint mMVPUniform;

    //Color and lighting-------------------------
    AmbientLight *mAmbientLight;

    Light *mLight;

    GLint mAmbientMVPUniform;
    GLint mAmbientColorUniform;
    GLint mAmbientLightPowerUniform;

    GLint mPhongMVPUniform;

    GLint mPhongModelMatrixUniform;
    GLint mPhongViewMatrixUniform;
    GLint mPhongProjectionMatrixUniform;

    GLint mPhongAmbientColorUniform;
    GLint mPhongLightPositionUniform;
    GLint mPhongCameraPositionUniform;

    std::unique_ptr<Shader> mAmbientColorProgram;
    std::unique_ptr<Shader> mPhongShaderProgram;
    //-------------------------------------------

    //Objects in scene-----------------------------
    std::unique_ptr<SceneObject> mTriangle1;

    std::unique_ptr<SceneObject> mPlane1; //Floor
    std::unique_ptr<SceneObject> mPlane2; //Wall 1
    std::unique_ptr<SceneObject> mPlane3; //Wall 2
    std::unique_ptr<SceneObject> mPlane4; //Wall 3
    std::unique_ptr<SceneObject> mPlane5; //Wall 4

    SceneObject* mOctahedron1;
    SceneObject* mOctahedron2;

    std::unique_ptr<SceneObject> mAxis;

    SceneObject* mBezierCurve;
    SceneObject* mSurface;
    //---------------------------------------------

    QBasicTimer mTimer;     //timer that drives the gameloop
    QTime mTimeStart;       //time variable that reads the actual FPS

    MainWindow *mMainWindow;

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};

    std::unique_ptr<Texture> mTexture1;
    GLuint mTextureUniform1;

    std::unique_ptr<Texture> mTexture2;
    GLuint mTextureUniform2;

    std::unique_ptr<QMatrix4x4> mViewMatrix;
    std::unique_ptr<QMatrix4x4> mPerspectiveMatrix;
    std::unique_ptr<QMatrix4x4> mMVPmatrix;

    bool mOrtho{false};
    bool mWireframe{false};
    int mouseXlast{0};
    int mouseYlast{0};

    int renderLoop{0};

    void checkForGLerrors();

    void setPerspectiveMatrix();

    void plainShaderAttribs();

    void phongShaderAttribs();

    void textureShaderAttribs();

    //Background--
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    //------------

protected:
    //    void mousePressEvent(QMouseEvent *event) override{}
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    //    void keyReleaseEvent(QKeyEvent *event) override{}
    void wheelEvent(QWheelEvent *event) override;

    void timerEvent(QTimerEvent *) override;    
};

#endif // RENDERWINDOW_H
