
#include "ui-createcertiwindow.h"
#include "util.h"
#include "mylwe.h"
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

    QString purpose=purposeEdit->text();
     if(util::contains(purpose,"mykey")){
             QMessageBox::critical(this,tr("警告"),tr("该用途已存在，请更换！"));
             return;
     }

     QString skFileName="my_"+purpose+".sk";
     QString pkFileName="my_"+purpose+".pk";

    //MyRSA rsa;
    //rsa.GenerateRSAKey(2048, privFilename, pubFilename);
    MyLWE lwe;
    lwe.generateKey();
    lwe.save(pkFileName,skFileName);

    QString pubkeyInfo= purposeEdit->text().toUtf8()
            +";" +mailEdit->text().toUtf8()
            +";" +validFromEdit->text().toUtf8()
            +";" +validUtilEdit->text().toUtf8();
    QString MyKeyinfo=pubkeyInfo+";"+pkFileName+";"+skFileName;

    updateCertiInfo(MyKeyinfo);


    // create certi file starts!
    QFile certiFile(Status::certiDir+"my_"+purposeEdit->text()+".cer") ;
    certiFile.open(QIODevice::ReadWrite|QIODevice::Append|QIODevice::Text);
    QTextStream certiStream(&certiFile);
    certiStream<<Status::username+";"+pubkeyInfo<<"\n";
    for(int i=0; i<LWE_M; i++)
    {
        certiStream<<lwe.pk1[i]<<" "<<lwe.pk2[i]<<"\n";
    }
    certiFile.close();
    // create certi file end!

}

void CreateCertiWindow::updateCertiInfo(QString MyKeyinfo)
{
    Status::showWidget->addSelfRecords(MyKeyinfo.split(";"));

    QFile mykeyFile(Status::workingDir+"Key/mykey");
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
