#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "renderwindow.h"
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QTextEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete mRenderWindow;
    delete ui;
}

void MainWindow::init()
{
    //Setting up the OpenGL 4.1 surface:
    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSamples(4);    // Set the number of samples used for multisampling
    format.setOption(QSurfaceFormat::DebugContext); //Should activate OpenGL debug Context used in RenderWindow::startOpenGLDebugger()
    format.setDepthBufferSize(16);      // The example rendering will need a depth buffer.
    qDebug() << "Requesting surface format" << format;

    //Making the renderwindow with this surface - testing if it went well:
    mRenderWindow = new RenderWindow(format, this);
    if (!mRenderWindow->context()) {
        qDebug() << (tr("Failed to create context"));
        //delete mRenderWindow;
        mRenderWindowContainer = new QWidget(this);
        addRenderWindow();
        return;
    }

    connect(mRenderWindow, &RenderWindow::ready, this, &MainWindow::renderWindowReady);
    connect(mRenderWindow, &RenderWindow::error, this, &MainWindow::renderWindowError);

    //Adds the renderwindow to the visual program - inside the
    // RenderWindowContainer that we can see in the form-designer.
    mRenderWindowContainer = QWidget::createWindowContainer(mRenderWindow);
    addRenderWindow();

    mRenderWindowContainer->setFocus(); //sets the keyboard input focus to this window when program starts
}

void MainWindow::renderWindowReady()
{
    //Testing if the context is valid
    QOpenGLContext *context = QOpenGLContext::currentContext();
    Q_ASSERT(context);
}

void MainWindow::renderWindowError(const QString &msg)
{
    //Generic error writing. Could easly be removed and handeled in other ways
    qDebug() << (tr("An error has occurred:\n%1").arg(msg));
}

void MainWindow::addRenderWindow()
{
    ui->renderLayout->addWidget(mRenderWindowContainer);
}

void MainWindow::on_actionWireframe_toggled(bool arg1)
{
    mRenderWindow->setWireframe(arg1);
}
