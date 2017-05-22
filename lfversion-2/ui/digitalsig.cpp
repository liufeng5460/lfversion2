#include "ui/digitalsig.h"
#include "status.h"
#include "mybliss.h"

#include <QMessageBox>

#include <QGridLayout>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDebug>

QString DigitalSigWindow::sigSuffix = ".bls";

DigitalSigWindow::DigitalSigWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("数字签名"));
    this->setWindowIcon(QIcon(":/image/identity"));

    initComponents();
    qDebug("after init components");

    QTabWidget* mainWidget = new QTabWidget;

    QWidget* signWidget=new QWidget;
    QGridLayout* createSigLayout = new QGridLayout;
     createSigLayout->setSpacing(10);
     createSigLayout->addWidget(srcFileLabel1,   0,0);
     createSigLayout->addWidget(srcFileEdit1,    0,1,1,3);
     createSigLayout->addWidget(srcFileButton1,  0,4);
     createSigLayout->addWidget(sigFileLabel1,   1,0);
     createSigLayout->addWidget(sigFileEdit1,    1,1,1,3);
     createSigLayout->addWidget(sigFileButton1,  1,4);
     createSigLayout->addWidget(pickCertiLabel1, 2,0);
     createSigLayout->addWidget(pickCertiBox1,   2,1,1,3);
     createSigLayout->addWidget(exeButton1,      3,4);
    signWidget->setLayout(createSigLayout);
    mainWidget->addTab(signWidget,"签名文件");


    QWidget* verifyWidget = new QWidget;
    QGridLayout* verifySigLayout = new QGridLayout;
    verifySigLayout->setSpacing(10);
    verifySigLayout->addWidget(srcFileLabel2,   0,0);
    verifySigLayout->addWidget(srcFileEdit2,    0,1,1,3);
    verifySigLayout->addWidget(srcFileButton2,  0,4);
    verifySigLayout->addWidget(sigFileLabel2,   1,0);
    verifySigLayout->addWidget(sigFileEdit2,    1,1,1,3);
    verifySigLayout->addWidget(sigFileButton2,  1,4);
    verifySigLayout->addWidget(pickCertiLabel2, 2,0);
    verifySigLayout->addWidget(pickCertiBox2,   2,1,1,3);
    verifySigLayout->addWidget(exeButton2,      3,4);
    verifyWidget->setLayout(verifySigLayout);
    mainWidget->addTab(verifyWidget,"验证签名");

    QVBoxLayout*  mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mainWidget);
    this->setLayout(mainLayout);

    /*
    createSigGroup = new QGroupBox;
    createSigGroup->setTitle("创建签名: ");
    createSigGroup->setFlat(false);
   createSigLayout = new QGridLayout;
    createSigLayout->setSpacing(10);
    createSigLayout->addWidget(srcFileLabel1,   0,0);
    createSigLayout->addWidget(srcFileEdit1,    0,1,1,3);
    createSigLayout->addWidget(srcFileButton1,  0,4);
    createSigLayout->addWidget(sigFileLabel1,   1,0);
    createSigLayout->addWidget(sigFileEdit1,    1,1,1,3);
    createSigLayout->addWidget(sigFileButton1,  1,4);
    createSigLayout->addWidget(pickCertiLabel1, 2,0);
    createSigLayout->addWidget(pickCertiBox1,   2,1,1,3);
    createSigLayout->addWidget(exeButton1,      3,4);
    createSigGroup->setLayout(createSigLayout);


    verifySigGroup = new QGroupBox("验证签名: ");
    verifySigLayout = new QGridLayout;
    verifySigLayout->setSpacing(10);

    verifySigLayout->addWidget(srcFileLabel2,   0,0);
    verifySigLayout->addWidget(srcFileEdit2,    0,1,1,3);
    verifySigLayout->addWidget(srcFileButton2,  0,4);
    verifySigLayout->addWidget(sigFileLabel2,   1,0);
    verifySigLayout->addWidget(sigFileEdit2,    1,1,1,3);
    verifySigLayout->addWidget(sigFileButton2,  1,4);
    verifySigLayout->addWidget(pickCertiLabel2, 2,0);
    verifySigLayout->addWidget(pickCertiBox2,   2,1,1,3);
    verifySigLayout->addWidget(exeButton2,      3,4);
    verifySigGroup->setLayout(verifySigLayout);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(createSigGroup);
    mainLayout->addWidget(verifySigGroup);

    mainLayout->setMargin(20);
    mainLayout->setSpacing(20);

    this->setLayout(mainLayout);
    qDebug("after set layout");

     connect(srcFileButton1, SIGNAL(clicked(bool)),this,SLOT(selectSrcFile1()));
    connect(sigFileButton1,SIGNAL(clicked(bool)), this, SLOT(selectSigFile1()));
    connect(exeButton1, SIGNAL(clicked(bool)),this,SLOT(createSig()));

    connect(srcFileButton2, SIGNAL(clicked(bool)),this,SLOT(selectSrcFile2()));
    qDebug("after connect");
    */

}

void DigitalSigWindow::initComponents()
{

    // widgets in tab1(create signature)
    srcFileLabel1 = new QLabel("原始文件: ");
    sigFileLabel1 = new QLabel("签名文件: ");
    srcFileEdit1 = new QLineEdit;
    sigFileEdit1 = new QLineEdit;
    srcFileButton1 = new QPushButton("选择");
    sigFileButton1 = new QPushButton("选择");
    pickCertiLabel1 = new QLabel("选择证书:");
    pickCertiBox1  =new QComboBox;
    exeButton1 = new QPushButton("创建");

    // widgets in tab2(verify signature)
    srcFileLabel2 = new QLabel("原始文件: ");
    srcFileEdit2 = new QLineEdit;
    srcFileButton2 = new QPushButton("选择");
    sigFileLabel2 = new QLabel("签名文件: ");
    sigFileEdit2 = new QLineEdit;
    sigFileButton2 = new QPushButton("选择");
    pickCertiLabel2 = new QLabel("选择证书: ");
    pickCertiBox2 = new QComboBox;
    exeButton2 = new QPushButton("验证");

    /*
    // get certification name for sign ( own certi)
    QFile myCertiListFile(Status::selfCertiInfo);
    myCertiListFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&myCertiListFile);
    while(!in.atEnd())
    {
        QString temp = in.readLine();
        pickCertiBox1->addItem(temp.left(temp.indexOf(";")));
        pickCertiBox2->addItem(temp.left(temp.indexOf(";")));
    }
    myCertiListFile.close();

    // get certification name for verify (others' certi)
    QFile  othersCertiListFile(Status::othersCertiInfo);
    othersCertiListFile.open(QIODevice::ReadOnly | QIODevice::Text);
    in.setDevice(&othersCertiListFile);
    while(!in.atEnd())
    {
        QString tmp = in.readLine();
        pickCertiBox2->addItem(tmp.split(";")[0]+"_"+tmp.split(";")[1]);
    }
    othersCertiListFile.close();
    */
}

void DigitalSigWindow::selectSrcFile1()
{
    /*
    QString srcFilePath = QFileDialog::getOpenFileName(this,"选择文件",QDir::homePath(),"All files(*)");
    srcFileEdit1->setText(srcFilePath);
    srcFileEdit1->setToolTip(srcFilePath);

    int dotIndex = srcFilePath.indexOf(".");
    QString dstFilePath;
    if(dotIndex == -1)
    {
        dstFilePath = srcFilePath+sigSuffix;
    }
    else
    {
        dstFilePath = srcFilePath.left(dotIndex)+sigSuffix;
    }
    sigFileEdit1->setText(dstFilePath);
    sigFileEdit1->setToolTip(dstFilePath);
*/
}

void DigitalSigWindow::selectSrcFile2()
{
    /*
    QString srcFilePath = QFileDialog::getOpenFileName(this,"选择文件",QDir::homePath(),"All files(*)");
    srcFileEdit2->setText(srcFilePath);
    srcFileEdit2->setToolTip(srcFilePath);
    */
}

void DigitalSigWindow::selectSigFile1()
{
    /*
    QString dstFilePath = QFileDialog::getSaveFileName(this,"选择保存文件",QDir::homePath(),"Bliss Sig(.bls)");
    sigFileEdit1->setText(dstFilePath);
    sigFileEdit1->setToolTip(dstFilePath);
    */
}

void DigitalSigWindow::createSig()
{
    /*
    bool success = MyBliss::sigFile(pickCertiBox1->currentText(),srcFileEdit1->text(),sigFileEdit1->text());
    if(success)
    {
        QMessageBox::information(nullptr,"数字签名","创建签名成功!");
    }
    else
    {
        QMessageBox::critical(nullptr,"数字签名","创建签名失败!");
    }
    */
}


void DigitalSigWindow::verifySig()
{
    /*
    bool success = MyBliss::verifyFile(pickCertiBox2->currentText(),
                                       srcFileEdit2->text(),
                                       sigFileEdit2->text());
    if(success)
    {
        QMessageBox::information(nullptr,"数字签名","验证成功!");
    }
    else
    {
        QMessageBox::critical(nullptr,"数字签名","验证失败!");
    }
    */
}
