
#include "ui-sendfilewindow.h"
#include "netaction.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QHostAddress>
SendFileWindow::SendFileWindow(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle(tr("发送文件"));

    nameLabel = new QLabel(tr("姓名: "));
    ipAddressLabel = new QLabel(tr("IP地址: "));
    portLabel = new QLabel(tr("端口号: "));
    fileLabel = new QLabel(tr("文件名: "));

    nameCombo = new QComboBox;
    ipAddressEdit =  new QLineEdit;
    portEdit = new QLineEdit;
    fileEdit = new QLineEdit;

    selectFileButton = new QPushButton(tr("选择文件"));
    sendButton = new QPushButton(tr("发送"));
    testButton =  new QPushButton(tr("测试"));

    QGridLayout* inputLayout = new QGridLayout;
    inputLayout->setMargin(10);
    inputLayout->setSpacing(10);
    int i=0;
    inputLayout->addWidget(nameLabel,i,0);
    inputLayout->addWidget(nameCombo,i++,1);

    inputLayout->addWidget(ipAddressLabel,i,0);
    inputLayout->addWidget(ipAddressEdit,i++,1);

    inputLayout->addWidget(portLabel,i,0);
    inputLayout->addWidget(portEdit,i++,1);

    inputLayout->addWidget(fileLabel,i,0);
    inputLayout->addWidget(fileEdit,i,1);
    inputLayout->addWidget(selectFileButton,i++,2);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setSpacing(20);
    buttonLayout->setMargin(20);
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

