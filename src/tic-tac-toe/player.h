#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "board.h"

class Player : public QObject
{
    Q_OBJECT

signals:
    void moveReady(Board::Location location); // emitted when player has chosen his next move

public:
    Player(Board::Symbol moveSymbol, bool manualPlayer);

    void startNextMove(Board board); // call when it is the player's turn, then listen for moveReady signal

    const Board::Symbol moveSymbol; // symbol that corresponds to the player on the board
    const bool manualPlayer; // true if player is in manual ie 'human' mode

    void receiveManualMove(Board::Location location); // receive moves from the human user

private:
    static const int WIN_GAIN = 10;
    bool awaitingMove = false;

    Board board; // TODO refactor as separate class

    Board::Location getBotMove() const;
    static int getGainOfMove(Board board, Board::Location moveLoc, Board::Symbol moveSymbol, bool maximize = true);
};

#endif // PLAYER_H
