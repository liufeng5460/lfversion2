#include <QMenu>
#include <QMenuBar>
#include "mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle(tr("集成加密软件"));
    this->setWindowIcon(QIcon(":/image/Icon.jpg"));
    this->setMinimumSize(850,350);


    //create action
    importCertiAction =new QAction(QIcon(":/image/import.jpg"),tr("引入证书"),this);
    importCertiAction->setShortcut(tr("Ctrl+O"));
    importCertiAction->setStatusTip(tr("添加一个证书"));

    newCertiAction =new QAction(QIcon(":/image/newFile"),tr("新建证书"),this);
    newCertiAction->setShortcut(tr("Ctrl+N"));
    newCertiAction->setStatusTip(tr("新建一个证书"));

    newAesKeyAction =new QAction(QIcon(":/image/newFile"),tr("新建Aes密钥"),this);
    newAesKeyAction->setStatusTip(tr("新建Aes密钥"));

    encryAction =new QAction(QIcon(":/image/encrypt"),tr("加密文件"),this);
    encryAction->setStatusTip(tr("打开加密窗口"));

    decryAction =new QAction(QIcon(":/image/decrypt"),tr("解密文件"),this);
    decryAction->setStatusTip(tr("打开解密窗口"));

    fileTransAction=new QAction(QIcon(":/image/filetransition"),tr("文件传输"),this);
    fileTransAction->setStatusTip(tr("文件传输"));


    exitAction =new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));





    // create menus

    QMenu *menu =menuBar()->addMenu(tr("文件"));
    menu->addAction(importCertiAction);
    menu->addAction(newCertiAction);
    menu->addAction(newAesKeyAction);
   // menu->addAction(changePortAction);
    menu->addSeparator();
    menu->addAction(exitAction);

    menu =menuBar()->addMenu(tr("操作"));
    menu->addAction(encryAction);
    menu->addAction(decryAction);
    menu->addAction(fileTransAction);


    //create tool bar
    toolBar =addToolBar("tool");
    toolBar->addAction(newCertiAction);

    //zone02
    //zone02 =addToolBar("Tool");
    toolBar->addAction(encryAction);
    toolBar->addAction(decryAction);
    // toolBar->addAction(digitalSignature);
    //  toolBar->addAction(authentication);
    toolBar->addAction(fileTransAction);

    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //zone02->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    // connect signals
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    util::centerize(this);
    showWidget =new ShowWidgetUI(this);
    setCentralWidget(showWidget);



}

MainWindow::~MainWindow()
{

}
