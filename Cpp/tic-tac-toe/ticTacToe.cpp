#include "ticTacToe.h"
#include "ui_ticTacToe.h"
#include "dialogNewGame.h"

#include <iostream>
using namespace std;

#include <QMessageBox>
#include <QDialog>
#include <QHBoxLayout>

TicTacToe::TicTacToe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToe),
    activePlayer(Xs)
{
    ui->setupUi(this);
    smButtons =  new QSignalMapper;
    buttons = new QPushButton**[row];
    game = new TicTacToeGame(row, col);

    for (int i = 0; i < row; ++i)
    {
        buttons[i] = new QPushButton*[col];
        for (int j = 0; j < col; ++j)
        {
            buttons[i][j] = new QPushButton;
            buttons[i][j]->setGeometry(0, 0, 100, 100);
            buttons[i][j]->setIconSize(QSize(100, 100));
            QHBoxLayout *tempLayout = new QHBoxLayout;
            tempLayout->addWidget(buttons[i][j]);
            ui->gridLayout->addLayout(tempLayout, i, j);
        }

    }

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            connect(buttons[i][j], SIGNAL(clicked()), smButtons, SLOT(map()));
            smButtons->setMapping(buttons[i][j], 10 * (i + 1) + j + 1);
        }
    }

    connect(smButtons, SIGNAL(mapped(int)), this, SLOT(clicked(int)));
    connect(ui->actionNew_game_2, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(ui->actionExit_2, SIGNAL(triggered()), this, SLOT(menuExit()));

    startNewGame();
}

TicTacToe::~TicTacToe()
{
    delete ui;
    delete smButtons;
    delete game;
    for (int i = 0; i < row; ++i)
    {
        delete[] buttons[i];
    }
    delete[] buttons;
}

void TicTacToe::startNewGame()
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            buttons[i][j]->setIcon(QIcon(":/white.jpg"));
        }
    }
    game->clear();
    activePlayer = Xs;
}

void TicTacToe::changePlayer()
{
    activePlayer = (activePlayer == Xs) ? Os : Xs;
}

void TicTacToe::checkEndGame()
{
    if (game->isGameFinish())
    {
        congratulateWinner(game->getWinner());
    }
}

void TicTacToe::congratulateWinner(Player winner)
{
    if (winner == Xs)
    {
        showEndGameDialog("Congratulate winner player Xs!");
    }
    else if (winner == Os)
    {
        showEndGameDialog("Congratulate winner player Os!");
    }
    else
    {
        showEndGameDialog("There is draw!");
    }
}

void TicTacToe::showEndGameDialog(const QString &text)
{
    DialogNewGame *dialog = new DialogNewGame(this, text);
    if (dialog->exec() == DialogNewGame::Accepted)
    {
        startNewGame();
    }
    else
    {
        menuExit();
    }
    delete dialog;
}

void TicTacToe::clicked(int idButton)
{
    int ii = idButton / 10 - 1;
    int jj = idButton % 10 - 1;
    if (game->isTaken(ii, jj))
    {
        return;
    }
    game->addMove(ii, jj, activePlayer);
    if (activePlayer == Xs)
    {
        buttons[ii][jj]->setIcon(QIcon(":/x.jpg"));
    }
    else
    {
        buttons[ii][jj]->setIcon(QIcon(":/zero.jpg"));
    }
    //buttons[ii][jj]->setEnabled(false);
    changePlayer();
    checkEndGame();
}

void TicTacToe::menuExit()
{
    this->close();
}

