#include "ui-encryptfilewindow.h"
#include "status.h"

#include <QVBoxLayout>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <string>
#include <QFileDialog>
using namespace std;
EncryptFileWindow::EncryptFileWindow(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle(tr("加密文件"));
    this->setWindowIcon(QIcon(":/image/encrypt"));

    /**** choose Aes Key ****/
   chooseKeyLabel=new QLabel(tr("请选择一个AES密钥"));
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
      if(line.isNull()) break;
       chooseKey->addItem(line);
   } while (!line.isNull());
    file->close();
   /**** choose Aes Key ****/

    /**** Layout01 ****/
    fileInputLabel=new QLabel(tr("请选择需要加密的文本：（txt格式）"));
    showChooseFile=new QLabel;
    chooseFileBtn=new QPushButton(tr("选择文件"));
    showOutputFile=new QLabel;
    chooseOutputRoot=new QPushButton(tr("更改保存路径"));
    encryptFileBtn=new QPushButton(tr("加密文件"));

    Layout01=new QGridLayout();

    Layout01->addWidget(chooseKey,0,0);
    Layout01->addWidget(chooseKeyLabel,0,1);
    Layout01->addWidget(fileInputLabel,1,0);
    Layout01->addWidget(chooseFileBtn,2,1);
    Layout01->addWidget(showChooseFile,3,0);
    Layout01->addWidget(showOutputFile,4,0);
    Layout01->addWidget(chooseOutputRoot,4,1);
    Layout01->addWidget(encryptFileBtn,5,1);



    /**** Layout02 ****/
    typingInputLabel=new QLabel(tr("或者输入您要加密的文本"));
    inputStrArea=new QTextEdit;
    encryptionStrBtn=new QPushButton(tr("加密文本"));

    Layout02=new QGridLayout();
    Layout02->addWidget(typingInputLabel,0,0);
    Layout02->addWidget(inputStrArea,1,0);
    Layout02->addWidget(encryptionStrBtn,1,1);


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




    QString keyName = chooseKey->currentText();
    QString keyFileName = QApplication::applicationDirPath()+"/Key/AES/"+keyName;
    aes.LoadKey(keyFileName.toStdString().c_str());
    aes.getKey();

    connect(encryptionStrBtn,SIGNAL(clicked(bool)),this,SLOT(encryptStr()));
    connect(saveToLocal,SIGNAL(clicked(bool)),this,SLOT(saveCipher()));
    connect(encryptFileBtn,SIGNAL(clicked(bool)),this,SLOT(encryptFile()));
}

void EncryptFileWindow::encryptStr()
{
    QString str  = inputStrArea->toPlainText();
    Status::cipherText = aes.Encrypt(str.toStdString());
    outputArea->setPlainText(QString(Status::cipherText.c_str()));
}

void EncryptFileWindow::saveCipher()
{
    QFile outputFile(QApplication::applicationDirPath()+"/Tmp/cipher");
    outputFile.open(QIODevice::WriteOnly);
    outputFile.write(Status::cipherText.data(),Status::cipherText.length());
}

void EncryptFileWindow::encryptFile()
{
    QString plainFileName = QFileDialog::getOpenFileName(this,"选择文件",QApplication::applicationDirPath(),"All files(*)");
    if(plainFileName.isEmpty()) return;
    QString cipherFileName = QApplication::applicationDirPath()+"/Tmp/cipher";
    aes.EncryptFile(plainFileName.toStdString(),cipherFileName.toStdString());
}
