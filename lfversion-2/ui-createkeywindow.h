#ifndef CREATEKEYWINDOW_H
#define CREATEKEYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
class CreateKeyWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CreateKeyWindow(QWidget *parent = 0);

signals:

public slots:

    void genAesKey();
private:
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *KeyLengthLabel;
    QRadioButton *Lenth16;
    QRadioButton *Lenth32;
    QPushButton *submitBtn;

};

#endif // CREATEKEYWINDOW_H
