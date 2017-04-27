#-------------------------------------------------
#
# Project created by QtCreator 2017-03-26T15:03:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lfversion-2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ui-showwidget.cpp \
    ui-createcertiwindow.cpp \
    ui-createkeywindow.cpp \
    ui-decryptfilewindow.cpp \
    ui-encryptfilewindow.cpp \
    util.cpp \
    myaes.cpp \
    myrsa.cpp \
    ui-sendfilewindow.cpp \
    netaction.cpp \
    status.cpp \
    ui-inputusernamedialog.cpp \
    mylwe.cpp

HEADERS  += mainwindow.h \
    util.h \
    ui-showwidget.h \
    ui-createcertiwindow.h \
    ui-createkeywindow.h \
    ui-decryptfilewindow.h \
    ui-encryptfilewindow.h \
    myaes.h \
    myrsa.h \
    ui-sendfilewindow.h \
    netaction.h \
    status.h \
    ui-inputusernamedialog.h \
    mylwe.h

FORMS    +=

CONFIG += c++11

RESOURCES += \
    icon.qrc

LIBS+=-L/home/ydu/code/qt/lfversion2/lfversion-2/lib -L/usr/lib/ -L/usr/lib/x86_64-linux-gnu -lcryptopp -lLWEEnc -lBlissSig -lntl -lssl -lmpfr
INCLUDEPATH += /home/ydu/code/qt/lfversion2/lfversion-2/include
INCLUDEPATH += /usr/include/
INCLUDEPATH += /usr/include/NTL
INCLUDEPATH += /usr/include/openssl
INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /home/ydu/code/qt/lfversion2/lfversion-2/include

LIBS +=-L/usr/lib/x86_64-linux-gnu/ -lmpfr
LIBS +=-L/usr/lib/x86_64-linux-gnu/ -lgmpxx
LIBS +=-L/usr/lib/x86_64-linux-gnu/ -lgmp
LIBS +=-L/usr/lib/x86_64-linux-gnu/ -lcrypto
LIBS +=-L/usr/lib/ -lntl


INCLUDEPATH += /usr/include/cryptopp /usr/include/LWE /usr/include/BlissSig /usr/include/openssl
