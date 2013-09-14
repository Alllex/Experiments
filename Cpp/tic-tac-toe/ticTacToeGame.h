#pragma once

enum Player
{
    nobody,
    Os,
    Xs
};

class TicTacToeGame
{
public:
    TicTacToeGame(const int countRow, const int countCol);
    ~TicTacToeGame();
    void clear();
    void addMove(const int x, const int y, Player player);
    bool isGameFinish();
    Player getWinner();
    bool isTaken(const int x, const int y);

private:
    int rows;
    int cols;
    Player winner;
    Player **situation;
    int countMoves;

    void rotateMatrix();
    void printMatrix();
};
