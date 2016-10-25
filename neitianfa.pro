#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T11:20:15
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport    # for qcustomplot use

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = neitianfa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nei_onepage.cpp \
    nei_result.cpp \
    nei_bottom.cpp \
    nei_login.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    nei_onepage.h \
    nei_result.h \
    nei_bottom.h \
    nei_common.h \
    nei_login.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    nei_onepage.ui \
    nei_result.ui \
    nei_bottom.ui \
    nei_login.ui

RESOURCES += \
    nei_resource.qrc
