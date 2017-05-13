
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
    model01->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("用途"));
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
    model02->setColumnCount(6);
    model02->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("姓名"));
    model02->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("用途"));
    model02->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("邮箱"));
    model02->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("生效期"));
    model02->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("失效期"));
    model02->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("公钥"));

    tableView02=new QTableView;
    tableView02->setModel(model02);
    tableView02->setColumnWidth(0,100);
    tableView02->setColumnWidth(1,100);
    tableView02->setColumnWidth(2,150);
    tableView02->setColumnWidth(3,110);
    tableView02->setColumnWidth(4,110);
    tableView02->setColumnWidth(5,230);
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


    extractData(model01,"Key/mykey",true);
    extractData(model02,"Key/pubkey",false);

    connect(tableView01, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showMenu01(QPoint)));
    connect(tableView02, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showMenu02(QPoint)));

    createMenu();

}

void ShowWidgetUI::extractData(QStandardItemModel *model, QString fileName,bool self)
{
    QFile *file01=new QFile(QApplication::applicationDirPath()+"/"+fileName);
   // QTextCodec *code = QTextCodec::codecForName("utf8");
    file01->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream01(file01);
  //  stream01.setCodec(code);

    QString line;
    int linenum=0;
    forever
    {
        line =QString(stream01.readLine());
        if(line.isEmpty() || line.isNull()) break;
        QStringList items  = line.split(";") ;
        for(int i=0; i<items.length(); i++)
        {
             model->setItem(linenum, i, new QStandardItem(items[i]));
        }
        linenum++;
    }
     file01->close();

}

void ShowWidgetUI::showMenu01(QPoint pos){
        menu01->clear(); //清除原有菜单
        menu01->addAction(deleteOtherCertiAction);
        //菜单出现的位置为当前鼠标的位置
        menu01->exec(QCursor::pos());
}

void ShowWidgetUI::showMenu02(QPoint pos){
    menu02->clear(); //清除原有菜单
    menu02->addAction(deleteSelfCertiAction);
    //菜单出现的位置为当前鼠标的位置
    menu02->exec(QCursor::pos());
}

void ShowWidgetUI::createMenu(){
    menu01=new QMenu(tableView01);
    menu02=new QMenu(tableView02);

    tableView01->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView02->setContextMenuPolicy(Qt::CustomContextMenu);

    deleteSelfCertiAction=new QAction(this);
    deleteSelfCertiAction->setText(QString(tr("删除该证书")));
    deleteOtherCertiAction=new QAction(this);
    deleteOtherCertiAction->setText(QString(tr("删除该证书")));
//    showPubKeyMess=new QAction(this);
//    showPubKeyMess->setText(QString(tr("查看证书信息")));
//    showPubAndPrivKeyMess=new QAction(this);
//    showPubAndPrivKeyMess->setText(QString(tr("查看证书信息")));

      connect(deleteSelfCertiAction, SIGNAL(triggered(bool)), this, SLOT(deleteOtherCerti()));
      connect(deleteOtherCertiAction, SIGNAL(triggered(bool)), this, SLOT(deleteSelfCerti()));
  //  connect(showPubKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubKeyMessFun()));
//    connect(showPubAndPrivKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubAndPrivKeyMessFun()));

}


void ShowWidgetUI::addCerti()
{
    QString cerFileName=QFileDialog::getOpenFileName(this,"打开文件",QDir::homePath(),"certification (*.cer)");
    if(cerFileName == nullptr) return;

    QFile *cerFile=new QFile(cerFileName);
    cerFile->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(cerFile);

    QString metaData = stream.readLine();
    QStringList itemList = metaData.split(";");
    QString pubKey = stream.readLine();



    // create pubkey file

    QString pubFileName="Key/RSA/PubKey_"+itemList[0]+"_"+itemList[1];
    util::writeMessageToFile(pubKey,pubFileName);

    // create local certification file
    QString localCertiFileName = "Key/Certi/"+itemList[0]+"_"+itemList[1]+".cer";
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

void ShowWidgetUI::deleteSelfCerti()
{
    QMessageBox message(QMessageBox::Warning,"警告","删除证书的动作不可撤销，是否要删除该证书？",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::No){
        return;
    }

    // delete info in mykey
    QString name = model01->item(tableView01->currentIndex().row(),0)->text();
    util::deleteCerti(name);


    // delete info in ui table
    int currentRow = tableView01->currentIndex().row();
    tableView01->model()->removeRow(currentRow);


}

void ShowWidgetUI::deleteOtherCerti()
{

    QString name = model02->item(tableView02->currentIndex().row(),0)->text();
    util::deleteCerti(name,false);
    int currentRow = tableView02->currentIndex().row();
     tableView02->model()->removeRow(currentRow);
}
void ShowWidgetUI::addSelfRecords(QStringList records)
{
    int nextRow=tableView01->model()->rowCount();
    for(int i=0; i<records.length(); i++)
    {
        model01->setItem(nextRow, i, new QStandardItem(records.at(i)));
    }
}
