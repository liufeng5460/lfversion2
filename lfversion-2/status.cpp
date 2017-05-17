#include "netaction.h"
#include "status.h"
#include "util.h"
#include "ui-inputusernamedialog.h"


#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <thread>

#define DEBUG 0


// about info
QString Status::appName("集成加密软件");

// user info
QString Status::username;

// main window pointer
ShowWidgetUI* Status::showWidget(nullptr);
MainWindow* Status::mainWindow(nullptr);

// web info
bool  Status::listening(false);
quint16 Status::port(5460);
string Status::plainText("");
string Status::cipherText("");

// path info
 QString Status::workingDir("");
 QString Status::tmpDir("");
QString Status::aesDir("");
 QString Status::rsaDir("");
 QString Status::LWEDir("");
 QString Status::BlissDir("");
 QString Status::certiDir("");
 QString Status::profile("");
 QString Status::logDir("");




 void Status::init()
 {
     updatePaths();
     checkDirs();
     config();
     new NetAction;

 }


 void Status::config()
 {

     /* config items
      * username
      */

     QFile profile(Status::profile);
     if(profile.exists())
     {
         profile.open(QIODevice::ReadOnly|QIODevice::Text);
         QTextStream in(&profile);
         QStringList pairs =in.readLine().split(":");
         Status::username = pairs.at(1);
         profile.close();
     }
     else
     {
         util::dialogSetup(new InputUsernameDialog);
     }
 }
 void Status::checkDirs()
 {
     //检查文件夹是否存在，不存在则创建
     QDir *checkDir=new QDir();
     bool exist;
     QString workingDir=QApplication::applicationDirPath();

     QString dirs[] = {
         "/Key",
         "/Tmp",
         "/Key/AES",
         "/Key/RSA",
         "/Key/LWE",
         "/Key/Bliss",
         "/Key/Certi",
         "/Config",
         "/Log"
     };
     for(QString d:dirs)
     {
         exist = checkDir->exists(workingDir+d);
         if(!exist) checkDir->mkdir(workingDir+d);
     }
 }

void Status::updatePaths(QString appDir)
{
    if(appDir.isEmpty())
    {
        appDir = QApplication::applicationDirPath();
    }

    // setup directories
    workingDir = appDir+"/";
    tmpDir = workingDir+"/Tmp/";
    aesDir = workingDir+"/Key/AES/";
    rsaDir = workingDir+"/Key/RSA/";
    LWEDir = workingDir+"/Key/LWE/";
    BlissDir = workingDir+"/Key/Bliss/";
    certiDir = workingDir+"/Key/Certi/";
    logDir = workingDir+"/Log/";


    // setup files
    profile = workingDir+"/Config/profile";

#if DEBUG
    qDebug()<<workingDir;
    qDebug()<<tmpDir;
    qDebug()<<aesDir;
    qDebug()<<rsaDir;
    qDebug()<<certiDir;
    qDebug()<<profile;
    qDebug()<<logDir;
#endif

}
