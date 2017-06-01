#ifndef STATUS
#define STATUS



#include "ui-showwidget.h"
#include "mainwindow.h"
#include "netaction.h"
#include <string>
#include <map>

using namespace std;
namespace Status {


void init();
void checkDirs();
void config();
void updatePaths(QString appDir="");

// about info
extern QString appName;

/* config info
 * username
 * port
 *
 *
 */
extern map<QString, QString> conf;

// main window pointer
extern MainWindow* mainWindow;
extern ShowWidgetUI* showWidget;
extern NetAction* server;

// network info
extern string cipherText;
extern string plainText;
extern int waitTime;

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
extern QString fileDir;

// file info
extern QString profile;
extern QString selfCertiInfo;
extern QString othersCertiInfo;
extern QString contact;
extern QString sendFileRecord;
extern QString receiveFileRecord;


}



#endif // STATUS

