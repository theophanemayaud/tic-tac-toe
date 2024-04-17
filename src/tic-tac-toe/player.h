#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "board.h"

class Player : public QObject
{
    Q_OBJECT

signals:
    void moveReady(uint move); // emitted when player has chosen his next move

public:
    Player(char moveSymbol, bool manualPlayer, uint difficulty);

    void startNextMove(const char* board); // call when it is the player's turn, then listen for moveReady signal

    const char moveSymbol; // symbol that corresponds to the player on the board
    const bool manualPlayer; // true if player is in manual ie 'human' mode

    void receiveManualMove(uint move); // receive moves from the human user

private:
    const int WIN_GAIN = 10;
    bool awaitingMove = false;

    const char* board; // TODO refactor as separate class
    const uint difficulty;

    uint getBotMove() const;
    int getGainOfMove(Board board, Board::Location moveLoc, Board::Symbol moveSymbol, bool maximize = true);
};

#endif // PLAYER_H
