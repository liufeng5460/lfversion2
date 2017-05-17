
#include "mainwindow.h"
#include "status.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Status::init();
    MainWindow w;
    w.show();

    return a.exec();
}






