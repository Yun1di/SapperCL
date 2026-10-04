#include <SFML/Graphics.hpp>
// #include<windows.h>
#include <iostream>

using namespace std;

const int SIZE = 20;
int field[SIZE][SIZE];

int main()
{
    // SetConsoleOutputCP(65001);
    
    sf::RenderWindow window(sf::VideoMode({840, 840}), "Сапер");

    // заполнение поля нулями
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            field[i][j] = 0;

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // обработка клика мыши
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                int col = mouse->position.x / 42;
                int row = mouse->position.y / 42;
                if (col >= 0 && col < SIZE && row >= 0 && row < SIZE)
                    field[row][col] = 1;
            }
        }

        window.clear(sf::Color::White);

        // рисуем сетку
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                sf::RectangleShape cell(sf::Vector2f(42, 42));
                cell.setPosition(sf::Vector2f(j * 42, i * 42));
                // цвет зависит от состояния клетки
                cell.setFillColor(field[i][j] == 1 ? sf::Color::Blue : sf::Color::White);
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::Black);

                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}