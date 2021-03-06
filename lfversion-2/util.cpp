
#include "status.h"
#include "util.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>


void util::centerize(QWidget* window)
{
    QDesktopWidget* d = QApplication::desktop();
    window->move((d->width()-window->width())/2, (d->height()-window->height())/2);
}

void util::dialogSetup(QWidget* window)
{
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setWindowModality(Qt::WindowModality::ApplicationModal);
    window->show();
    centerize(window);
    window->setFixedSize(window->size());

}


void util::writeMessageToFile(QString message, QString fileName, bool currentDir)
{
    if(currentDir) fileName = QApplication::applicationDirPath()+"/"+fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<message;
    out.flush();
    file.close();
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
    // remove bliss key files
    QDir  blissDir(Status::BlissDir);
    QStringList fileNames = blissDir.entryList();
    for(QString fileName : fileNames)
    {
        if(fileName.contains(name))
        {
         //   qDebug()<<fileName;
            blissDir.remove(fileName);
        }

    }

    // remove cer file
    QDir cerDir(Status::certiDir);
    fileNames.clear();
    fileNames = cerDir.entryList();
    for(QString fileName:fileNames)
    {
        if(fileName.contains(name))
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
        if(record.contains(name)) continue;
        stream<<record<<"\n";
    }
}

QString util::arrayToString(long *a, int length, QString sep, bool newLine)
{
    if(a==nullptr) return "";
    QByteArray result;
    QTextStream out(&result,QIODevice::WriteOnly);
    for(int i=0; i<length; i++)
    {
        out<<a[i];
        if(!sep.isEmpty())
        {
            out<<sep;
        }
    }
    if(newLine)
    {
        out<<"\n";
    }
    out.flush();
    return QString(result);
}

void  util::addContact(const QString &name, const QString &ip)
{
    QFile contactFile(Status::contact);
    contactFile.open(QIODevice::Append | QIODevice::Text);
    QString message = name;
    if(!ip.isEmpty())
    {
        message += ","+ip;
    }
    message+="\n";
    contactFile.write(message.toStdString().c_str());

    contactFile.close();
}

void util::appendIp(const QString &name, const QString &ip)
{
    QFile contactFile(Status::contact);
    contactFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&contactFile);
    QStringList recordsList;
    QString metaData= in.readLine();
    while(!in.atEnd())
    {
        recordsList.append(in.readLine());
    }
    contactFile.close();

    for(int i=0;i<recordsList.size(); i++)
    {
        if(name == recordsList[i])
        {
            if(!recordsList[i].contains(ip))
            {
                recordsList[i]+=","+ip;
            }
        }
    }

    contactFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&contactFile);
    out<<metaData<<"\n";
    for(QString record: recordsList)
    {
        out<<record<<"\n";
    }
    contactFile.close();
}

void util::getContact(QStringList &nameList, QStringList &ipList)
{
    QFile contactFile(Status::contact);
    contactFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in(&contactFile);
    in.readLine();
    QString line;
    QString name;
    QString ip;
    while(!in.atEnd())
    {
        line = in.readLine();
        int firstSep = line.indexOf(",");
        if(firstSep != -1)
        {
            name = line.left(firstSep);
            nameList.append(name);
            ip = line.right(line.size()-firstSep-1);
            ipList.append(ip);
        }
        else
        {
            nameList.append(line);
        }
    }
    contactFile.close();
}

void util::appendSendFileRecord(const QString &name, const QString &ip, const QString &filePath)
{
    QFile theFile(Status::sendFileRecord);
    if(theFile.exists())
    {
        theFile.open(QIODevice::Append | QIODevice::Text);
    }
    else
    {
        theFile.open(QIODevice::WriteOnly |QIODevice::Text);
    }
    QString record;
    record +=filePath   +","
            +name       +","
            +ip         +","
            +QDateTime::currentDateTime().toString("yyyy-M-d H:m:s")+"\n";
    theFile.write(record.toStdString().c_str());
    theFile.close();
}

void util::appendReceiveFileRecord(const QString& name, const QString& ip, const QString& filePath)
{
    QFile theFile(Status::receiveFileRecord);
    if(theFile.exists())
    {
        theFile.open(QIODevice::Append | QIODevice::Text);
    }
    else
    {
        theFile.open(QIODevice::WriteOnly |QIODevice::Text);
    }
    QString record;
    record += filePath +","
            + name      +","
            + ip        +","
            + QDateTime::currentDateTime().toString("yyyy-M-d H:m:s")+"\n";
    theFile.write(record.toStdString().c_str());
    theFile.close();
}

void util::writeConf()
{
    QFile profile(Status::profile);
//    qDebug()<<Status::profile;
    profile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&profile);

    for(auto it = Status::conf.begin(); it!=Status::conf.end(); it++)
    {
        if(it->first == "listenning") continue;
        out<<it->first
          <<":"
         <<it->second
        <<"\n";
    }

    profile.close();
}
