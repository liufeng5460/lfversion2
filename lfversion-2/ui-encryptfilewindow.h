#ifndef ENCRYFILEWINDOW_H
#define ENCRYFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QComboBox>
class EncrytFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit EncrytFileWindow(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout *Layout01;
    QLabel *fileInputLabel;
    QLabel *showChoseFile;
    QLabel *showOutputFile;
    QPushButton *choseOutputRoot;
    QPushButton *choseFileBtn;
    QPushButton *encrptionFileBtn;

     QGridLayout *Layout02;
     QLabel *typingInputLabel;
     QTextEdit *inputStrArea;
     QPushButton *encrptionStrBtn;

     QGridLayout *Layout03;
     QLabel *outputLabel;
     QTextEdit *outputArea;
     QPushButton *saveToLocal;

     QLabel *choseKeyLabel;
     QComboBox *chooseKey;

};

#endif // ENCRYFILEWINDOW_H
