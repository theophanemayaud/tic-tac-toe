#ifndef BOARD_H
#define BOARD_H

#include <vector>

// Tic tac toe board holding the game logic
// like possible moves and current game state
class Board
{

public:
        // Element indices as per tic tac toe map or as per Location enum:
        // 0 | 1 | 2
        // ––––––––––
        // 3 | 4 | 5
        // ––––––––––
        // 6 | 7 | 8
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

    static const uint DIFFICULTY_MAX = 100; // hard game
    static const uint DIFFICULTY_MIN = 1; // easy game

    Board(uint difficulty = DIFFICULTY_MIN);

    uint difficulty; // Game difficulty in terms of how difficult the game should be

    void AddMove(Location loc, Symbol symbol);
    bool HasWon(Symbol symbol) const; // indicates if the player of given symbol has won the game
    bool MoveAllowed(Location location) const;
    std::vector<Location> GetFreeCells() const;
    Symbol GetSymbolInCell(Location location) const;

private:
    static const int NUMBER_OF_CELLS = 9;

    // Board states storing each player's symbol where they played
    std::vector<Symbol> board;
};

#endif // BOARD_H
