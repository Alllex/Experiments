#include "ticTacToeGame.h"
#include <algorithm>
#include <iostream>
using std::swap;
using std::cout;
using std::endl;

TicTacToeGame::TicTacToeGame(const int countRow, const int countCol): rows(countRow),
    cols(countCol), winner(nobody), countMoves(0)
{
    situation = new Player*[rows];
    for (int i = 0; i < rows; ++i)
    {
        situation[i] = new Player[cols];
    }
    clear();
}

TicTacToeGame::~TicTacToeGame()
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] situation[i];
    }
    delete[] situation;
}

void TicTacToeGame::clear()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            situation[i][j] = nobody;
        }
    }
    winner = nobody;
    countMoves = 0;
}

void TicTacToeGame::addMove(const int x, const int y, Player player)
{
    situation[x][y] = player;
    countMoves++;
}

bool TicTacToeGame::isGameFinish()
{
    bool result = false;
    for (int idRotate = 0; idRotate < 4; ++idRotate)
    {
        bool equalUp = true;
        bool equalCentral = true;
        bool equalDiagonal = true;
        for (int i = 1; i < cols; ++i)
        {
            Player main = situation[0][0];
            if (main == nobody || main != situation[0][i])
            {
                equalUp = false;
            }
            if (main == nobody || main != situation[i][i])
            {
                equalDiagonal = false;
            }
            if (situation[1][0] == nobody || situation[1][0] != situation[1][i])
            {
                equalCentral = false;
            }
        }
        if (equalUp || equalDiagonal)
        {
            winner = situation[0][0];
            result = true;
        }
        else if (equalCentral)
        {
            winner = situation[1][0];
            result = true;
        }
        //printMatrix();
        rotateMatrix();
    }
    if (!result && countMoves == rows * cols)
    {
        winner = nobody;
        return true;
    }
    return result;
}

Player TicTacToeGame::getWinner()
{
    return winner;
}

bool TicTacToeGame::isTaken(const int x, const int y)
{
    return situation[x][y] != nobody;
}

void TicTacToeGame::rotateMatrix()
{
    swap(situation[0][0], situation[0][2]);
    swap(situation[2][0], situation[2][2]);
    swap(situation[0][0], situation[2][2]);

    swap(situation[1][0], situation[0][1]);
    swap(situation[2][1], situation[1][2]);
    swap(situation[1][0], situation[1][2]);
}

void TicTacToeGame::printMatrix()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << " " << situation[i][j];
        }
        cout << endl;
    }
}
