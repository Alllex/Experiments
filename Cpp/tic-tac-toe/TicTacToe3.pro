#-------------------------------------------------
#
# Project created by QtCreator 2012-11-07T17:52:33
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacToe3
TEMPLATE = app


SOURCES += main.cpp\
        ticTacToe.cpp \
    ticTacToeGame.cpp \
    dialogNewGame.cpp

HEADERS  += ticTacToe.h \
    ticTacToeGame.h \
    dialogNewGame.h

FORMS    += ticTacToe.ui \
    dialogNewGame.ui

RESOURCES += \
    imageResourse.qrc
