#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T23:31:03
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSServerApp
TEMPLATE = app


SOURCES += main.cpp \
    ui/mainwindow.cpp \
    src/server.cpp \
    src/clientthread.cpp \
    src/userlistmodel.cpp

HEADERS  += \
    ui/mainwindow.h \
    src/server.h \
    src/clientthread.h \
    src/userlistmodel.h
