#ifndef SHOWWIDGETUI_H
#define SHOWWIDGETUI_H

#include <QFrame>
#include <QStandardItemModel>
#include <QTableView>

class ShowWidgetUI : public QFrame
{
    Q_OBJECT
public:
    explicit ShowWidgetUI(QWidget *parent = 0);


signals:

public slots:

private:
    QString *name;
    QString *mail;
    QString *validFrom;
    QString *validUtil;
    QString *detail;
    QString *keyId;

    QStandardItemModel *model01;
    QStandardItemModel *model02;
    QTableView *tableView01;
    QTableView *tableView02;
};

#endif // SHOWWIDGETUI_H
