

#include "util.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>


void util::centerize(QWidget* window)
{
    QDesktopWidget* d = QApplication::desktop();
    window->move((d->width()-window->width())/2, (d->height()-window->height())/2);
}

void util::windowSetup(QWidget* window)
{
    window->setAttribute(Qt::WA_DeleteOnClose);
    centerize(window);
    window->show();
}


void util::writeMessageToFile(QString message, QString fileName, bool currentDir)
{
    if(currentDir) fileName = QApplication::applicationDirPath()+"/"+fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<message;
    out.flush();
    file.close();;


}

void util::appendMessageToFile(QString message, QString fileName, bool newLine,bool currentDir)
{
    if(currentDir) fileName = QApplication::applicationDirPath()+"/"+fileName;
    QFile file(fileName);
    file.open(QIODevice::Append|QIODevice::Text);
    QTextStream out(&file);
    out<<message<<"\n";
    out.flush();
    file.close();
}

bool util::contains(QString newKeyName, QString KeyInfoFileName){
    QFile *keyInfo=new QFile(QCoreApplication::applicationDirPath()+"/Key/"+KeyInfoFileName);
    keyInfo->open(QIODevice::ReadOnly | QIODevice::Text);
    QString keyInfoStr=keyInfo->readAll();
    keyInfo->close();

    if(keyInfoStr.lastIndexOf(newKeyName)>=0){
        return true;
    }
    return false;
}

//如果是5行，RowNum最大为4
void util::deleteOneline(int RowNum, QString &fileContent)//
{
    int nLine=0;
    int Index=0;
    //算出行数nLine
    while(Index!=-1)
    {
        Index=fileContent.indexOf('\n',Index+1);
        nLine++;
    }

    //如果是直接从位置0开始删除\n算一个字符"abc\nme\ndo" \n的index是3要删除3+1个字符，即index+1个
    if(RowNum==0)
    {
        int nIndex=fileContent.indexOf('\n');
        fileContent.remove(0,nIndex+1);
    }
    else
    {
        int nTemp=RowNum;
        int nIndex=0,nIndex2=0;
        while(nTemp--)
        {
            //
            nIndex=fileContent.indexOf('\n',nIndex+1);//这里会更新nIndex
            if(nIndex!=-1)//说明是有效的
            {
                nIndex2=fileContent.indexOf('\n',nIndex+1);
            }
        }
        //删除的行不是最后一行（从nIndex+1这个位置起nIndex2-nIndex个字符全部抹去）
        if(RowNum<nLine-1)
        {
            fileContent.remove(nIndex+1, nIndex2-nIndex);//不用减一
        }
        //删除的是最后一行（从nIndex起始len-nIndex个字符全抹去）
        //不能从nIndex+1处开始，
        else if(RowNum==nLine-1)
        {
            int len=fileContent.length();
            fileContent.remove(nIndex,len-nIndex);
        }
        else
        {

        }

    }
}
void util::deleteOnelineInFile(int RowNum, QString filename)
{
    QString fileContent;
    QFile readfile(filename);
    if(readfile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&readfile);
        fileContent=stream.readAll();
    }
    readfile.close();
    deleteOneline(RowNum, fileContent);

    QFile writefile(filename);
    if(writefile.open(QIODevice::WriteOnly))
    {
        QTextStream wrtstream(&writefile);
        wrtstream<<fileContent;
    }
    writefile.close();
}

void util::deleteCerti(QString& name, bool self)
{
    // remove rsa key files
    QDir RSADir(QApplication::applicationDirPath()+"/Key/RSA");
    QStringList fileNames = RSADir.entryList();
    for(QString fileName:fileNames)
    {
        if(fileName.endsWith(name))
        {
         //   qDebug()<<fileName;
            RSADir.remove(fileName);
        }

    }

    // remove cer file
    QDir cerDir(QApplication::applicationDirPath()+"/Key/Certi");
    fileNames.clear();
    fileNames = cerDir.entryList();
    for(QString fileName:fileNames)
    {
        if(fileName.startsWith(name))
        {
           // qDebug()<<fileName;
            cerDir.remove(fileName);
        }
    }


    // remove record from metadata file

    QString metaDataFileName=QApplication::applicationDirPath()+"/Key/";
    if(self)
    {
        metaDataFileName += "mykey";
    }
    else
    {
        metaDataFileName += "pubkey";
    }
    QFile metaDataFile(metaDataFileName);
    metaDataFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&metaDataFile);
    QStringList records;
    while(!stream.atEnd())
    {
        records.append(stream.readLine());
    }
    metaDataFile.close();

    metaDataFile.open(QIODevice::WriteOnly|QIODevice::Text);
    for(QString record : records)
    {
        if(record.startsWith(name)) continue;
        stream<<record<<"\n";
    }
}




