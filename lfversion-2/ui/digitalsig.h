#ifndef DIGITALSIG_H
#define DIGITALSIG_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
class DigitalSigWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DigitalSigWindow(QWidget *parent = 0);


signals:

public slots:
    void selectSrcFile1();
    void selectSrcFile2();
    void selectSigFile1();
    void selectSigFile2();
    void createSig();
    void verifySig();

private:
    void initComponents();
    static QString sigSuffix;

    QLabel* srcFileLabel1;
    QLabel* sigFileLabel1;
    QLineEdit* srcFileEdit1;
    QLineEdit* sigFileEdit1;
    QPushButton* srcFileButton1;
    QPushButton* sigFileButton1;
    QLabel* pickCertiLabel1;
    QComboBox* pickCertiBox1;
    QPushButton* exeButton1;

    QLabel* srcFileLabel2;
    QLabel* sigFileLabel2;
    QLineEdit* srcFileEdit2;
    QLineEdit* sigFileEdit2;
    QPushButton* srcFileButton2;
    QPushButton* sigFileButton2;
    QLabel* pickCertiLabel2;
    QComboBox* pickCertiBox2;
    QPushButton* exeButton2;



/*
    QVBoxLayout* mainLayout;
    QGroupBox* createSigGroup;
    QGroupBox* verifySigGroup;
    QGridLayout* createSigLayout;
    QGridLayout* verifySigLayout;

    QLabel* srcFileLabel1;
    QLabel* sigFileLabel1;
    QLineEdit* srcFileEdit1;
    QLineEdit* sigFileEdit1;
    QPushButton* srcFileButton1;
    QPushButton* sigFileButton1;
    QLabel* pickCertiLabel1;
    QComboBox* pickCertiBox1;
    QPushButton* exeButton1;

    QLabel* srcFileLabel2;
    QLabel* sigFileLabel2;
    QLineEdit* srcFileEdit2;
    QLineEdit* sigFileEdit2;
    QPushButton* srcFileButton2;
    QPushButton* sigFileButton2;
    QLabel* pickCertiLabel2;
    QComboBox* pickCertiBox2;
    QPushButton* exeButton2;
    */
};

#endif // DIGITALSIG_H
