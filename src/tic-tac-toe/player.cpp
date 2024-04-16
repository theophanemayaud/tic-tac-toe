#include "player.h"

#include <QTimer>

Player::Player(char moveSymbol, bool manualPlayer)
    : moveSymbol(moveSymbol), manualPlayer(manualPlayer)
{

}

void Player::startNextMove(const char board[9])
{
    this->board = board;

    if(this->manualPlayer)
        return; // in manual mode we just wait until user chooses a move

    // TODO auto player, get next move
    for (uint i = 0; i < sizeof(board); ++i) {
        if(board[i] == ' '){
            QTimer::singleShot(1, this, [this, i](){emit this->moveReady(i);});
            return;
        }
    }
}

void Player::receiveManualMove(uint move)
{
    if(this->manualPlayer && this->board[move] == ' ')
        emit moveReady(move);
}
