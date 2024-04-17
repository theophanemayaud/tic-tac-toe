#include "player.h"
#include "QtCore/qdebug.h"

#include <QTimer>
#include <QRandomGenerator>

Player::Player(Board::Symbol moveSymbol, bool manualPlayer)
    : moveSymbol(moveSymbol), manualPlayer(manualPlayer)
{

}

void Player::startNextMove(Board board)
{
    this->board = board;

    if(this->manualPlayer)
        return; // in manual mode we just wait until user chooses a move

    Board::Location chosenMove = getBotMove();
    QTimer::singleShot(1000, this, [this, chosenMove](){emit this->moveReady(chosenMove);});
}

void Player::receiveManualMove(Board::Location location)
{
    if(this->manualPlayer && this->board.MoveAllowed(location))
        emit moveReady(location);
}

Board::Location Player::getBotMove() const
{
    std::multimap<int, Board::Location> gainOfPossibleMoves;
    for (auto freeCell : this->board.GetFreeCells()) {
        gainOfPossibleMoves.insert({getGainOfMove(this->board, freeCell, this->moveSymbol), freeCell});
    }

    auto possibleBestMove = gainOfPossibleMoves.crbegin();
    const uint nbEqualBestMoves = gainOfPossibleMoves.count(possibleBestMove->first);

    std::advance(possibleBestMove, QRandomGenerator::global()->bounded((uint)0,(uint)nbEqualBestMoves-1));

    Board::Location chosenMove = possibleBestMove->second;

    // difficulties are from 1 to 100
    // we make the bot choose a random move instead of the optimal move
    // when a random number between 1 and 100 > the difficulty
    // Thus if the difficulty is at
    //      100 we always choose the optimal move
    //      50 we choose the optimal move only half the time
    //      1 we only choose randomly
    if(QRandomGenerator::global()->bounded(1,100) > this->board.difficulty){
        auto possibleRandomMove = gainOfPossibleMoves.cbegin();
        std::advance(possibleRandomMove, QRandomGenerator::global()->bounded((uint)1,(uint)(gainOfPossibleMoves.size()-1)));
        chosenMove = possibleRandomMove->second;
        qDebug() << "Performed random move";
    }

    return chosenMove;
}

int Player::getGainOfMove(Board board, Board::Location moveLoc, Board::Symbol moveSymbol, bool maximize)
{
    board.AddMove(moveLoc, moveSymbol);
    if(board.HasWon(moveSymbol))
        return WIN_GAIN;

    for (auto freeCell : board.GetFreeCells()) {
        if(maximize) {
        }
        else {
        }
    }
    return WIN_GAIN;

}


