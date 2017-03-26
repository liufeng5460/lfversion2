#ifndef DECRYFILEWINDOW_H
#define DECRYFILEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
class DecryptFileWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DecryptFileWindow(QWidget *parent = 0);

signals:

public slots:

private:
    QGridLayout *Layout01;
    QLabel *fileInputLabel;
    QLabel *showChoseFile;
    QLabel *showOutputFile;
    QPushButton *choseOutputRoot;
    QPushButton *choseFileBtn;
    QPushButton *decrptionFileBtn;


    QGridLayout *Layout02;
    QLabel *typingInputLabel;
    QTextEdit *inputStrArea;
    QPushButton *decrptionStrBtn;

    QGridLayout *Layout03;
    QLabel *outputLabel;
    QTextEdit *outputArea;
    QPushButton *saveToLocal;

    QLabel *choseKeyLabel;
    QComboBox *chooseKey;
};

#endif // DECRYFILEWINDOW_H
