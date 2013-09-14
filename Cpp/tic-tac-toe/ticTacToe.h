#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>

#include "ticTacToeGame.h"

namespace Ui {
class TicTacToe;
}

class TicTacToe : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TicTacToe(QWidget *parent = 0);
    ~TicTacToe();
    
private:
    static const int col = 3;
    static const int row = 3;
    Ui::TicTacToe *ui;
    QPushButton ***buttons;
    QSignalMapper *smButtons;
    TicTacToeGame *game;
    Player activePlayer;

    void changePlayer();
    void checkEndGame();
    void congratulateWinner(Player winner);
    void showEndGameDialog(const QString &text);

private slots:
    void clicked(int idButton);
    void menuExit();
    void startNewGame();
};
