/********************************************************************************
** Form generated from reading UI file 'dialogNewGame.ui'
**
** Created: Sun Sep 8 02:08:57 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGNEWGAME_H
#define UI_DIALOGNEWGAME_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QLabel>

QT_BEGIN_NAMESPACE

class Ui_DialogNewGame
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *DialogNewGame)
    {
        if (DialogNewGame->objectName().isEmpty())
            DialogNewGame->setObjectName(QString::fromUtf8("DialogNewGame"));
        DialogNewGame->resize(480, 133);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/x.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        DialogNewGame->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(DialogNewGame);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(120, 90, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(DialogNewGame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 17, 431, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Century Schoolbook"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(DialogNewGame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 451, 31));
        label_2->setFont(font);

        retranslateUi(DialogNewGame);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogNewGame, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogNewGame, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogNewGame);
    } // setupUi

    void retranslateUi(QDialog *DialogNewGame)
    {
        DialogNewGame->setWindowTitle(QApplication::translate("DialogNewGame", "Game Over", 0));
        label->setText(QApplication::translate("DialogNewGame", "Text", 0));
        label_2->setText(QApplication::translate("DialogNewGame", "Do you want start new game or exit?", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogNewGame: public Ui_DialogNewGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGNEWGAME_H
