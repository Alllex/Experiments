#include <QGuiApplication>
#include "mainMenu.h"

#include "tester.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainMenu w;
    //w.show();
    Tester tester;
    tester.run();
    //return a.exec();
    return 0;
}
