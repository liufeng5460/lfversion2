#include "mainwindow.h"
#include "netaction.h"
#include "status.h"
#include "mybliss.h"
#include "mylwe.h"


//#include "netserver.h"
#include <QApplication>
#include <QDir>
#include <iostream>
#include <QDebug>
#include <cstdint>
#include <LWEEnc.h>
//#include <BlissSig.h>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Status::init();
    MainWindow w;
    w.show();


    return a.exec();
}






