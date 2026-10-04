#pragma once
#include "Cell.h"
#include "Config.h"

// интерфейс игрового поля

class Board {
public:
    Board();                     // = resetGame()

    void reset();

    // взаимодействие
    void open(int row, int col);
    void toggleFlag(int row, int col);
    bool isMine(int row, int col) const;

    bool checkVictory() const;
    bool inBounds(int row, int col) const;

    const Cell& at(int row, int col) const { return field[row][col]; }

private:
    void placeMines();
    int  countMinesAround(int row, int col) const;
    void openRecursive(int row, int col);

    Cell field[cfg::SIZE][cfg::SIZE];
};