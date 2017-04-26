#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include "mainwindow.h"
#include "util.h"
#include "status.h"
#include "ui-createcertiwindow.h"
#include "ui-createkeywindow.h"
#include "ui-encryptfilewindow.h"
#include "ui-decryptfilewindow.h"
#include "ui-sendfilewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    if(!Status::username.isEmpty())
    {
        this->setWindowTitle(Status::appName+"--当前用户: "+Status::username);
    }
    else
    {
        this->setWindowTitle(Status::appName);
    }
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
    connect(fileTransAction, SIGNAL(triggered()),this,SLOT(sendFile()));


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


    menu = menuBar()->addMenu(tr("Setup"));

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
    Status::showWidget = showWidget;
    Status::mainWindow = this;

   // updateStatusBar("0");


}

MainWindow::~MainWindow()
{

}

void MainWindow::updateStatusBar(QString port)
{
    QString portInfo = tr("正在监听端口: ")+port;
    if(portInfoLabel == nullptr){
        portInfoLabel = new QLabel(portInfo);
        statusBar()->addWidget(portInfoLabel);
    }else{
        statusBar()->removeWidget(portInfoLabel);
        delete portInfoLabel;
        portInfoLabel = new QLabel(portInfo);
        statusBar()->addWidget(portInfoLabel);
        statusBar()->show();
    }
}

void MainWindow::createCerti(){
    util::dialogSetup(new CreateCertiWindow);
}

void MainWindow::selectCerti()
{
    showWidget->addCerti();
}

void MainWindow::createKey()
{
    util::dialogSetup(new CreateKeyWindow);
}

void MainWindow::encrytFile()
{
    util::dialogSetup(new EncryptFileWindow);
}

void MainWindow::decrytFile()
{
    util::dialogSetup(new DecryptFileWindow);
}

void MainWindow::sendFile()
{
    util::dialogSetup(new SendFileWindow);
}
