#ifndef UTIL
#define UTIL

#include <QDesktopWidget>
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QStringList>
namespace util{

void centerize(QWidget* window);
void dialogSetup(QWidget* window);
bool contains(QString newKeyName, QString KeyInfoFileName);
void deleteOneline(int RowNum, QString &fileContent);
void deleteOnelineInFile(int RowNum, QString filename);
void writeMessageToFile(QString message, QString fileName,bool currentDir = true);
void appendMessageToFile(QString message, QString fileName, bool newLine = true, bool currentDir = true);
void deleteCerti(QString& name, bool self = true);
QString arrayToString(long* a,int length, QString sep=" ", bool newLine = true);

// for config/contact file
void addContact(const QString& name, const QString& ip="");
void appendIp(const QString& name, const QString& ip);
void getContact(QStringList& nameList,QStringList& ipList);
}



#endif
