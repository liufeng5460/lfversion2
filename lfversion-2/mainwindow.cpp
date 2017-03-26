#include <QMenu>
#include <QMenuBar>
#include "mainwindow.h"
#include "util.h"
#include "ui-createcertiwindow.h"
#include "ui-createkeywindow.h"
#include "ui-encryptfilewindow.h"
#include "ui-decryptfilewindow.h"
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
    connect(importCertiAction,SIGNAL(triggered()),this,SLOT(selectCerti()));


    newCertiAction =new QAction(QIcon(":/image/newFile"),tr("新建证书"),this);
    newCertiAction->setShortcut(tr("Ctrl+N"));
    newCertiAction->setStatusTip(tr("新建一个证书"));
    connect(newCertiAction,SIGNAL(triggered()),this,SLOT(createCerti()));


    newAesKeyAction =new QAction(QIcon(":/image/newFile"),tr("新建Aes密钥"),this);
    newAesKeyAction->setStatusTip(tr("新建Aes密钥"));
    connect(newAesKeyAction,SIGNAL(triggered()),this,SLOT(createKey()));

    encryptAction =new QAction(QIcon(":/image/encrypt"),tr("加密文件"),this);
    encryptAction->setStatusTip(tr("打开加密窗口"));
    connect(encryptAction,SIGNAL(triggered()),this,SLOT(encrytFile()));


    decryptAction =new QAction(QIcon(":/image/decrypt"),tr("解密文件"),this);
    decryptAction->setStatusTip(tr("打开解密窗口"));
    connect(decryptAction,SIGNAL(triggered()),this,SLOT(decrytFile()));


    fileTransAction=new QAction(QIcon(":/image/filetransition"),tr("文件传输"),this);
    fileTransAction->setStatusTip(tr("文件传输"));


    exitAction =new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));




    // create menus

    QMenu *menu =menuBar()->addMenu(tr("文件"));
    menu->addAction(importCertiAction);
    menu->addAction(newCertiAction);
    menu->addAction(newAesKeyAction);
   // menu->addAction(changePortAction);
    menu->addSeparator();
    menu->addAction(exitAction);

    menu =menuBar()->addMenu(tr("操作"));
    menu->addAction(encryptAction);
    menu->addAction(decryptAction);
    menu->addAction(fileTransAction);


    //create tool bar
    toolBar =addToolBar("tool");
    toolBar->addAction(newCertiAction);

    //zone02
    //zone02 =addToolBar("Tool");
    toolBar->addAction(encryptAction);
    toolBar->addAction(decryptAction);
    // toolBar->addAction(digitalSignature);
    //  toolBar->addAction(authentication);
    toolBar->addAction(fileTransAction);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //zone02->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);


    util::centerize(this);
    showWidget =new ShowWidgetUI(this);
    setCentralWidget(showWidget);



}

MainWindow::~MainWindow()
{

}


void MainWindow::createCerti(){
    util::windowSetup(new CreateCertiWindow);
}

void MainWindow::selectCerti()
{
    showWidget->addCerti();
}

void MainWindow::createKey()
{
    util::windowSetup(new CreateKeyWindow);
}

void MainWindow::encrytFile()
{
    util::windowSetup(new EncrytFileWindow);
}

void MainWindow::decrytFile()
{
    util::windowSetup(new DecryptFileWindow);
}
