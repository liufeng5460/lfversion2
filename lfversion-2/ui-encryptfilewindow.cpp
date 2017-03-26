#include "ui-encryptfilewindow.h"

#include <QVBoxLayout>
#include <QFile>
#include <QApplication>
#include <QTextStream>
EncrytFileWindow::EncrytFileWindow(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle(tr("加密文件"));
    this->setWindowIcon(QIcon(":/image/encrypt"));

    /**** choose Aes Key ****/
   choseKeyLabel=new QLabel(tr("请选择一个AES密钥"));
   chooseKey = new QComboBox();

   /*********read file content*********/
  QFile *file=new QFile(QApplication::applicationDirPath()+"/Key/AESkey");
 // QTextCodec *code = QTextCodec::codecForName("utf8");
  file->open(QIODevice::ReadOnly | QIODevice::Text);
   QTextStream stream(file);
 //  stream.setCodec(code);
   QString line;
   do{
      line =QString(stream.readLine());
       chooseKey->addItem(line);
   } while (!line.isNull());
    file->close();
   /**** choose Aes Key ****/

    /**** Layout01 ****/
    fileInputLabel=new QLabel(tr("请选择需要加密的文本：（txt格式）"));
    showChoseFile=new QLabel;
    choseFileBtn=new QPushButton(tr("选择文件"));
    showOutputFile=new QLabel;
    choseOutputRoot=new QPushButton(tr("更改保存路径"));
    encrptionFileBtn=new QPushButton(tr("加密文件"));

    Layout01=new QGridLayout();

    Layout01->addWidget(chooseKey,0,0);
    Layout01->addWidget(choseKeyLabel,0,1);
    Layout01->addWidget(fileInputLabel,1,0);
    Layout01->addWidget(choseFileBtn,2,1);
    Layout01->addWidget(showChoseFile,3,0);
    Layout01->addWidget(showOutputFile,4,0);
    Layout01->addWidget(choseOutputRoot,4,1);
    Layout01->addWidget(encrptionFileBtn,5,1);



    /**** Layout02 ****/
    typingInputLabel=new QLabel(tr("或者输入您要加密的文本"));
    inputStrArea=new QTextEdit;
    encrptionStrBtn=new QPushButton(tr("加密文本"));

    Layout02=new QGridLayout();
    Layout02->addWidget(typingInputLabel,0,0);
    Layout02->addWidget(inputStrArea,1,0);
    Layout02->addWidget(encrptionStrBtn,1,1);


    /**** Layout03 ****/
    outputLabel=new QLabel(tr("生成的密文："));
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
}

