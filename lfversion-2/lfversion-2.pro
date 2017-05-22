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
    mylwe.cpp \
    mybliss.cpp \
    ui/digitalsig.cpp \
    ui/aboutdialog.cpp \
    ui/setupdialog.cpp

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
    mylwe.h \
    mybliss.h \
    ui/digitalsig.h \
    ui/aboutdialog.h \
    ui/setupdialog.h

FORMS    +=

CONFIG += c++11

RESOURCES += \
    icon.qrc

LIBS+=-L/home/ydu/code/qt/lfversion2/lfversion-2/lib
LIBS+=-L/usr/lib/
LIBS+=-L/usr/lib/x86_64-linux-gnu



LIBS += -lcryptopp
LIBS += -lLWEEnc
LIBS += -lBliss
LIBS += -lssl
LIBS += -lmpfr
LIBS += -lgmpxx
LIBS += -lgmp
LIBS += -lcrypto
LIBS += -lntl
LIBS += -lEntropy

INCLUDEPATH += /usr/include/
INCLUDEPATH += /usr/include/Entropy
INCLUDEPATH += /usr/include/LWE
INCLUDEPATH += /usr/include/Bliss
INCLUDEPATH += /usr/include/NTL
INCLUDEPATH += /usr/include/openssl
