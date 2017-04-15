#include "ui-decryptfilewindow.h"
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
DecryptFileWindow::DecryptFileWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("解密文件"));
    this->setWindowIcon(QIcon(":/image/decrypt"));

    /**** choose Aes Key ****/
   chooseKeyLabel=new QLabel(tr("请选择一个AES密钥"));
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
    showchooseFile=new QLabel;
    chooseFileBtn=new QPushButton(tr("选择文件"));
    showOutputFile=new QLabel;
    chooseOutputRoot=new QPushButton(tr("更改保存路径"));
    decryptFileBtn=new QPushButton(tr("解密文件"));

    Layout01=new QGridLayout();
    Layout01->addWidget(chooseKeyLabel,0,1);
    Layout01->addWidget(chooseKey,0,0);
    Layout01->addWidget(fileInputLabel,1,0);
    Layout01->addWidget(chooseFileBtn,1,1);
    Layout01->addWidget(showchooseFile,2,0);
    Layout01->addWidget(showOutputFile,3,0);
    Layout01->addWidget(chooseOutputRoot,3,1);
    Layout01->addWidget(decryptFileBtn,4,1);


    /**** Layout02 ****/
    typingInputLabel=new QLabel(tr("或者输入您要解密的文本"));
    inputStrArea=new QTextEdit;
    decryptStrBtn=new QPushButton(tr("解密文本"));

    Layout02=new QGridLayout();
    Layout02->addWidget(typingInputLabel,0,0);
    Layout02->addWidget(inputStrArea,1,0);
    Layout02->addWidget(decryptStrBtn,1,1);


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


    QString keyName = chooseKey->currentText();
    QString keyFileName = QApplication::applicationDirPath()+"/Key/AES/"+keyName;
    aes.LoadKey(keyFileName.toStdString().c_str());
    aes.getKey();

     connect(chooseFileBtn,SIGNAL(clicked()),this,SLOT(chooseFile()));
   // connect(chooseOutputRoot,SIGNAL(clicked()),this,SLOT(changeRoot()));
     connect(decryptFileBtn,SIGNAL(clicked()),this,SLOT(decryptFile()));
     connect(decryptStrBtn,SIGNAL(clicked()),this,SLOT(decryptStr()));
//    connect(saveToLocal,SIGNAL(clicked()),this,SLOT(saveToLocalFun()));
}

void DecryptFileWindow::decryptStr()
{
    QString cipherText  = inputStrArea->toPlainText();
    string plainText = aes.Decrypt(cipherText.toStdString());
    outputArea->setPlainText(QString(plainText.c_str()));

}
void DecryptFileWindow::chooseFile()
{
     QString cipherFileName = QFileDialog::getOpenFileName(this,"选择文件",QApplication::applicationDirPath(),"All files(*)");
     if(cipherFileName.isEmpty()) return;
    showchooseFile->setText(cipherFileName);
     /*
     QFile cipherFile(cipherFileName);
     cipherFile.open(QIODevice::ReadOnly);
     string plainText =  aes.Decrypt(cipherFile.readAll().toStdString());
     inputStrArea->setPlainText(QString(plainText.c_str()));
     */
}

void DecryptFileWindow::decryptFile()
{
    QString cipherFileName = QFileDialog::getOpenFileName(this,"选择文件",QApplication::applicationDirPath(),"All files(*)");
    if(cipherFileName.isEmpty()) return;
    QString plainFileName = QApplication::applicationDirPath()+"/Tmp/plain";
    aes.DecryptFile(cipherFileName.toStdString(),plainFileName.toStdString());
}
