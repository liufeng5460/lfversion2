#ifndef SENDFILEWINDOW_H
#define SENDFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
class SendFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SendFileWindow(QWidget *parent = 0);

signals:

public slots:
    void selectFile();
    void doSend();
private:
    QLabel* nameLabel;
    QLabel* ipAddressLabel;
    QLabel* portLabel;
    QLabel* fileLabel;

    QComboBox* nameCombo;
    QLineEdit* ipAddressEdit;
    QLineEdit* portEdit;
    QLineEdit* fileEdit;

    QPushButton* selectFileButton;
    QPushButton* testButton;
    QPushButton* sendButton;


    QString fileName;
};

#endif // SENDFILEWINDOW_H
