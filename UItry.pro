#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T19:52:26
#
#-------------------------------------------------

QT       += core gui
QT      +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UItry
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    start.cpp \
    game.cpp \
    result.cpp \
    introduction.cpp \
    setting.cpp \
    viewpainter.cpp \
    logic/game_logic.cpp \
    logic/game_map.cpp

HEADERS += \
        mainwindow.h \
    start.h \
    game.h \
    result.h \
    introduction.h \
    setting.h \
    viewpainter.h \
    logic/game_logic.h \
    logic/game_map.h

FORMS += \
        mainwindow.ui \
    start.ui \
    game.ui \
    result.ui \
    introduction.ui \
    setting.ui

RESOURCES += \
    image.qrc \
    sound.qrc


DISTFILES += \


