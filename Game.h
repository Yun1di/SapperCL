#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Renderer.h"

//окно,цикл,ввод

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    void handleMouse(const sf::Event::MouseButtonPressed& mouse);
    void handleKey(const sf::Event::KeyPressed& key);

    sf::RenderWindow window;
    Board            board;
    Renderer         renderer;
    GameState        state = GameState::Playing;
};