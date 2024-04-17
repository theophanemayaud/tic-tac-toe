#include "board.h"

Board::Board() :
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
    }
{
    for (int i = 0; i < NUMBER_OF_CELLS; ++i) {
        board.push_back(Symbol::NoPlayer);
    }
}

void Board::AddMove(Location loc, Symbol symbol){
    if(this->board[(int)loc] != Symbol::NoPlayer)
        throw "FORBIDDEN: Attempted to move to already filled cell";

    this->board[(int)loc] = symbol;
}

bool Board::HasWon(Symbol symbol){
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
