#include <QtGui/QApplication>
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    LoginWindow lw;
//    if(!lw.checkLogin())
//    {
//        qApp->exit();
//    }

    MainWindow w;
    w.show();

    return a.exec();
}
