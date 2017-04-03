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
}



#endif
