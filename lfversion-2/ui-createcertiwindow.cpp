
#include "ui-createcertiwindow.h"
#include "util.h"
#include "myrsa.h"
#include "status.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStack>
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>
#include <QTextEdit>
#include <QMessageBox>
CreateCertiWindow::CreateCertiWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("新建证书"));

    purposeLabel=new QLabel(tr("用途"));
    mailLabel=new QLabel(tr("邮箱"));
    validFromLabel=new QLabel(tr("生效期"));
    validUtilLabel=new QLabel(tr("失效期"));

    purposeEdit=new QLineEdit;
    mailEdit=new QLineEdit;
    validFromEdit=new QLineEdit;
    validUtilEdit=new QLineEdit;

    submitBtn=new QPushButton(tr("生成"));

    QGridLayout *mainLayout =new QGridLayout(this);
    mainLayout->setMargin(20);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(purposeLabel,0,0);
    mainLayout->addWidget(purposeEdit,0,1);
    mainLayout->addWidget(mailLabel,1,0);
    mainLayout->addWidget(mailEdit,1,1);
    mainLayout->addWidget(validFromLabel,2,0);
    mainLayout->addWidget(validFromEdit,2,1);
    mainLayout->addWidget(validUtilLabel,3,0);
    mainLayout->addWidget(validUtilEdit,3,1);
    mainLayout->addWidget(submitBtn,4,1);


    connect(submitBtn,SIGNAL(clicked()),this,SLOT(genKey()));

}

void CreateCertiWindow::genKey(){

    QString keyname=purposeEdit->text();
     string name=keyname.toStdString();


     if(util::contains(keyname,"mykey")){
             QMessageBox::critical(this,tr("警告"),tr("该RSA密钥已存在，请换一个名称！"));
             return;
     }

     string privFile="Key/RSA/PrivKey_"+name;
     string pubFile="Key/RSA/PubKey_"+name;

    const char *privFilename=privFile.c_str();
    const char *pubFilename=pubFile.c_str();

    pubFileName = QString::fromStdString(pubFile);
    privFileName = QString::fromStdString(privFile);

    MyRSA rsa;
    rsa.GenerateRSAKey(2048, privFilename, pubFilename);

    QString pubkeyInfo= Status::username.toUtf8()
            +";" +purposeEdit->text().toUtf8()
            +";" +mailEdit->text().toUtf8()
            +";" +validFromEdit->text().toUtf8()
            +";" +validUtilEdit->text().toUtf8();
    QString MyKeyinfo=pubkeyInfo+";"+pubFilename+";"+privFilename;

    updateCertiInfo(MyKeyinfo);


    // create certi file
    QFile certiFile(QApplication::applicationDirPath()+"/Key/Certi/"+purposeEdit->text()+".cer") ;
    certiFile.open(QIODevice::ReadWrite|QIODevice::Append|QIODevice::Text);
    QTextStream certiStream(&certiFile);
    certiStream<<pubkeyInfo<<"\n";

    QFile pubkeyFile(QApplication::applicationDirPath()+"/"+pubFile.c_str());
    pubkeyFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream pubkeyStream(&pubkeyFile);
    certiStream<<pubkeyStream.readLine();

    certiFile.close();
    pubkeyFile.close();

}

void CreateCertiWindow::updateCertiInfo(QString MyKeyinfo)
{
    Status::showWidget->addSelfRecords(MyKeyinfo.split(";"));

    QFile mykeyFile(QCoreApplication::applicationDirPath()+"/Key/mykey");
    if( mykeyFile.open(QIODevice::ReadWrite|QIODevice::Append | QIODevice::Text) ){
       QTextStream in01(&mykeyFile);
       in01<<  MyKeyinfo << "\n";
    } else {
       // qDebug() <<  file01.error();
       // qDebug() <<  file01.errorString();
    }
    mykeyFile.close();

    this->close();

}
