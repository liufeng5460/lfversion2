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
extern QString workingDir;
extern QString keyDir;
extern QString tmpDir;
extern QString aesDir;
extern QString rsaDir;
extern QString LWEDir;
extern QString BlissDir;
extern QString certiDir;
extern QString logDir;
extern QString configDir;

// file info
extern QString profile;
extern QString selfCertiInfo;
extern QString othersCertiInfo;
extern QString contact;


}



#endif // STATUS

