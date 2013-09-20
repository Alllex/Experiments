#include <QApplication>
#include "ticTacToe.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToe w;
    w.show();
    return a.exec();
}
