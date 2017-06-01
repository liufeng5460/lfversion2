#include "netaction.h"
#include "status.h"
#include "util.h"

#include "ui-inputusernamedialog.h"


#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>


#define DEBUG 0


// about info
QString Status::appName("集成加密软件");

// user info
map<QString,QString> Status::conf;

// object pointer
ShowWidgetUI* Status::showWidget(nullptr);
MainWindow* Status::mainWindow(nullptr);
NetAction* Status::server;

// web info
string Status::plainText("");
string Status::cipherText("");
int Status::waitTime = 10000;

// path info
 QString Status::workingDir("");
 QString Status::tmpDir("");
QString Status::aesDir("");
 QString Status::rsaDir("");
 QString Status::LWEDir("");
 QString Status::BlissDir("");
 QString Status::certiDir("");

 QString Status::logDir("");
 QString Status::keyDir;
 QString Status::configDir;
 QString Status::fileDir;

 // file info
  QString Status::profile;
 QString Status::selfCertiInfo;
 QString Status::othersCertiInfo;
QString Status::contact;
QString Status::sendFileRecord;
QString Status::receiveFileRecord;


 void Status::init()
 {
     updatePaths();
     checkDirs();
     config();
      server = new NetAction;
 }


 void Status::config()
 {

     /* config items
      * user info
      */

     QFile profileFile(Status::profile);
     if(profileFile.exists())
     {
         profileFile.open(QIODevice::ReadOnly|QIODevice::Text);
         QTextStream in(&profileFile);
         while(!in.atEnd())
         {
            QString line = in.readLine();
            if(line.isEmpty())
            {
                break;
            }
            QStringList pairs =line.split(":");
            conf[pairs.at(0).trimmed()] = pairs.at(1).trimmed();
         }
         profileFile.close();
     }
     else
     {
         util::dialogSetup(new InputUsernameDialog);
     }
     if(conf["port"].isEmpty())
     {
         conf["port"] = "5460";
     }



     // for contact file
    QFile contactFile(contact);
    if(!contactFile.exists())
    {
        contactFile.open(QIODevice::WriteOnly|QIODevice::Text);
        contactFile.write(QString("username,ip\n").toStdString().c_str());
        contactFile.close();
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

    appDir = QApplication::applicationDirPath();

    // setup directories
    workingDir = appDir;
    tmpDir = workingDir +"/Tmp/";
    logDir = workingDir +"/Log/";
    keyDir = workingDir +"/Key/";
    aesDir = workingDir +"/Key/AES/";
    rsaDir = workingDir +"/Key/RSA/";
    LWEDir = workingDir +"/Key/LWE/";
    BlissDir = workingDir+"/Key/Bliss/";
    certiDir = workingDir+"/Key/Certi/";
    configDir = workingDir+"/Config/";
    fileDir = tmpDir;

    // setup files
    profile = configDir+"profile";
    selfCertiInfo = keyDir+"mykey";
    othersCertiInfo = keyDir+"pubkey";
    contact = configDir+"contact";
    sendFileRecord = logDir+"SendFileRecord";
    receiveFileRecord = logDir+"ReceiveFileRecord";
}
