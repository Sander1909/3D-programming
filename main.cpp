#include "mainwindow.h"
#include <QApplication>
#include "iostream"

int main(int argc, char *argv[])
{
    //Forces the usage of desktop OpenGL
    //Attribute must be set before Q(Gui)Application is constructed:
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    int returnValue{0};
    try
    {
        returnValue = a.exec();
    }
    catch (...) // catch-all handler
    {
        std::cout << "We caught an exception of an undetermined type\n";
    }
    return returnValue;
}
