#-------------------------------------------------
#
# Project created by QtCreator 2013-02-01T15:54:00
#
#-------------------------------------------------

QT       += core gui

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qrcode_clock
TEMPLATE = app

LIBS += -lqrencode

SOURCES += main.cpp\
        qrcode_clock.cpp \
    qrlabel.cpp

HEADERS  += qrcode_clock.h \
    qrlabel.h

FORMS    += qrcode_clock.ui
