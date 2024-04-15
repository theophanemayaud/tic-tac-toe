#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handlePlayerMove(uint move);

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_start_clicked();

    void on_restartButton_clicked();

    void on_map1_clicked() { manualMoveClicked(1); }; // TODO do this in code by connecting signals
    void on_map2_clicked() { manualMoveClicked(2); };
    void on_map3_clicked() { manualMoveClicked(3); };
    void on_map4_clicked() { manualMoveClicked(4); };
    void on_map5_clicked() { manualMoveClicked(5); };
    void on_map6_clicked() { manualMoveClicked(6); };
    void on_map7_clicked() { manualMoveClicked(7); };
    void on_map8_clicked() { manualMoveClicked(8); };
    void on_map9_clicked() { manualMoveClicked(9); };

private:
    void manualMoveClicked(uint move);

    Player *player1;
    char player1Symbol = 'X';
    Player *player2;
    char player2Symbol = 'O';

    Player *currentPlayer;

    // Array of board states storing each player's symbol where they played
    // Element indices as per tic tac toe map :
    // 0 | 1 | 2
    // ––––––––––
    // 3 | 4 | 5
    // ––––––––––
    // 6 | 7 | 8
    char boardStates[9];

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
