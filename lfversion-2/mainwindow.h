#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QLabel>
#include <QToolBar>
#include "ui-showwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QLabel* portInfoLabel = nullptr;

    ShowWidgetUI *showWidget;

  //  QMenu *fileMenu;                           		//各项菜单栏

    QToolBar *toolBar;                          	//工具栏
    //QToolBar *zone02;

    QAction *importCertiAction;                     	//文件菜单项
    QAction *newCertiAction;
    QAction *newAesKeyAction;
    QAction *digitalSigAction;
   // QAction *authentication;
   // QAction *changePortAction;

    QAction *fileTransAction;
    QAction *fileTransRecordAction;

    QAction *encryptAction;
    QAction *decryptAction;


    QAction *exitAction;

    // under system menu
    QAction *aboutAction;
    QAction *setupAction;

private slots:
    void selectCerti();
    void openCreateCertiWindow();
    void openCreateKeyWindow();
    void openEncrytFileWindow();
    void openDecrytFileWindow();
    void openSendFileWindow();
    void openDigitalSigWindow();
    void openAboutDialog();
    void openSetupDialog();
    void openFileRecordWindow();
};

#endif // MAINWINDOW_H
