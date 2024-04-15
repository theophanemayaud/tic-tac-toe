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

// ---------------
// BEGIN: UI slots -------------

void MainWindow::on_start_clicked()
{
    this->ui->stacked->setCurrentIndex(1);

    const bool humanPlaysFirst = this->ui->playFirst->isChecked();
    this->player1 = new Player('X', humanPlaysFirst);
    this->player2 = new Player('O', !humanPlaysFirst);
    this->currentPlayer = humanPlaysFirst
        ? player1
        : player2;

    // RESET BOARD
    ui->map1->setText(" ");
    ui->map2->setText(" ");
    ui->map3->setText(" ");
    ui->map4->setText(" ");
    ui->map5->setText(" ");
    ui->map6->setText(" ");
    ui->map7->setText(" ");
    ui->map8->setText(" ");


    // START FIRST MOVE
    this->setWindowTitle(
        currentPlayer->manualPlayer
            ? "Your move !"
            : "Computer is thinking"
    );

    QObject::connect(currentPlayer, &Player::moveReady, this, &MainWindow::handlePlayerMove);
    currentPlayer->startNextMove(boardStates);
}

void MainWindow::on_restartButton_clicked()
{
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

