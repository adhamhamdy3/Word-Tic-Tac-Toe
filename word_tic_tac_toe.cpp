#include "word_tic_tac_toe.h"
#include "./ui_word_tic_tac_toe.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QtVirtualKeyboard>

Word_Tic_Tac_Toe::Word_Tic_Tac_Toe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Word_Tic_Tac_Toe)
{
    ui->setupUi(this);

    player1 = true;
    player2 = false;

    nonHumanPlayer = false;
    gameOver = false;

    Board = new Word_TicTacToe_Board<char>();

    getPlayerInfo();
}

Word_Tic_Tac_Toe::~Word_Tic_Tac_Toe()
{
    delete ui;

    if (players[0]) delete players[0];
    if (players[1]) delete players[1];
    if (Board) delete Board;

    delete W_TTT_GAME;
}

void Word_Tic_Tac_Toe::getPlayerInfo(){
    QString player1Name = QInputDialog::getText(this, "Player 1 Name", "Enter Player 1 name:", QLineEdit::Normal, "Player 1");
    if(player1Name.isEmpty()) player1Name = "Player1";

    QChar player1Symbol = getSymbol("X");

    players[0] = new W_TTT_Player<char>(player1Name.toStdString(), player1Symbol.toLatin1());

    QMessageBox msgBox(this);

    msgBox.setText("Choose your opponent type:");
    // QPushButton* aiButton = msgBox.addButton("AI Player", QMessageBox::ActionRole);
    // QPushButton* randomButton = msgBox.addButton("Random Computer Player", QMessageBox::ActionRole);
    QPushButton* realButton = msgBox.addButton("Real Player", QMessageBox::ActionRole);

    msgBox.exec();

    QChar player2Symbol;

    /*if (msgBox.clickedButton() == aiButton) {
        player2Symbol = getSymbol("O");
        players[1] = new P_TTT_AI_Player<char>(player2Symbol.toLatin1());
        players[1]->setBoard(Board);
        nonHumanPlayerMode = true;
    } else if (msgBox.clickedButton() == randomButton) {
        player2Symbol = getSymbol("O");
        players[1] = new P_TTT_Random_Player<char>(player2Symbol.toLatin1());
        nonHumanPlayerMode = true;
    } else */if (msgBox.clickedButton() == realButton) {
        QString player2Name = QInputDialog::getText(this, "Player 2 Name", "Enter Player 2 name:", QLineEdit::Normal, "Player 2");
        if (player2Name.isEmpty()) player2Name = "Player 2";

        player2Symbol = getSymbol("O");

        players[1] = new W_TTT_Player<char>(player2Name.toStdString(), player2Symbol.toLatin1());
    }

    ui->name1Label->setText("Name: " + QString::fromStdString(players[0]->getname()));
    ui->mark1Label->setText("Mark: " + QString::fromStdString(string(1, players[0]->getsymbol())));

    ui->name2Label->setText("Name: " + QString::fromStdString(players[1]->getname()));
    ui->mark2Label->setText("Mark: " + QString::fromStdString(string(1, players[1]->getsymbol())));
}

QChar Word_Tic_Tac_Toe::getSymbol(const QString& defaultSymbol){
    QChar playerSymbol;
    while (true) {
        QString symbolInput = QInputDialog::getText(this, "Player 1 Symbol", "Enter Player 1 symbol (one character):", QLineEdit::Normal, defaultSymbol);
        if (symbolInput.size() == 1 && !symbolInput.at(0).isSpace()) {
            playerSymbol = symbolInput.at(0);
            break;
        } else {
            QMessageBox::warning(this, "Invalid Input", "Player 1 symbol must be a single non-whitespace character.");
        }
    }
    return playerSymbol;
}

void Word_Tic_Tac_Toe::on_W_TTT_Grid_cellDoubleClicked(int row, int column)
{
    int currentRow = row;
    int currentColumn = column;

    // Open the touch keyboard dialog
    TouchKeyboardDialog *keyboardDialog = new TouchKeyboardDialog(this);
    connect(keyboardDialog, &TouchKeyboardDialog::characterSelected, this, [=](QChar character) {
        updateCellCharacter(row, column, character);
    });

    keyboardDialog->exec(); // Show the dialog modally



}

void Word_Tic_Tac_Toe::updateCellCharacter(int row, int column, QChar character) {
    // Update the cell with the selected character
    ui->W_TTT_Grid->setItem(row, column, new QTableWidgetItem(character));
}

