#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H

#include <QMainWindow>
#include "BoardGame_Classes.h"
#include "Word_TicTacToe.h"
#include "touchkeyboarddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Word_Tic_Tac_Toe;
}
QT_END_NAMESPACE

class Word_Tic_Tac_Toe : public QMainWindow
{
    Q_OBJECT

public:
    Word_Tic_Tac_Toe(QWidget *parent = nullptr);
    ~Word_Tic_Tac_Toe();

private slots:
    void on_W_TTT_Grid_cellDoubleClicked(int row, int column);

private:
    Ui::Word_Tic_Tac_Toe *ui;
    Player<char>* players[2];
    Word_TicTacToe_Board<char>* Board;
    GameManager<char>* W_TTT_GAME;

private:
    bool player1, player2;

    bool nonHumanPlayer;
    bool gameOver;

    void getPlayerInfo();
    QChar getSymbol(const QString&);

    void updateCellCharacter(int row, int column, QChar character);
};
#endif // WORD_TIC_TAC_TOE_H
