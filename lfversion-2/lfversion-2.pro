#-------------------------------------------------
#
# Project created by QtCreator 2017-03-26T15:03:12
#
#-------------------------------------------------

QT       += core gui

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
    util.cpp

HEADERS  += mainwindow.h \
    util.h \
    ui-showwidget.h \
    ui-createcertiwindow.h \
    ui-createkeywindow.h \
    ui-decryptfilewindow.h \
    ui-encryptfilewindow.h \
    aeshandler.h

FORMS    +=

CONFIG += c++11

RESOURCES += \
    icon.qrc

LIBS+=-L/usr/lib/  -lcryptopp

INCLUDEPATH += /usr/include/cryptopp
