#include "player.h"

#include <QTimer>
#include <QRandomGenerator>

Player::Player(char moveSymbol, bool manualPlayer)
    : moveSymbol(moveSymbol), manualPlayer(manualPlayer)
{

}

void Player::startNextMove(const char *board)
{
    this->board = board;

    if(this->manualPlayer)
        return; // in manual mode we just wait until user chooses a move

    uint chosenMove = getBotMove();
    QTimer::singleShot(1000, this, [this, chosenMove](){emit this->moveReady(chosenMove);});
}

void Player::receiveManualMove(uint move)
{
    if(this->manualPlayer && this->board[move] == ' ')
        emit moveReady(move);
}

uint Player::getBotMove() const
{
    std::multimap<int, uint> gainOfPossibleMoves;
    for (uint i = 0; i < 9; ++i) { // TODO Refactor board as class to avoid 9 magic number
        if(board[i] == ' '){
            gainOfPossibleMoves.insert({10, i});
        }
    }

    auto possibleBestMove = gainOfPossibleMoves.crbegin();
    const uint nbEqualBestMoves = gainOfPossibleMoves.count(possibleBestMove->first);

    std::advance(possibleBestMove, QRandomGenerator::global()->bounded((uint)0,(uint)nbEqualBestMoves-1));

    // TODO randomize based on difficulty

    return possibleBestMove->second;
}

