
#include "ui-sendfilewindow.h"
#include "netaction.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QHostAddress>
SendFileWindow::SendFileWindow(QWidget *parent) : QWidget(parent)
{

    setWindowTitle(tr("发送文件"));
    ipAddressLabel = new QLabel(tr("IP地址: "));
    portLabel = new QLabel(tr("端口号: "));
    fileLabel = new QLabel(tr("文件名: "));

    ipAddressEdit =  new QLineEdit;
    portEdit = new QLineEdit;
    fileEdit = new QLineEdit;

    selectFileButton = new QPushButton(tr("选择文件"));
    sendButton = new QPushButton(tr("发送"));
    testButton =  new QPushButton(tr("测试"));

    QGridLayout* inputLayout = new QGridLayout;
    inputLayout->setMargin(10);
    inputLayout->setSpacing(10);

    inputLayout->addWidget(ipAddressLabel,0,0);
    inputLayout->addWidget(ipAddressEdit,0,1);
    inputLayout->addWidget(portLabel,1,0);
    inputLayout->addWidget(portEdit,1,1);
    inputLayout->addWidget(fileLabel,2,0);
    inputLayout->addWidget(fileEdit,2,1);
    inputLayout->addWidget(selectFileButton,2,2);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setSpacing(20);
    buttonLayout->setMargin(10);
    buttonLayout->addWidget(testButton);
    buttonLayout->addWidget(sendButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);

    connect(selectFileButton, SIGNAL(clicked(bool)), this,SLOT(selectFile()));
    connect(sendButton,SIGNAL(clicked(bool)),this,SLOT(doSend()));
    ipAddressEdit->setText(tr("127.0.0.1"));
    portEdit->setText(tr("5460"));
}

void SendFileWindow::selectFile()
{
    fileName = QFileDialog::getOpenFileName(this,"选择文件","/home/ydu","All files(*)");
    if(fileName == nullptr) return;
    fileEdit->setText(fileName);
}

void SendFileWindow::doSend()
{
    QString ip = ipAddressEdit->text().trimmed();
    int port = portEdit->text().trimmed().toInt();
    NetAction::sendFile(fileEdit->text(),QHostAddress(ip),port);
}

