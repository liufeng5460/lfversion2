#ifndef SENDFILEWINDOW_H
#define SENDFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
class SendFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SendFileWindow(QWidget *parent = 0);

signals:

public slots:
    void selectFile();

private:
    QLabel* ipAddressLabel;
    QLabel* portLabel;
    QLabel* fileLabel;

    QLineEdit* ipAddressEdit;
    QLineEdit* portEdit;
    QLineEdit* fileEdit;

    QPushButton* selectFileButton;
    QPushButton* testButton;
    QPushButton* sendButton;


    QString fileName;
};

#endif // SENDFILEWINDOW_H
