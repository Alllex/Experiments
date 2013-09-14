#pragma once

#include <QDialog>

namespace Ui {
class DialogNewGame;
}

class DialogNewGame : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNewGame(QWidget *parent = 0);
    DialogNewGame(QWidget *parent = 0, const QString &message = "");
    ~DialogNewGame();
    
private:
    Ui::DialogNewGame *ui;
};
