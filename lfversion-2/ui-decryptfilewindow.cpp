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

    initComponents();

    QTabWidget* mainWidget = new QTabWidget;

    QWidget* fileWidget = new QWidget;
    QVBoxLayout* mainLayout1 = new QVBoxLayout;
    auto vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(chooseFileBtn);
    vBoxLayout->addWidget(showChooseFile);
    vBoxLayout->addWidget(chooseOutputRoot);
    vBoxLayout->addWidget(showOutputFile);
    mainLayout1->addLayout(vBoxLayout);
    mainLayout1->addWidget(decryptFileBtn,0,Qt::AlignCenter);
    fileWidget->setLayout(mainLayout1);
    mainWidget->addTab(fileWidget,"文件加密");

    auto tempLayout = new QVBoxLayout;
    auto chooseKeyLayout = new QHBoxLayout;
    chooseKeyLayout->addWidget(chooseKeyLabel);
    chooseKeyLayout->addWidget(chooseKey);
    tempLayout->addLayout(chooseKeyLayout);
    tempLayout->addWidget(mainWidget);
    this->setLayout(tempLayout);



    QString keyName = chooseKey->currentText();
    QString keyFileName = QApplication::applicationDirPath()+"/Key/AES/"+keyName;
    aes.LoadKey(keyFileName.toStdString().c_str());
    aes.getKey();

     connect(chooseFileBtn,SIGNAL(clicked()),this,SLOT(chooseFile()));
    connect(chooseOutputRoot,SIGNAL(clicked()),this,SLOT(chooseOutputFile()));
     connect(decryptFileBtn,SIGNAL(clicked()),this,SLOT(decryptFile()));
   //  connect(decryptStrBtn,SIGNAL(clicked()),this,SLOT(decryptStr()));
//    connect(saveToLocal,SIGNAL(clicked()),this,SLOT(saveToLocalFun()));
}
void DecryptFileWindow::initComponents()
{
    // tab1
    chooseKeyLabel=new QLabel(tr("选择AES密钥"));
    chooseKey = new QComboBox();
    QFile *file=new QFile(QApplication::applicationDirPath()+"/Key/AESkey");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(file);
    QString line;
    while(true)
    {
        line =QString(stream.readLine());
        if(line.isNull()) break;
        chooseKey->addItem(line);
    }
    file->close();


    showChooseFile=new QTextEdit;
    chooseFileBtn=new QPushButton(tr("选择文件"));

    showOutputFile=new QTextEdit;
    chooseOutputRoot=new QPushButton(tr("更改保存路径"));

    decryptFileBtn=new QPushButton(tr("jiemi文件"));

}


void DecryptFileWindow::chooseFile()
{
     QString cipherFileName = QFileDialog::getOpenFileName(this,"选择文件",QDir::homePath());
     showChooseFile->setText(cipherFileName);
}

void DecryptFileWindow::chooseOutputFile()
{
    QString outputFileName = QFileDialog::getSaveFileName(this,"选择保存文件",QDir::homePath());
    showOutputFile->setPlainText(outputFileName);
}


void DecryptFileWindow::decryptFile()
{
    QString plainFileName = showChooseFile->toPlainText();
    if(plainFileName.isEmpty()) return;
    QString cipherFileName = showOutputFile->toPlainText();
    aes.DecryptFile(plainFileName.toStdString(),cipherFileName.toStdString());
    QMessageBox::information(this,"message","success");
}
