#ifndef STATUS
#define STATUS



#include "ui-showwidget.h"
#include "mainwindow.h"
#include <string>

using namespace std;
namespace Status {


void init();
void checkDirs();
void config();
void updatePaths(QString appDir="");

// about info
extern QString appName;

// user info
extern QString username;

// main window pointer
extern MainWindow* mainWindow;
extern ShowWidgetUI* showWidget;

// network info
extern bool listening;
extern quint16 port;
extern string cipherText;
extern string plainText;

//path info

extern QString profile;
extern QString workingDir;
extern QString tmpDir;
extern QString aesDir;
extern QString rsaDir;
extern QString certiDir;
extern QString logDir;

}



#endif // STATUS

