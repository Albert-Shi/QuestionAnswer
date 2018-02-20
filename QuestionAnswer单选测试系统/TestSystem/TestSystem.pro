#-------------------------------------------------
#
# Project created by QtCreator 2016-06-06T16:00:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    questioninput.cpp \
    adminlogin.cpp \
    questionlist.cpp \
    answerui.cpp \
    settingquantity.cpp

HEADERS  += mainwindow.h \
    core.h \
    questioninput.h \
    adminlogin.h \
    questionlist.h \
    answerui.h \
    global.h \
    settingquantity.h

FORMS    += mainwindow.ui \
    questioninput.ui \
    adminlogin.ui \
    questionlist.ui \
    answerui.ui \
    settingquantity.ui

DISTFILES +=

RC_FILE = icon.rc

QMAKE_CXXFLAGS_RELEASE += -g

QMAKE_CFLAGS_RELEASE += -g

QMAKE_LFLAGS_RELEASE = -mthreads -W

RESOURCES += \
    images.qrc
