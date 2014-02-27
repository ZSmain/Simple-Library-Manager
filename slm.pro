#-------------------------------------------------
#
# Project created by QtCreator 2013-12-29T15:37:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gestionDeBibliotheque
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    member.cpp \
    book.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    member.h \
    book.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    Resources.qrc
