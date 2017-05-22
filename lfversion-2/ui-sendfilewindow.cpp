
#include "ui-sendfilewindow.h"
#include "netaction.h"
#include "util.h"

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
    ipAddressCombo =  new QComboBox;
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
    inputLayout->addWidget(ipAddressCombo,i++,1);

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


    ipAddressCombo->setEditable(true);
//    ipAddressCombo->setText(tr("127.0.0.1"));
    portEdit->setText(tr("5460"));

    // get name list
    util::getContact(nameList,ipList);
    for(QString name: nameList)
    {
        nameCombo->addItem(name);
    }
    updateIpList(0);

    connect(selectFileButton, SIGNAL(clicked(bool)), this,SLOT(selectFile()));
    connect(sendButton,SIGNAL(clicked(bool)),this,SLOT(doSend()));
    connect(nameCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(updateIpList(int)));

}

void SendFileWindow::selectFile()
{
    fileName = QFileDialog::getOpenFileName(this,"选择文件","/home/ydu","All files(*)");
    if(fileName == nullptr) return;
    fileEdit->setText(fileName);
}

void SendFileWindow::doSend()
{
    QString ip = ipAddressCombo->currentText().trimmed();
    int port = portEdit->text().trimmed().toInt();
    bool success = NetAction::sendFile(nameCombo->currentText(),fileEdit->text(),QHostAddress(ip),port);
    if(success)
    {
        util::appendIp(nameCombo->currentText(), ipAddressCombo->currentText());
        util::appendSendFileRecord(nameCombo->currentText(),ip,fileEdit->text());
    }
}

void SendFileWindow::updateIpList(int index)
{
    if(index < ipList.size())
    {
        ipAddressCombo->clear();
        ipAddressCombo->addItem("127.0.0.1");
        QString ips = ipList.at(index);
        QStringList ipListTemp = ips.split(",");
        for(QString ip : ipListTemp)
        {
            ipAddressCombo->addItem(ip);
        }
    }
}
