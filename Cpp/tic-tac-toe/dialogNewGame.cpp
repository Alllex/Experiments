#include "dialogNewGame.h"
#include "ui_dialogNewGame.h"

DialogNewGame::DialogNewGame(QWidget *parent):
    QDialog(parent),
    ui(new Ui::DialogNewGame)
{
    ui->setupUi(this);
}

DialogNewGame::DialogNewGame(QWidget *parent, const QString &message):
    QDialog(parent),
    ui(new Ui::DialogNewGame)
{
    ui->setupUi(this);
    ui->label->setText(message);
}

DialogNewGame::~DialogNewGame()
{
    delete ui;
}
