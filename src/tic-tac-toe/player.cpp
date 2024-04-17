#include "player.h"
#include "QtCore/qdebug.h"

#include <QTimer>
#include <QRandomGenerator>

Player::Player(Board::Symbol moveSymbol, bool manualPlayer)
    : moveSymbol(moveSymbol), manualPlayer(manualPlayer)
{

}

void Player::StartNextMove(Board board)
{
    this->board = board;

    if(this->manualPlayer)
        return; // in manual mode we just wait until user chooses a move

    Board::Location chosenMove = getBotMove();
    // small timer for simulating that the bot is "thinking" even though calculations are very fast
    QTimer::singleShot(1000, this, [this, chosenMove](){emit this->MoveReady(chosenMove);});
}

void Player::ReceiveManualMove(Board::Location location)
{
    if(this->manualPlayer && this->board.MoveAllowed(location))
        emit MoveReady(location);
}

Board::Location Player::getBotMove() const
{
    // first we calculate how likely each available move is to result
    // in the bot winning, ie the "gain" of the move
    std::multimap<int, Board::Location> gainOfPossibleMoves;
    for (auto freeCell : this->board.GetFreeCells()) {
        gainOfPossibleMoves.insert({getGainOfMove(this->board, freeCell, this->moveSymbol, true), freeCell});
    }

    // we choose randomly between any of the best moves ie equal gain, to make the game varied
    auto possibleBestMove = gainOfPossibleMoves.crbegin();
    const uint nbEqualBestMoves = gainOfPossibleMoves.count(possibleBestMove->first);

    if(nbEqualBestMoves>1)
        std::advance(possibleBestMove, QRandomGenerator::global()->bounded((uint)0, (uint)nbEqualBestMoves));

    Board::Location chosenMove = possibleBestMove->second;

    // we make the bot choose a random move instead of the optimal move depending on the difficulty
    // when the random number surpasses the difficulty, the choice is made random
    // Eg if the difficulty is between 1 and 100 we generate a random number within thos bounds, thus
    //      with difficulty set to 100 we always choose the optimal move
    //      with difficulty set to 50 we choose the optimal move only half the time
    //      with difficulty set to 1 we only choose randomly
    if(QRandomGenerator::global()->bounded(Board::DIFFICULTY_MIN,Board::DIFFICULTY_MAX) > this->board.difficulty){
        auto possibleRandomMove = gainOfPossibleMoves.cbegin();
        const uint nbRandomMoves = gainOfPossibleMoves.size();
        uint chosenRandomMoveIndex = QRandomGenerator::global()->bounded((uint)0, (uint)(nbRandomMoves));
        if(chosenRandomMoveIndex>1)
            std::advance(possibleRandomMove, chosenRandomMoveIndex);
        chosenMove = possibleRandomMove->second;
        qDebug() << "Bot chose move at random";
    }

    return chosenMove;
}

int Player::getGainOfMove(Board board, Board::Location moveLoc, Board::Symbol moveSymbol, bool isMainPlayer)
{
    // first we check if the move ends the game and return the appropriate gain depending on who is being simulated
    board.AddMove(moveLoc, moveSymbol);
    if(board.HasWon(moveSymbol))
        return isMainPlayer ? WIN_GAIN : -WIN_GAIN; // the gain is the point of view of the main player, ie negative when the opponent wins
    if(board.GetFreeCells().empty())
        return 0; // draw is of lesser gain than victory and higher gain than loss (as per point of view of main player)

    // otherwise we evaluate all sub moves that the opponent could take after the evaluated player's current move,
    // to evaluate the worst case following scenario and return the gain from that scenario

    // sorted multimap for accessing easily highest/lowest gain move afterwards
    std::multimap<int, Board::Location> gainOfPossibleOpponentMoves;

    const auto opponentSymbol = moveSymbol == Board::Symbol::PlayerX ? Board::Symbol::PlayerO : Board::Symbol::PlayerX;

    for(auto freeCell : board.GetFreeCells()) {
        gainOfPossibleOpponentMoves.insert({getGainOfMove(board, freeCell, opponentSymbol, !isMainPlayer), freeCell});
    }
    if(isMainPlayer) {
        // The main player is simulated,
        // and we have evaluated the gains of all subsequent moves the opponent/adversary could take
        // The adversary will logically make the move resulting in lowest gain for the main player, so we assumes such
        // Therefore we return the first ie lowest gain value as we can assume this to be our current move gain
        // NB We subtract 1 at each recursion to make best/highest gain move also the one with least turns
        return gainOfPossibleOpponentMoves.cbegin()->first -1;
    }
    else {
        // The adversary to the main player is simulated,
        // and we have evaluated the gains of all subsequent moves the opponent/main player could take
        // The main player will logically make the move resulting in highest gain for the adversary, so we assumes such
        // Therefore we return the last ie highest gain value as we can assume this to be the current move gain
        // NB We subtract 1 at each recursion to make best/highest gain move also the one with least turns
        return gainOfPossibleOpponentMoves.crbegin()->first -1;
    }
}


