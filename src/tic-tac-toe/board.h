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
        PlayerX = 'X',
        PlayerO = 'O',
        NoPlayer = ' '
    };
    static const uint DIFFICULTY_MAX = 100;
    static const uint DIFFICULTY_MIN = 1;

    Board(uint difficulty = DIFFICULTY_MIN);

    void AddMove(Location loc, Symbol symbol);
    bool HasWon(Symbol symbol) const;
    bool MoveAllowed(Location location) const;
    std::vector<Location> GetFreeCells() const;
    Symbol GetSymbolInCell(Location location) const;
    uint difficulty;

private:
    static const int NUMBER_OF_CELLS = 9;

    // Board states storing each player's symbol where they played
    // Element indices as per tic tac toe map or as per Location enum:
    // 0 | 1 | 2
    // ––––––––––
    // 3 | 4 | 5
    // ––––––––––
    // 6 | 7 | 8
    std::vector<Symbol> board;

};

#endif // BOARD_H
