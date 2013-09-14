#-------------------------------------------------
#
# Project created by QtCreator 2013-01-01T23:51:47
#
#-------------------------------------------------

QT       += core gui

TARGET = CashWatcher
TEMPLATE = app


SOURCES += main.cpp\
        mainMenu.cpp \
    tester.cpp \
    architecture/manager/cash.cpp \
    architecture/manager/account.cpp \
    architecture/manager/accountDescription.cpp \
    architecture/manager/accountHistory.cpp \
    architecture/manager/accountOperation.cpp \
    architecture/manager/manager.cpp \
    architecture/user.cpp \
    architecture/auxiliary/time.cpp

HEADERS  += mainMenu.h \
    tester.h \
    architecture/manager/cash.h \
    architecture/manager/account.h \
    architecture/manager/accountDescription.h \
    architecture/manager/accountHistory.h \
    architecture/manager/accountOperation.h \
    architecture/manager/manager.h \
    architecture/user.h \
    architecture/auxiliary/time.h

FORMS    += mainMenu.ui

OTHER_FILES += \
    logs/alllex/accounts.log
