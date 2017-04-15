#ifndef ENCRYFILEWINDOW_H
#define ENCRYFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QComboBox>

#include "myaes.h"

class EncryptFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit EncryptFileWindow(QWidget *parent = 0);

signals:

public slots:
    void encryptStr();
    void saveCipher();
    void encryptFile();
private:
    QGridLayout *Layout01;
    QLabel *fileInputLabel;
    QLabel *showChooseFile;
    QLabel *showOutputFile;
    QPushButton *chooseOutputRoot;
    QPushButton *chooseFileBtn;
    QPushButton *encryptFileBtn;

     QGridLayout *Layout02;
     QLabel *typingInputLabel;
     QTextEdit *inputStrArea;
     QPushButton *encryptionStrBtn;

     QGridLayout *Layout03;
     QLabel *outputLabel;
     QTextEdit *outputArea;
     QPushButton *saveToLocal;

     QLabel *chooseKeyLabel;
     QComboBox *chooseKey;


     MyAES aes;

};

#endif // ENCRYFILEWINDOW_H
