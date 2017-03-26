#include "ui-showwidget.h"
#include <QVBoxLayout>
#include <QStack>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include <QTextStream>
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
