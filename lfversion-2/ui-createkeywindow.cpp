#include "ui-createkeywindow.h"
#include "myaes.h"
#include "util.h"
#include <QGridLayout>
#include <QMessageBox>
CreateKeyWindow::CreateKeyWindow(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle(tr("新建AES密钥"));
    nameLabel=new QLabel(tr("AES密钥名称："));
    nameEdit=new QLineEdit;
    KeyLengthLabel=new QLabel(tr("AES密钥长度(bytes)："));
    Lenth16=new QRadioButton(tr("16"));
    Lenth32=new QRadioButton(tr("32"));
    submitBtn=new QPushButton(tr("提交"));

    QGridLayout *mainLayout =new QGridLayout(this);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);


    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameEdit,0,1);
    mainLayout->addWidget(KeyLengthLabel,1,0);
    mainLayout->addWidget(Lenth16,2,0);
    mainLayout->addWidget(Lenth32,3,0);
    mainLayout->addWidget(submitBtn,4,1);


    connect(submitBtn,SIGNAL(clicked()),this,SLOT(genAesKey()));
}

void CreateKeyWindow::genAesKey(){
    QString keyname=nameEdit->text();
    if(keyname.isEmpty() ){
        QMessageBox::critical(this,tr("警告"),tr("请先填写AES密钥名字！"));
        return;
    }


    if(util::contains(keyname,"AESkey")){
            QMessageBox::critical(this,tr("警告"),tr("该AES密钥已存在，请换一个名称！"));
            return;
    }

    int length;
    if(Lenth16->isChecked()){
        //qDebug() << "16";
        length=16;
    } else if(Lenth32->isChecked()){
       // qDebug() << "32";
        length=32;
    } else {

    }


    QString keyroot=QCoreApplication::applicationDirPath()+"/Key/AES/"+keyname;
    QString message;
    try{

        MyAES aes;
        aes.GenerateKey(length);//生成16 byte AES秘钥
        aes.SaveKey(keyroot.toStdString().c_str());
        message="已生成密钥！";

        QFile filein(QCoreApplication::applicationDirPath()+"/Key/AESkey");
        if( filein.open(QIODevice::ReadWrite|QIODevice::Append | QIODevice::Text) ){
            QTextStream in(&filein);
            in<<  keyname << "\n";
        } else {
            message=filein.errorString();
        }
        filein.close();

    } catch(Exception e) {
        cout << e.GetWhat() << endl;
    }

    QMessageBox::information(this,tr("提示"),message);
    this->close();
}
