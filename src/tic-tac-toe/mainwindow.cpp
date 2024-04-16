#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlePlayerMove(uint move)
{
    disconnect(currentPlayer, nullptr, this, nullptr); // disconnect further calls from current player as they have made their move
    qDebug() << "Handle move :" << move;

    this->boardStates[move] = this->currentPlayer->moveSymbol;

    if(playerWon(boardStates, currentPlayer->moveSymbol)){
        updateBoardDisplay(boardStates, this->currentPlayer->manualPlayer);
        this->setWindowTitle(
            this->currentPlayer->manualPlayer
                ? "You won !"
                : "You lost..."
            );
        return; // user must now reset game
    }

    this->currentPlayer = currentPlayer == player1
                            ? player2
                            : player1;
    updateBoardDisplay(this->boardStates, this->currentPlayer->manualPlayer);

    QObject::connect(currentPlayer, &Player::moveReady, this, &MainWindow::handlePlayerMove);
    currentPlayer->startNextMove(this->boardStates);
}

// ------------------------------
// BEGIN : private functions
void MainWindow::updateBoardDisplay(const char board[9], bool manualPlayer)
{
    ui->map1->setText(QString(board[0]));
    ui->map2->setText(QString(board[1]));
    ui->map3->setText(QString(board[2]));
    ui->map4->setText(QString(board[3]));
    ui->map5->setText(QString(board[4]));
    ui->map6->setText(QString(board[5]));
    ui->map7->setText(QString(board[6]));
    ui->map8->setText(QString(board[7]));
    ui->map9->setText(QString(board[8]));

    this->setWindowTitle(
        manualPlayer
            ? "Your move !"
            : "Computer is thinking..."
        );
}

bool MainWindow::playerWon(const char board[9], const char playerSymbol)
{
    if(    // horizontal lines
           (board[0] == playerSymbol && board[1] == playerSymbol && board[2] == playerSymbol)
        || (board[3] == playerSymbol && board[4] == playerSymbol && board[5] == playerSymbol)
        || (board[6] == playerSymbol && board[7] == playerSymbol && board[8] == playerSymbol)
        // vertical lines
        || (board[0] == playerSymbol && board[3] == playerSymbol && board[6] == playerSymbol)
        || (board[1] == playerSymbol && board[4] == playerSymbol && board[7] == playerSymbol)
        || (board[2] == playerSymbol && board[5] == playerSymbol && board[8] == playerSymbol)
        // diagonal lines
        || (board[0] == playerSymbol && board[4] == playerSymbol && board[8] == playerSymbol)
        || (board[2] == playerSymbol && board[4] == playerSymbol && board[6] == playerSymbol)
        )
        return true;

    return false;
}

// END : private functions
// ------------------------------

// ------------------------------
// BEGIN: UI slots -------------

void MainWindow::on_start_clicked()
{
    this->ui->stacked->setCurrentIndex(1);

    const bool humanPlaysFirst = this->ui->playFirst->isChecked();
    this->player1 = new Player('X', true);
    this->player2 = new Player('O', false);
    this->currentPlayer = humanPlaysFirst
        ? player1
        : player2;

    // SETUP BOARD
    std::fill_n(this->boardStates, sizeof(this->boardStates), ' ');
    updateBoardDisplay(this->boardStates, this->currentPlayer->manualPlayer);

    // START FIRST MOVE
    QObject::connect(currentPlayer, &Player::moveReady, this, &MainWindow::handlePlayerMove);
    currentPlayer->startNextMove(boardStates);
}

void MainWindow::on_restartButton_clicked()
{
    // TODO free players
    this->ui->stacked->setCurrentIndex(0);
}

void MainWindow::manualMoveClicked(uint move)
{
    currentPlayer->receiveManualMove(move);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->ui->difficulty->setNum(value+1);
}

// END: UI slots -------------
// ---------------

