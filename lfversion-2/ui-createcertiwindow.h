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
    QLabel *nameLabel;
    QLabel *mailLabel;
    QLabel *validFromLabel;
    QLabel *validUtilLabel;
    QLineEdit *nameEdit;
    QLineEdit *mailEdit;
    QLineEdit *validFromEdit;
    QLineEdit *validUtilEdit;
    QString pubFileName;
    QString privFileName;
    QPushButton *submitBtn;
signals:

public slots:
};

#endif // CREATECERTIWINDOW_H
