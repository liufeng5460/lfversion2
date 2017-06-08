
#include "mainwindow.h"
#include "status.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.addLibraryPath("./Lib");

    Status::init();
    MainWindow w;
    w.show();

    return a.exec();
}






