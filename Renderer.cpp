// Renderer.cpp
#include "Renderer.h"
#include "Config.h"
#include <string>

// реализация отрисовки

Renderer::Renderer(sf::RenderTarget& t) : target(t) {}

bool Renderer::loadFont(const std::string& path) {
    fontLoaded = font.openFromFile(path);
    return fontLoaded;
}

void Renderer::draw(const Board& board, GameState state) {
    drawField(board, state);
    if (state == GameState::GameOver) drawGameOver();
    if (state == GameState::Win)      drawWin();
}

void Renderer::drawField(const Board& board, GameState state) {
    for (int i = 0; i < cfg::SIZE; ++i) {
        for (int j = 0; j < cfg::SIZE; ++j) {
            drawCell(board.at(i, j), i, j, state);
        }
    }
}

void Renderer::drawCell(const Cell& cell, int row, int col, GameState state) {
    sf::RectangleShape rect({cfg::CELL, cfg::CELL});
    rect.setPosition({col * cfg::CELL, row * cfg::CELL});
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(sf::Color::Black);
    rect.setFillColor(cell.opened ? sf::Color(100, 100, 100) : sf::Color::White);
    target.draw(rect);

    auto drawGlyph = [&](const std::string& s, sf::Color color) {
        if (!fontLoaded) return;
        sf::Text t(font);
        t.setString(s);
        t.setCharacterSize(30);
        t.setFillColor(color);
        t.setPosition({col * cfg::CELL + 20.f, row * cfg::CELL + 8.f});
        target.draw(t);
    };

    if (state == GameState::GameOver && cell.mine)
        drawGlyph("X", sf::Color::Black);

    if (cell.flagged)
        drawGlyph("F", sf::Color::Red);

    if (cell.opened && cell.minesAround > 0)
        drawGlyph(std::to_string(cell.minesAround), sf::Color::White);
}

void Renderer::drawGameOver() {
    sf::RectangleShape overlay({(float)cfg::WIN_W, (float)cfg::WIN_H});
    overlay.setFillColor(sf::Color(50, 0, 0, 160));
    target.draw(overlay);

    if (!fontLoaded) return;

    sf::Text t(font);
    t.setString("GAME OVER");
    t.setCharacterSize(60);
    t.setFillColor(sf::Color::Red);
    t.setPosition({250.f, 350.f});
    target.draw(t);

    sf::Text r(font);
    r.setString("Press R to restart");
    r.setCharacterSize(25);
    r.setFillColor(sf::Color::White);
    r.setPosition({300.f, 430.f});
    target.draw(r);
}

void Renderer::drawWin() {
    sf::RectangleShape overlay({(float)cfg::WIN_W, (float)cfg::WIN_H});
    overlay.setFillColor(sf::Color(0, 0, 0, 160));
    target.draw(overlay);

    if (!fontLoaded) return;

    sf::Text t(font);
    t.setString("VICTORY");
    t.setCharacterSize(60);
    t.setFillColor(sf::Color::Green);
    t.setPosition({312.f, 350.f});
    target.draw(t);

    sf::Text r(font);
    r.setString("Press R to restart");
    r.setCharacterSize(25);
    r.setFillColor(sf::Color::White);
    r.setPosition({300.f, 430.f});
    target.draw(r);
}