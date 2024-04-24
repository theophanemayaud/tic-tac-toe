#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// Tic tac toe game UI with settings first page and board display second page
// Uses the board and player logic, to refresh the UI when game state changes
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void HandlePlayerMove(Board::Location location);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_start_clicked();

    void on_restartButton_clicked();

    void on_map1_clicked() { manualMoveClicked(Board::Location::TopLeft); };
    void on_map2_clicked() { manualMoveClicked(Board::Location::TopMiddle); };
    void on_map3_clicked() { manualMoveClicked(Board::Location::TopRight); };
    void on_map4_clicked() { manualMoveClicked(Board::Location::MiddleLeft); };
    void on_map5_clicked() { manualMoveClicked(Board::Location::MiddleMiddle); };
    void on_map6_clicked() { manualMoveClicked(Board::Location::MiddleRight); };
    void on_map7_clicked() { manualMoveClicked(Board::Location::BottomLeft); };
    void on_map8_clicked() { manualMoveClicked(Board::Location::BottomMiddle); };
    void on_map9_clicked() { manualMoveClicked(Board::Location::BottomRight); };

private:
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    Player* currentPlayer;

    Board board = Board();

    void manualMoveClicked(Board::Location location);

    void updateDisplay();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
