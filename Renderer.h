// Renderer.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Renderer {
public:
    explicit Renderer(sf::RenderTarget& target);

    bool loadFont(const std::string& path);

    void draw(const Board& board, GameState state);

private:
    void drawField(const Board& board, GameState state);
    void drawCell(const Cell& cell, int row, int col, GameState state);
    void drawGameOver();
    void drawWin();

    sf::RenderTarget& target;
    sf::Font font;
    bool fontLoaded = false;
};