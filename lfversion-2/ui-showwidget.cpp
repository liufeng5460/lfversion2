
#include "ui-showwidget.h"
#include "util.h"

#include <QVBoxLayout>
#include <QStack>
#include <QList>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QFile>

#include <iostream>
using namespace std;
ShowWidgetUI::ShowWidgetUI(QWidget *parent) : QFrame(parent)
{

    model01 = new QStandardItemModel();
    model01->setColumnCount(6);
    model01->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("姓名"));
    model01->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("邮箱"));
    model01->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("生效期"));
    model01->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("失效期"));
    model01->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("公钥"));
    model01->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("私钥"));

    tableView01=new QTableView;
    tableView01->setModel(model01);
    tableView01->setColumnWidth(0,115);
    tableView01->setColumnWidth(1,130);
    tableView01->setColumnWidth(2,85);
    tableView01->setColumnWidth(3,85);
    tableView01->setColumnWidth(4,195);
    tableView01->setColumnWidth(5,195);
    tableView01->setSelectionBehavior(QTableView::SelectRows);
    tableView01->setEditTriggers(QTableView::NoEditTriggers);
    tableView01->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView01->setMouseTracking(true);

    model02 = new QStandardItemModel();
    model02->setColumnCount(5);
    model02->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("姓名"));
    model02->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("邮箱"));
    model02->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("生效期"));
    model02->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("失效期"));
    model02->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("公钥"));

    tableView02=new QTableView;
    tableView02->setModel(model02);
    tableView02->setColumnWidth(0,150);
    tableView02->setColumnWidth(1,180);
    tableView02->setColumnWidth(2,120);
    tableView02->setColumnWidth(3,120);
    tableView02->setColumnWidth(4,230);
    tableView02->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView02->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView01->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView02->setMouseTracking(true);

    QVBoxLayout *mainLayout =new QVBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(new QLabel("我的证书："));
    mainLayout->addWidget(tableView01);
    mainLayout->addWidget(new QLabel("拥有他人证书："));
    mainLayout->addWidget(tableView02);


    extractData(model01,"Key/mykey",5);
    extractData(model02,"Key/pubkey",4);

    connect(tableView01, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showMenu01(QPoint)));
    connect(tableView02, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showMenu02(QPoint)));

    createMenu();

}

void ShowWidgetUI::extractData(QStandardItemModel *model, QString fileName,int count)
{
    QFile *file01=new QFile(QApplication::applicationDirPath()+"/"+fileName);
   // QTextCodec *code = QTextCodec::codecForName("utf8");
    file01->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream01(file01);
  //  stream01.setCodec(code);

    QString line;
    int linenum=0;
    do{
        line =QString(stream01.readLine());
        if(line.isEmpty() || line.isNull()) break;
        QStringList temp  = line.split(";") ;
        QList<QString>::Iterator it = temp.begin(),itend = temp.end();
          int iter = 0;
          for (;it != itend && iter<=count; it++,iter++){
              model->setItem(linenum, iter, new QStandardItem(temp[iter]));
           }
          linenum++;
    } while (!line.isNull() && !line.isEmpty());
     file01->close();

}

void ShowWidgetUI::showMenu01(QPoint pos){
        menu01->clear(); //清除原有菜单
        menu01->addAction(deletePubAndPrivKey);
        menu01->addAction(showPubAndPrivKeyMess);
        //菜单出现的位置为当前鼠标的位置
        menu01->exec(QCursor::pos());
}

void ShowWidgetUI::showMenu02(QPoint pos){
    menu02->clear(); //清除原有菜单
    menu02->addAction(deletePubKey);
    menu02->addAction(showPubKeyMess);
    //菜单出现的位置为当前鼠标的位置
    menu02->exec(QCursor::pos());
}

void ShowWidgetUI::createMenu(){
    menu01=new QMenu(tableView01);
    menu02=new QMenu(tableView02);

    tableView01->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView02->setContextMenuPolicy(Qt::CustomContextMenu);

    deletePubKey=new QAction(this);
    deletePubKey->setText(QString(tr("删除该证书")));
    deletePubAndPrivKey=new QAction(this);
    deletePubAndPrivKey->setText(QString(tr("删除该证书")));
//    showPubKeyMess=new QAction(this);
//    showPubKeyMess->setText(QString(tr("查看证书信息")));
//    showPubAndPrivKeyMess=new QAction(this);
//    showPubAndPrivKeyMess->setText(QString(tr("查看证书信息")));

   // connect(deletePubKey, SIGNAL(triggered(bool)), this, SLOT(deletePubKeyFun()));
      connect(deletePubAndPrivKey, SIGNAL(triggered(bool)), this, SLOT(deletePubAndPrivKeyFun()));
  //  connect(showPubKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubKeyMessFun()));
//    connect(showPubAndPrivKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubAndPrivKeyMessFun()));

}


void ShowWidgetUI::addCerti()
{
    QString cerFileName=QFileDialog::getOpenFileName(this,"打开文件","/home/ydu","certification (*.cer)");
    if(cerFileName == nullptr) return;

    QFile *cerFile=new QFile(cerFileName);
    cerFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(cerFile);

    QString metaData = stream.readLine();
    QStringList itemList = metaData.split(";");
    QString pubKey = stream.readLine();



    // create pubkey file

    QString pubFileName="Key/RSA/PubKey_"+itemList.at(0);
    util::writeMessageToFile(pubKey,pubFileName);

    // create certification file
    QString localCertiFileName = "Key/Certi/"+itemList.at(0)+".cer";
    util::writeMessageToFile(metaData+"\n"+pubKey,localCertiFileName);

    // update table view

    int nextRow=tableView02->model()->rowCount();
    int i=0;
    for(QString item: itemList)
    {
        model02->setItem(nextRow, i, new QStandardItem(item));
        i++;
    }
    model02->setItem(nextRow,i,new QStandardItem(pubFileName));

    // update pubkey file
    QString totalMetaData = metaData+";"+pubFileName;
    util::appendMessageToFile(totalMetaData,"Key/pubkey");
    cerFile->close();
}

void ShowWidgetUI::deletePubAndPrivKeyFun()
{

    QMessageBox message(QMessageBox::Warning,"警告","删除证书的动作不可撤销，是否要删除该证书？",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::No){
        return;
    }

    int currentRow = tableView01->currentIndex().row();
    QString workingDir = QCoreApplication::applicationDirPath() + "/";
    QString pubkeyroot=workingDir  + (model01->data(model01->index(currentRow,4))).toString();
    QString privkeyroot= workingDir+ (model01->data(model01->index(currentRow,5))).toString();
    QString certiRoot = workingDir+"Key/Certi/"+model01->data(model01->index(currentRow,0)).toString()+".cer";

    QFile::remove(pubkeyroot);
    QFile::remove(privkeyroot);
    QFile::remove(certiRoot);

     //   fileOperation.deleteOnelineInFile(currentRow,QString(QCoreApplication::applicationDirPath()+"/Key/mykey"));

        QList<QString> lines;
        QFile pubkeyFile(workingDir+"Key/mykey");
        pubkeyFile.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream pubkeyStream(&pubkeyFile);
        QString line;
        while(!pubkeyStream.atEnd())
        {
            line = pubkeyStream.readLine().trimmed();
            if(line=="") continue;
            if(line.startsWith(model01->data(model01->index(currentRow,0)).toString()))
            {
                //qDebug()<<model01->data(model01->index(currentRow,0)).toString();
                continue;
            }
            lines.append(line);
        }
        pubkeyFile.close();

        pubkeyFile.open(QIODevice::WriteOnly|QIODevice::Text);
        for(int i=0; i<lines.length();i++)
        {
            pubkeyStream<<lines[i]<<"\n";
        }
        pubkeyFile.close();

        tableView01->model()->removeRow(currentRow);
}
