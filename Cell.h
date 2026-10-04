#pragma once

// типы данных

struct Cell {
    bool mine        = false; // мина 
    bool opened      = false; // открытая клетка
    bool flagged     = false; // флаг
    int  minesAround = 0;     // кол-во мин вокруг
};

enum class GameState {
    Playing,        // процесс игры
    GameOver,       //проигрышь
    Win             //выигрышь
};