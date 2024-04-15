#include "player.h"

Player::Player(char moveSymbol, bool manualPlayer)
    : moveSymbol(moveSymbol), manualPlayer(manualPlayer)
{

}

void Player::startNextMove(const char board[9])
{
    this->board = board;
    this->awaitingMove = true;

    // TODO if auto player, get next move
}

void Player::receiveManualMove(uint move)
{
    if(this->manualPlayer && this->awaitingMove && this->board[move] == ' ')
        emit this->moveReady(move);
}
