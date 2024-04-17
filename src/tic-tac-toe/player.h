#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "board.h"

// Tic tac toe player
// Contains the player strategy and behavior while playing the game
class Player : public QObject
{
    Q_OBJECT

signals:
    void MoveReady(Board::Location location); // emitted when player has chosen his next move

public:
    Player(Board::Symbol moveSymbol, bool manualPlayer);

    void StartNextMove(Board board); // call when it is the player's turn, then listen for moveReady signal

    const Board::Symbol moveSymbol; // symbol that corresponds to the player on the board
    const bool manualPlayer; // true if player is in manual ie 'human' mode

    void ReceiveManualMove(Board::Location location); // receive moves from the human user

private:
    // wheight of a winning move when evaluating all possible options
    // must be greater than the number of total possible options
    // as the gain is decreased on each move to make moves
    // that lead to a faster victory have a bigger gain
    static const int WIN_GAIN = 15;

    Board board;

    // Gets the move chosen by an automatic algorithm
    // This depends on the board difficulty from random to perfect player
    // Choices between equally good moves are randomized to make the game more varied
    Board::Location getBotMove() const;

    // Calculates the max/min (depending on the player being simulated)
    // possible gain of a given move,
    // enabling by recursive use the calculation along all
    // branches of the game state tree to evaluate which move(s) is/are best at every step
    static int getGainOfMove(Board board, Board::Location moveLoc, Board::Symbol moveSymbol, bool isMainPlayer);
};

#endif // PLAYER_H
