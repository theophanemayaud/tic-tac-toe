#include "player.h"

#include <QTimer>
#include <QRandomGenerator>

Player::Player(char moveSymbol, bool manualPlayer, uint difficulty)
    : moveSymbol(moveSymbol), manualPlayer(manualPlayer), difficulty(difficulty)
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

    uint chosenMove = possibleBestMove->second;

    // difficulties are from 1 to 100
    // we make the bot choose a random move instead of the optimal move
    // when a random number between 1 and 100 > the difficulty
    // Thus if the difficulty is at
    //      100 we always choose the optimal move
    //      50 we choose the optimal move only half the time
    //      1 we only choose randomly
    if(QRandomGenerator::global()->bounded(1,100) > this->difficulty){
        auto possibleRandomMove = gainOfPossibleMoves.cbegin();
        std::advance(possibleRandomMove, QRandomGenerator::global()->bounded((uint)1,(uint)(gainOfPossibleMoves.size()-1)));
        chosenMove = possibleRandomMove->second;
    }

    return chosenMove;
}

