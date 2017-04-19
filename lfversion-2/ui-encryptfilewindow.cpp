#include "ui-encryptfilewindow.h"
#include "status.h"

#include <QVBoxLayout>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
using namespace std;
EncryptFileWindow::EncryptFileWindow(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle(tr("加密文件"));
    this->setWindowIcon(QIcon(":/image/encrypt"));

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
    mainLayout1->addWidget(encryptFileBtn,0,Qt::AlignCenter);
    fileWidget->setLayout(mainLayout1);
    mainWidget->addTab(fileWidget,"文件加密");

    QWidget* textWidget = new QWidget;
    auto mainLayout2 = new QGridLayout;
    mainLayout2->addWidget(typingInputLabel,1,0);
    mainLayout2->addWidget(outputLabel,1,1);
    mainLayout2->addWidget(inputStrArea,2,0);
    mainLayout2->addWidget(outputArea,2,1);
    mainLayout2->addWidget(saveToLocal,3,0);
    mainLayout2->addWidget(encryptStrBtn,3,1);

    textWidget->setLayout(mainLayout2);
    mainWidget->addTab(textWidget,"文本加密");


    auto tempLayout = new QVBoxLayout;
    auto chooseKeyLayout = new QGridLayout;
    chooseKeyLayout->addWidget(chooseKeyLabel,0,0);
    chooseKeyLayout->addWidget(chooseKey,0,1);
    chooseKeyLayout->addWidget(chooseRSAKeyLabel,1,0);
    chooseKeyLayout->addWidget(choosePubkey,1,1);
    chooseKeyLayout->addWidget(useAES,0,2);
    chooseKeyLayout->addWidget(useRSA,1,2);
    tempLayout->addLayout(chooseKeyLayout);
    tempLayout->addWidget(mainWidget);
    this->setLayout(tempLayout);




    // initiate aes handler
    QString keyName = chooseKey->currentText();
    QString keyFileName = QApplication::applicationDirPath()+"/Key/AES/"+keyName;
    aes.LoadKey(keyFileName.toStdString().c_str());
    aes.getKey();



    connect(chooseFileBtn,SIGNAL(clicked(bool)),this,SLOT(chooseFile()));
    connect(chooseOutputRoot,SIGNAL(clicked(bool)),this,SLOT(chooseOutput()));
    connect(encryptStrBtn,SIGNAL(clicked(bool)),this,SLOT(encryptStr()));
    connect(saveToLocal,SIGNAL(clicked(bool)),this,SLOT(saveCipher()));
    connect(encryptFileBtn,SIGNAL(clicked(bool)),this,SLOT(encryptFile()));
}

void EncryptFileWindow::initComponents()
{
    // choose key

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


    chooseRSAKeyLabel = new QLabel(tr("选择RSA密钥"));
    choosePubkey = new QComboBox();
    QFile pubkeyFile(QApplication::applicationDirPath()+"/Key/mykey");
    pubkeyFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream pubkeyStream(&pubkeyFile);
    while(true)
    {
        line = pubkeyStream.readLine();
        if(line.isNull()) break;
        choosePubkey->addItem(line.left(line.indexOf(";")));
    }
    file->close();

    useAES = new QRadioButton("使用AES");
    useRSA = new QRadioButton("使用RSA");
    useAES->setChecked(true);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(useAES);
    buttonGroup->addButton((useRSA));

     // tab1
    fileInputLabel=new QLabel(tr("请选择需要加密的文本：（txt格式）"));
    showChooseFile=new QTextEdit;
    chooseFileBtn=new QPushButton(tr("选择文件"));
    showOutputFile=new QTextEdit;
    chooseOutputRoot=new QPushButton(tr("更改保存路径"));
    encryptFileBtn=new QPushButton(tr("加密文件"));




    // tab2
    typingInputLabel=new QLabel(tr("或者输入您要加密的文本"));
    inputStrArea=new QTextEdit;
    encryptStrBtn=new QPushButton(tr("加密文本"));

    outputLabel=new QLabel(tr("生成的密文："));
    outputArea=new QTextEdit;
    saveToLocal=new QPushButton(tr("保存至本地"));
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
    QString plainFileName = showChooseFile->toPlainText();
    if(plainFileName.isEmpty()) return;
    QString cipherFileName = outputFileName;
    if(useAES->isChecked())
    {
        aes.EncryptFile(plainFileName.toStdString(),cipherFileName.toStdString());
    }
    else if(useRSA->isChecked())
    {
        QString pubkeyFileName = QApplication::applicationDirPath()+"/Key/RSA/PubKey_"+choosePubkey->currentText();
        rsa.Encrypt(pubkeyFileName.toStdString().c_str()
                    ,plainFileName.toStdString().c_str()
                    ,cipherFileName.toStdString().c_str());
    }
    QMessageBox::information(this,"message","success");
}

void EncryptFileWindow::chooseFile()
{
    QString plainFileName = QFileDialog::getOpenFileName(this,"选择文件",QDir::homePath(),"All files(*)");
    showChooseFile->setPlainText(plainFileName);
}

void EncryptFileWindow::chooseOutput()
{
    outputFileName = QFileDialog::getSaveFileName(this,"选择保存文件",QDir::homePath());
    if(outputFileName.isEmpty()) return;
    showOutputFile->setPlainText(outputFileName);
}
