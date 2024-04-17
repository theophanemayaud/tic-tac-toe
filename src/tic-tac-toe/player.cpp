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
        gainOfPossibleMoves.insert({getGainOfMove(this->board, freeCell, this->moveSymbol, true), freeCell});
    }

    // we choose randomly between any of the best moves ie equal gain
    auto possibleBestMove = gainOfPossibleMoves.crbegin();
    const uint nbEqualBestMoves = gainOfPossibleMoves.count(possibleBestMove->first);

    if(nbEqualBestMoves>1)
        std::advance(possibleBestMove, QRandomGenerator::global()->bounded((uint)0,(uint)nbEqualBestMoves-1));

    Board::Location chosenMove = possibleBestMove->second;

    // difficulties are from 1 to 100
    // we make the bot choose a random move instead of the optimal move
    // when a random number between 1 and 100 > the difficulty
    // Eg if the difficulty is at
    //      100 we always choose the optimal move
    //      50 we choose the optimal move only half the time
    //      1 we only choose randomly
    if(QRandomGenerator::global()->bounded(Board::DIFFICULTY_MIN,Board::DIFFICULTY_MAX) > this->board.difficulty){
        auto possibleRandomMove = gainOfPossibleMoves.cbegin();
        uint chosenRandomMoveIndex = QRandomGenerator::global()->bounded((uint)0,(uint)(gainOfPossibleMoves.size()-1));
        std::advance(possibleRandomMove, chosenRandomMoveIndex);
        chosenMove = possibleRandomMove->second;
        qDebug() << "Performed random move";
    }

    return chosenMove;
}

int Player::getGainOfMove(Board board, Board::Location moveLoc, Board::Symbol moveSymbol, bool isMainPlayer)
{
    board.AddMove(moveLoc, moveSymbol);
    if(board.HasWon(moveSymbol))
        return isMainPlayer ? WIN_GAIN : -WIN_GAIN;
    if(board.GetFreeCells().empty())
        return 0; // subtract 1 to make draw be of lesser gain than victory

    // evaluate sub moves that the opponent could take in answer to evaluate the worst case scenario
    std::multimap<int, Board::Location> gainOfPossibleMoves;
    const auto opponentSymbol = moveSymbol == Board::Symbol::PlayerX ? Board::Symbol::PlayerO : Board::Symbol::PlayerX;

    for(auto freeCell : board.GetFreeCells()) {
        gainOfPossibleMoves.insert({getGainOfMove(board, freeCell, opponentSymbol, !isMainPlayer), freeCell});
    }
    if(isMainPlayer) {
        return gainOfPossibleMoves.cbegin()->first -1; // take first ie highest gain. The main player knows that the adversary will make the move resulting in lowest gain
    }
    else {
        return gainOfPossibleMoves.crbegin()->first -1; // take last ie lowest gain: subtract 1 at each recursion to make best/highest gain move also the one with least turns
    }
}


