#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->difficulty->setNum(static_cast<int>(this->board.difficulty));
    ui->horizontalSlider->setSliderPosition(static_cast<int>(this->board.difficulty)-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandlePlayerMove(Board::Location location)
{
    disconnect(currentPlayer, nullptr, this, nullptr); // disconnect further calls from current player as they have made their move
    qDebug() << "Handle move :" << (int)location;

    this->board.AddMove(location, this->currentPlayer->moveSymbol);

    QString endMessage;
    if(this->board.HasWon(currentPlayer->moveSymbol))
        endMessage = this->currentPlayer->manualPlayer ? "You won !" : "You lost...";
    else if(this->board.GetFreeCells().empty())
        endMessage = "It's a tie !";
    if(!endMessage.isEmpty()){
        updateDisplay();
        this->setWindowTitle(endMessage);
        return; // user must now reset game
    }

    this->currentPlayer = currentPlayer == player1
                            ? player2
                            : player1;
    updateDisplay();

    QObject::connect(currentPlayer, &Player::MoveReady, this, &MainWindow::HandlePlayerMove);
    currentPlayer->StartNextMove(this->board);
}

// ------------------------------
// BEGIN : private functions
void MainWindow::updateDisplay()
{
    ui->map1->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::TopLeft))));
    ui->map2->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::TopMiddle))));
    ui->map3->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::TopRight))));
    ui->map4->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::MiddleLeft))));
    ui->map5->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::MiddleMiddle))));
    ui->map6->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::MiddleRight))));
    ui->map7->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::BottomLeft))));
    ui->map8->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::BottomMiddle))));
    ui->map9->setText(QString(static_cast<char>(this->board.GetSymbolInCell(Board::Location::BottomRight))));

    this->setWindowTitle(
        this->currentPlayer->manualPlayer
            ? "Your move ! (You play " + QString(static_cast<char>(this->currentPlayer->moveSymbol)) + ")"
            : "Computer is thinking... (Computer plays " + QString(static_cast<char>(this->currentPlayer->moveSymbol)) + ")"
        );
}

// END : private functions
// ------------------------------

// ------------------------------
// BEGIN: UI slots -------------

void MainWindow::on_start_clicked()
{
    this->ui->stacked->setCurrentIndex(1);

    const bool humanPlaysFirst = this->ui->playFirst->isChecked();

    delete this->player1; delete this->player2;
    this->player1 = new Player(Board::Symbol::PlayerX, true);
    this->player2 = new Player(Board::Symbol::PlayerO, false);
    this->currentPlayer = humanPlaysFirst
        ? player1
        : player2;

    // SETUP UI BOARD
    this->board = Board(this->ui->horizontalSlider->value()+1);
    updateDisplay();

    // START FIRST MOVE
    QObject::connect(currentPlayer, &Player::MoveReady, this, &MainWindow::HandlePlayerMove);
    currentPlayer->StartNextMove(board);
}

void MainWindow::on_restartButton_clicked()
{
    this->ui->stacked->setCurrentIndex(0);
}

void MainWindow::manualMoveClicked(Board::Location location)
{
    currentPlayer->ReceiveManualMove(location);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->ui->difficulty->setNum(value+1);
    this->board.difficulty = value+1;
}

// END: UI slots -------------
// ---------------
