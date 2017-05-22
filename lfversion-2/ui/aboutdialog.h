#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class AboutDialog : public QWidget
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel* purpose;
    QLabel* name;
    QLabel* institution;
    QLabel* address;
    QLabel* contact;
    QPushButton* okButton;

};

#endif // ABOUTDIALOG_H
