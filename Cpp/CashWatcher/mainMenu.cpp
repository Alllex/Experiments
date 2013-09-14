#include "mainMenu.h"
#include "ui_mainMenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

}

MainMenu::~MainMenu()
{
    delete ui;
}
