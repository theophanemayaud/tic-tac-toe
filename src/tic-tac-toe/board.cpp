#include "board.h"

Board::Board(uint difficulty) :
    board {
        Symbol::NoPlayer,
        Symbol::NoPlayer,
        Symbol::NoPlayer,
        Symbol::NoPlayer,
        Symbol::NoPlayer,
        Symbol::NoPlayer,
        Symbol::NoPlayer,
        Symbol::NoPlayer,
        Symbol::NoPlayer
    },
    difficulty(difficulty)
{
    for (int i = 0; i < NUMBER_OF_CELLS; ++i) {
        this->board.push_back(Symbol::NoPlayer);
    }
}

void Board::AddMove(Location loc, Symbol symbol){
    if(!MoveAllowed(loc))
        throw "FORBIDDEN: Attempted to move to already filled cell";

    this->board[(int)loc] = symbol;
}

bool Board::HasWon(Symbol symbol) const
{
    if(    // horizontal lines
           (board[(int)Location::TopLeft] == symbol && board[(int)Location::TopMiddle] == symbol && board[(int)Location::TopRight] == symbol)
        || (board[(int)Location::MiddleLeft] == symbol && board[(int)Location::MiddleMiddle] == symbol && board[(int)Location::MiddleRight] == symbol)
        || (board[(int)Location::BottomLeft] == symbol && board[(int)Location::BottomMiddle] == symbol && board[(int)Location::BottomRight] == symbol)
        // vertical lines
        || (board[(int)Location::TopLeft] == symbol && board[(int)Location::MiddleLeft] == symbol && board[(int)Location::BottomLeft] == symbol)
        || (board[(int)Location::TopMiddle] == symbol && board[(int)Location::MiddleMiddle] == symbol && board[(int)Location::BottomMiddle] == symbol)
        || (board[(int)Location::TopRight] == symbol && board[(int)Location::MiddleRight] == symbol && board[(int)Location::BottomRight] == symbol)
        // diagonal lines
        || (board[(int)Location::TopLeft] == symbol && board[(int)Location::MiddleMiddle] == symbol && board[(int)Location::BottomRight] == symbol)
        || (board[(int)Location::BottomLeft] == symbol && board[(int)Location::MiddleMiddle] == symbol && board[(int)Location::TopRight] == symbol)
        )
        return true;

    return false;
}

bool Board::MoveAllowed(Location location) const
{
    if(this->board[(int)location] == Symbol::NoPlayer)
        return true;

    return false;
}

std::vector<Board::Location> Board::GetFreeCells() const
{
    std::vector<Board::Location> freeCells;
    for (int i = 0; i < NUMBER_OF_CELLS; ++i) {
        if(this->board[i] == Symbol::NoPlayer)
            freeCells.push_back((Board::Location)i);
    }
    return freeCells;
}

Board::Symbol Board::GetSymbolInCell(Board::Location location) const
{
    return this->board[(int)location];
}


