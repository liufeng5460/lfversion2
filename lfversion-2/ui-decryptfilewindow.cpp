#include "ui-decryptfilewindow.h"
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>
#include <QCoreApplication>
#include <QFile>
DecryptFileWindow::DecryptFileWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("解密文件"));
    this->setWindowIcon(QIcon(":/image/decrypt"));

    /**** choose Aes Key ****/
   choseKeyLabel=new QLabel(tr("请选择一个AES密钥"));
   chooseKey = new QComboBox();

   /*********read file content*********/
   QFile *file=new QFile(QCoreApplication::applicationDirPath()+"/Key/AESkey");
   QTextCodec *code = QTextCodec::codecForName("utf8");
   file->open(QIODevice::ReadOnly | QIODevice::Text);
   QTextStream stream(file);
   stream.setCodec(code);
   QString line;
   do{
      line =QString(stream.readLine());
       chooseKey->addItem(line);
   } while (!line.isNull());
   file->close();
   /**** choose Aes Key ****/

    /**** Layout01 ****/
    fileInputLabel=new QLabel(tr("请选择需要解密的文本：（txt格式）"));
    showChoseFile=new QLabel;
    choseFileBtn=new QPushButton(tr("选择文件"));
    showOutputFile=new QLabel;
    choseOutputRoot=new QPushButton(tr("更改保存路径"));
    decrptionFileBtn=new QPushButton(tr("解密文件"));

    Layout01=new QGridLayout();
    Layout01->addWidget(choseKeyLabel,0,1);
    Layout01->addWidget(chooseKey,0,0);
    Layout01->addWidget(fileInputLabel,1,0);
    Layout01->addWidget(choseFileBtn,1,1);
    Layout01->addWidget(showChoseFile,2,0);
    Layout01->addWidget(showOutputFile,3,0);
    Layout01->addWidget(choseOutputRoot,3,1);
    Layout01->addWidget(decrptionFileBtn,4,1);


    /**** Layout02 ****/
    typingInputLabel=new QLabel(tr("或者输入您要解密的文本"));
    inputStrArea=new QTextEdit;
    decrptionStrBtn=new QPushButton(tr("解密文本"));

    Layout02=new QGridLayout();
    Layout02->addWidget(typingInputLabel,0,0);
    Layout02->addWidget(inputStrArea,1,0);
    Layout02->addWidget(decrptionStrBtn,1,1);


    /**** Layout03 ****/
    outputLabel=new QLabel(tr("生成的明文："));
    outputArea=new QTextEdit;
    saveToLocal=new QPushButton(tr("保存至本地"));

    Layout03=new QGridLayout();
    Layout03->addWidget(outputLabel,0,0);
    Layout03->addWidget(outputArea,1,0);
    Layout03->addWidget(saveToLocal,1,1);

    /*************************************/
    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->setMargin(10);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(Layout01);
    mainLayout->addLayout(Layout02);
    mainLayout->addLayout(Layout03);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    connect(choseFileBtn,SIGNAL(clicked()),this,SLOT(choseFile()));
    connect(choseOutputRoot,SIGNAL(clicked()),this,SLOT(changeRoot()));
    connect(decrptionFileBtn,SIGNAL(clicked()),this,SLOT(doDecryptionFile()));
    connect(decrptionStrBtn,SIGNAL(clicked()),this,SLOT(doDecryptionString()));
//    connect(saveToLocal,SIGNAL(clicked()),this,SLOT(saveToLocalFun()));
}

