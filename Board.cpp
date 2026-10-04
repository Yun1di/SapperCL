#include "Board.h"
#include <cstdlib>
#include <ctime>

// реализация интерфейса игрового поля 

Board::Board() {
    static bool seeded = false;
    if (!seeded) 
    { std::srand(std::time(nullptr)); 
        seeded = true; 
    }
    reset();
}

void Board::reset() {
    for (int i = 0; i < cfg::SIZE; ++i)
        for (int j = 0; j < cfg::SIZE; ++j)
            field[i][j] = Cell{};

    placeMines();

    for (int i = 0; i < cfg::SIZE; ++i)
        for (int j = 0; j < cfg::SIZE; ++j)
            if (!field[i][j].mine)
                field[i][j].minesAround = countMinesAround(i, j);
}

void Board::placeMines() {
    int placed = 0;
    while (placed < cfg::MINES) 
    {
        int r = std::rand() % cfg::SIZE;
        int c = std::rand() % cfg::SIZE;
        if (!field[r][c].mine) 
        {
            field[r][c].mine = true;
            ++placed;
        }
    }
}

int Board::countMinesAround(int row, int col) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j) 
        {
            if (i == 0 && j == 0) 
                continue;
            int r = row + i, c = col + j;
            if (inBounds(r, c) && field[r][c].mine) 
                ++count;
        }
    return count;
}

bool Board::inBounds(int row, int col) const {
    return row >= 0 && row < cfg::SIZE && col >= 0 && col < cfg::SIZE;
}

void Board::open(int row, int col) {
    if (!inBounds(row, col))       return;
    if (field[row][col].opened)    return;
    if (field[row][col].flagged)   return;
    if (field[row][col].mine)      return;   // мину не открываем (Game сам решит проигрыш)
    openRecursive(row, col);
}

void Board::openRecursive(int row, int col) {
    if (!inBounds(row, col))     return;
    if (field[row][col].opened)  return;
    if (field[row][col].flagged) return;
    if (field[row][col].mine)    return;

    field[row][col].opened = true;

    if (field[row][col].minesAround > 0) return;

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j) 
        {
            if (i == 0 && j == 0) 
                continue;
            openRecursive(row + i, col + j);
        }
}

void Board::toggleFlag(int row, int col) {
    if (!inBounds(row, col))    return;
    if (field[row][col].opened) return;
    field[row][col].flagged = !field[row][col].flagged;
}

bool Board::isMine(int row, int col) const {
    return inBounds(row, col) && field[row][col].mine;
}

bool Board::checkVictory() const {
    for (int i = 0; i < cfg::SIZE; ++i)
        for (int j = 0; j < cfg::SIZE; ++j)
            if (!field[i][j].mine && !field[i][j].opened)
                return false;
    return true;
}