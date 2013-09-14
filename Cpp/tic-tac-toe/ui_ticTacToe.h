/********************************************************************************
** Form generated from reading UI file 'ticTacToe.ui'
**
** Created: Fri 9. Nov 10:34:51 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICTACTOE_H
#define UI_TICTACTOE_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_TicTacToe
{
public:
    QAction *actionNew_game;
    QAction *actionExit;
    QAction *actionNew_game_2;
    QAction *actionExit_2;
    QAction *actionHuman_vs_Human;
    QAction *actionHuman_vs_Computer;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuSettings;

    void setupUi(QMainWindow *TicTacToe)
    {
        if (TicTacToe->objectName().isEmpty())
            TicTacToe->setObjectName(QString::fromUtf8("TicTacToe"));
        TicTacToe->setWindowModality(Qt::NonModal);
        TicTacToe->resize(325, 350);
        TicTacToe->setMinimumSize(QSize(325, 350));
        TicTacToe->setMaximumSize(QSize(325, 350));
        TicTacToe->setBaseSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/x.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        TicTacToe->setWindowIcon(icon);
        TicTacToe->setToolButtonStyle(Qt::ToolButtonTextOnly);
        actionNew_game = new QAction(TicTacToe);
        actionNew_game->setObjectName(QString::fromUtf8("actionNew_game"));
        actionExit = new QAction(TicTacToe);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionNew_game_2 = new QAction(TicTacToe);
        actionNew_game_2->setObjectName(QString::fromUtf8("actionNew_game_2"));
        actionExit_2 = new QAction(TicTacToe);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        actionHuman_vs_Human = new QAction(TicTacToe);
        actionHuman_vs_Human->setObjectName(QString::fromUtf8("actionHuman_vs_Human"));
        actionHuman_vs_Human->setCheckable(true);
        actionHuman_vs_Human->setChecked(true);
        actionHuman_vs_Human->setEnabled(false);
        actionHuman_vs_Computer = new QAction(TicTacToe);
        actionHuman_vs_Computer->setObjectName(QString::fromUtf8("actionHuman_vs_Computer"));
        actionHuman_vs_Computer->setEnabled(false);
        centralWidget = new QWidget(TicTacToe);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        TicTacToe->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TicTacToe);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 325, 21));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        TicTacToe->setMenuBar(menuBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuMenu->addAction(actionNew_game_2);
        menuMenu->addAction(actionExit_2);
        menuSettings->addAction(actionHuman_vs_Human);
        menuSettings->addAction(actionHuman_vs_Computer);

        retranslateUi(TicTacToe);

        QMetaObject::connectSlotsByName(TicTacToe);
    } // setupUi

    void retranslateUi(QMainWindow *TicTacToe)
    {
        TicTacToe->setWindowTitle(QApplication::translate("TicTacToe", "TicTacToe", 0));
        actionNew_game->setText(QApplication::translate("TicTacToe", "New game", 0));
        actionExit->setText(QApplication::translate("TicTacToe", "Exit", 0));
        actionNew_game_2->setText(QApplication::translate("TicTacToe", "New game", 0));
        actionExit_2->setText(QApplication::translate("TicTacToe", "Exit", 0));
        actionHuman_vs_Human->setText(QApplication::translate("TicTacToe", "Human vs. Human", 0));
        actionHuman_vs_Computer->setText(QApplication::translate("TicTacToe", "Human vs. Computer", 0));
        menuMenu->setTitle(QApplication::translate("TicTacToe", "Menu", 0));
        menuSettings->setTitle(QApplication::translate("TicTacToe", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class TicTacToe: public Ui_TicTacToe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICTACTOE_H
