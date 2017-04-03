#ifndef UTIL
#define UTIL

#include <QDesktopWidget>
#include <QApplication>
#include <QTextStream>
#include <QFile>
namespace util{

void centerize(QWidget* window);
void windowSetup(QWidget* window);
bool contains(QString newKeyName, QString KeyInfoFileName);
void deleteOneline(int RowNum, QString &fileContent);
void deleteOnelineInFile(int RowNum, QString filename);
void writeMessageToFile(QString message, QString fileName,bool currentDir = true);
void appendMessageToFile(QString message, QString fileName, bool newLine = true, bool currentDir = true);
void deleteRecords(QString& name, bool self = true);
}



#endif
