#ifndef DECRYFILEWINDOW_H
#define DECRYFILEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>

#include "myaes.h"
class DecryptFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DecryptFileWindow(QWidget *parent = 0);

signals:

public slots:
    void decryptStr();
    void chooseFile();
    void decryptFile();
private:
    QGridLayout *Layout01;
    QLabel *fileInputLabel;
    QLabel *showchooseFile;
    QLabel *showOutputFile;
    QPushButton *chooseOutputRoot;
    QPushButton *chooseFileBtn;
    QPushButton *decryptFileBtn;


    QGridLayout *Layout02;
    QLabel *typingInputLabel;
    QTextEdit *inputStrArea;
    QPushButton *decryptStrBtn;

    QGridLayout *Layout03;
    QLabel *outputLabel;
    QTextEdit *outputArea;
    QPushButton *saveToLocal;

    QLabel *chooseKeyLabel;
    QComboBox *chooseKey;

    MyAES aes;
};

#endif // DECRYFILEWINDOW_H
