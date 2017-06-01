#ifndef FILERECORDWINDOW_H
#define FILERECORDWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>

class FileRecordWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FileRecordWindow(QWidget *parent = 0);

signals:

public slots:

private:
    QStandardItemModel *model01;
    QStandardItemModel *model02;
    QTableView *tableView01;
    QTableView *tableView02;

    void extractData();
};

#endif // FILERECORDWINDOW_H
