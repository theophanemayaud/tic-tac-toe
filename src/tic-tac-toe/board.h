#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{

public:
    enum class Location : int {
        TopLeft = 0,
        TopMiddle = 1,
        TopRight = 2,
        MiddleLeft = 3,
        MiddleMiddle = 4,
        MiddleRight = 5,
        BottomLeft = 6,
        BottomMiddle = 7,
        BottomRight = 8
    };

    enum class Symbol : char {
        Player1 = 'X',
        Player2 = 'O',
        NoPlayer = ' '
    };

    Board();

    std::vector<Symbol> const& cells(){ return this->board; }

    void AddMove(Location loc, Symbol symbol);
    bool HasWon(Symbol symbol);

private:
    const int NUMBER_OF_CELLS = 9;

    std::vector<Symbol> board;
};

#endif // BOARD_H
