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
    QString cipherFileName = showChooseFile->toPlainText();
    if(cipherFileName.isEmpty()) return;
    QString plainFileName = showOutputFile->toPlainText();
    if(useAES->isChecked())
    {
        aes.DecryptFile(plainFileName.toStdString(),cipherFileName.toStdString());
    }else if(useRSA->isChecked())
    {
        QString privkeyFileName = QApplication::applicationDirPath()+"/Key/RSA/PrivKey_"+choosePubkey->currentText();
        rsa.Decrypt(privkeyFileName.toStdString().c_str()
                    ,cipherFileName.toStdString().c_str()
                    ,plainFileName.toStdString().c_str());
    }
    QMessageBox::information(this,"message","success");
}
