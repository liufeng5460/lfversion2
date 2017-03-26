#include "ui-showwidget.h"
#include <QVBoxLayout>
#include <QStack>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
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
    extractData(model02,"Key/pubkey",6);

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
    showPubKeyMess=new QAction(this);
    showPubKeyMess->setText(QString(tr("查看证书信息")));
    showPubAndPrivKeyMess=new QAction(this);
    showPubAndPrivKeyMess->setText(QString(tr("查看证书信息")));

 //   connect(deletePubKey, SIGNAL(triggered(bool)), this, SLOT(deletePubKeyFun()));
  //  connect(deletePubAndPrivKey, SIGNAL(triggered(bool)), this, SLOT(deletePubAndPrivKeyFun()));
  //  connect(showPubKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubKeyMessFun()));
//    connect(showPubAndPrivKeyMess, SIGNAL(triggered(bool)), this, SLOT(showPubAndPrivKeyMessFun()));

}


void ShowWidgetUI::addCerti()
{
    QString filePlace = QFileDialog::getOpenFileName(this,"打开文件","/","all files(*)");
    QFile *file=new QFile(filePlace);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(file);
  //  QTextCodec *code = QTextCodec::codecForName("ANSI");
 //   stream.setCodec(code);
    QString data;
    QString info="";
    int i=0;
    int currentIndex=tableView02->model()->rowCount();
    qDebug() << currentIndex;

    while (!stream.atEnd() && i<=5)
    {
        data=QString(stream.readLine());
        info=info+data+";";
        model02->setItem(currentIndex, i, new QStandardItem(data));
        i=i+1;
    }
    file->close();

    qDebug() << info;

    QFile filein(QCoreApplication::applicationDirPath()+"/Key/pubkey");
    if( filein.open(QIODevice::ReadWrite|QIODevice::Append | QIODevice::Text) ){
        QTextStream in(&filein);
       in<<  info << "\n";
    } else {
        qDebug() <<  filein.error();
        qDebug() <<  filein.errorString();
    }
    filein.close();
}
