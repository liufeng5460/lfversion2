#ifndef CREATECERTIWINDOW_H
#define CREATECERTIWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class CreateCertiWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CreateCertiWindow(QWidget *parent = 0);

private:
    QLabel *purposeLabel;
    QLabel *mailLabel;
    QLabel *validFromLabel;
    QLabel *validUtilLabel;
    QLineEdit *purposeEdit;
    QLineEdit *mailEdit;
    QLineEdit *validFromEdit;
    QLineEdit *validUtilEdit;
    QString pubFileName;
    QString privFileName;
    QPushButton *submitBtn;
signals:
   // void toShowWidget(QStack<QString>);

private slots:
    void updateCertiInfo(QString );
    void genCerti();
};

#endif // CREATECERTIWINDOW_H
