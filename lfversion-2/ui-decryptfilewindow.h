#ifndef DECRYFILEWINDOW_H
#define DECRYFILEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include "myaes.h"
#include "myrsa.h"
class DecryptFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DecryptFileWindow(QWidget *parent = 0);

signals:

public slots:

    void chooseFile();
    void chooseOutputFile();
    void decryptFile();
private:
    QLabel *fileInputLabel;
    QTextEdit *showChooseFile;
    QTextEdit *showOutputFile;
    QPushButton *chooseOutputRoot;
    QPushButton *chooseFileBtn;
    QPushButton *decryptFileBtn;

    QLabel *chooseKeyLabel;
    QLabel *chooseRSAKeyLabel;
    QComboBox *choosePubkey;
    QComboBox *chooseKey;
    QRadioButton *useAES;
    QRadioButton *useRSA;
    QButtonGroup *buttonGroup;

    MyAES aes;
    MyRSA rsa;
    void initComponents();
};

#endif // DECRYFILEWINDOW_H
