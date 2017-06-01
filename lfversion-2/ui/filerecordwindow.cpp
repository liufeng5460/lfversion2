#include "ui/filerecordwindow.h"
#include "status.h"

#include <QTabWidget>
#include <QVBoxLayout>
FileRecordWindow::FileRecordWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("文件传输记录"));

    // for send file tab
    model01 = new QStandardItemModel();
    model01->setColumnCount(4);
    model01->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("文件"));
    model01->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("接收者"));
    model01->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("IP地址"));
    model01->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("发送时间"));


    tableView01=new QTableView;
    tableView01->setModel(model01);
    int widths[] = {120,60,80,120};
    int i=0;
    tableView01->setColumnWidth(0,widths[i++]);
    tableView01->setColumnWidth(1,widths[i++]);
    tableView01->setColumnWidth(2,widths[i++]);
    tableView01->setColumnWidth(3,widths[i++]);



    // for reveive file records tab;

    model02 = new QStandardItemModel();
    model02->setColumnCount(4);
    model02->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("文件"));
    model02->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("发送者"));
    model02->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("IP地址"));
    model02->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("接收时间"));


    tableView02=new QTableView;
    tableView02->setModel(model02);
    int widths2[] = {120,60,80,120};
    i=0;
    tableView02->setColumnWidth(0,widths2[i++]);
    tableView02->setColumnWidth(1,widths2[i++]);
    tableView02->setColumnWidth(2,widths2[i++]);
    tableView02->setColumnWidth(3,widths2[i++]);

    // layout
    QTabWidget* mainWidget = new QTabWidget;
    QWidget* tab1 = new QWidget;
    QVBoxLayout* tab1Layout = new QVBoxLayout;
    tab1Layout->addWidget(tableView01);
    tab1->setLayout(tab1Layout);

    QWidget* tab2 = new QWidget;
    QVBoxLayout* tab2Layout = new QVBoxLayout;
    tab2Layout->addWidget(tableView02);
    tab2->setLayout(tab2Layout);


    mainWidget->addTab(tab1, "发送文件");
    mainWidget->addTab(tab2, "接收文件");


    QVBoxLayout* tmpLayout = new QVBoxLayout;
    tmpLayout->addWidget(mainWidget);
    this->setLayout(tmpLayout);
    this->setMinimumWidth(550);

    extractData();
    tableView01->resizeColumnsToContents();


}

void FileRecordWindow::extractData()
{

    // extract sended file data
    QFile sendFileRecordFile(Status::sendFileRecord);
    if(sendFileRecordFile.exists())
    {
        sendFileRecordFile.open(QIODevice::ReadOnly |QIODevice::Text);
        QTextStream out(&sendFileRecordFile);
        int i=0,j=0;
        while(!out.atEnd())
        {
            QString line = out.readLine();
            auto items = line.split(",");
            for(auto item: items)
            {
                model01->setItem(i,j++,new QStandardItem(item));
            }
            j=0;
            i++;
        }

        sendFileRecordFile.close();
    }

    // extract received file data
    QFile receivedFileRecordFile(Status::sendFileRecord);
    if(receivedFileRecordFile.exists())
    {
        receivedFileRecordFile.open(QIODevice::ReadOnly |QIODevice::Text);
        QTextStream out(&receivedFileRecordFile);
        int i=0,j=0;
        while(!out.atEnd())
        {
            QString line = out.readLine();
            auto items = line.split(",");
            for(auto item: items)
            {
                model01->setItem(i,j++,new QStandardItem(item));
            }
            j=0;
            i++;
        }

        receivedFileRecordFile.close();
    }
}
