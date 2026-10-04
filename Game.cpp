#include "Game.h"
#include "Config.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode({cfg::WIN_W, cfg::WIN_H}), "Sapper")
    , renderer(window)
{
    if (!renderer.loadFont("fnt_dotumche.ttf")) 
    {
        std::cerr << "Font not found!\n";
    }
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            handleKey(*key);

        if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            handleMouse(*mouse);
    }
}

void Game::handleKey(const sf::Event::KeyPressed& key) {
    using K = sf::Keyboard::Scancode;
    if (key.scancode == K::Escape) window.close();
    if (key.scancode == K::R) {
        board.reset();
        state = GameState::Playing;
    }
}

void Game::handleMouse(const sf::Event::MouseButtonPressed& mouse) {
    if (state != GameState::Playing) return;

    int col = static_cast<int>(mouse.position.x / cfg::CELL);
    int row = static_cast<int>(mouse.position.y / cfg::CELL);
    if (!board.inBounds(row, col)) return;

    if (mouse.button == sf::Mouse::Button::Right) 
    {
        board.toggleFlag(row, col);
    }
    else if (mouse.button == sf::Mouse::Button::Left) 
    {
        const Cell& c = board.at(row, col);
        if (c.opened || c.flagged) return;

        if (board.isMine(row, col)) 
        {
            state = GameState::GameOver;
        } else {
            board.open(row, col);
            if (board.checkVictory())
                state = GameState::Win;
        }
    }
}

void Game::update() {}

void Game::render() {
    window.clear(sf::Color::White);
    renderer.draw(board, state);
    window.display();
}