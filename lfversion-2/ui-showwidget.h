#ifndef SHOWWIDGETUI_H
#define SHOWWIDGETUI_H

#include <QFrame>
#include <QStandardItemModel>
#include <QTableView>
#include <QFile>
#include <QMenu>
#include <QAction>
class ShowWidgetUI : public QFrame
{
    Q_OBJECT
public:
    explicit ShowWidgetUI(QWidget *parent = 0);

    void addCerti();

signals:

public slots:

    void showMenu01(QPoint);
    void showMenu02(QPoint);
private:

    QMenu *menu01;
    QMenu *menu02;
    QAction *deletePubKey;
    QAction *deletePubAndPrivKey;
    QAction *showPubKeyMess;
    QAction *showPubAndPrivKeyMess;

    void extractData(QStandardItemModel* model, QString fileName,int count);
    void createMenu();


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
