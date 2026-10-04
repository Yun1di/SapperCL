#include<SFML/Graphics.hpp>
#include<iostream>

// using std::cout;
using namespace std;

const int SIZE =16;
const int MINES =32;
;
// coust int FLAGGED = 32;
// int field[SIZE][SIZE];

// int CountMines=MINES;
// int NOopen=0;

struct Cell 
{
    bool mine = false;
    bool opened = false;
    bool flagged = false;
    int minesAround=0;
};

Cell field[SIZE][SIZE];
// bool fall = false;

enum class GameState
{
    Playing,
    GameOver,
    Win
};
GameState gamestate = GameState::Playing;


void placeMines() // прототип растановки мин на поле
{
    srand(time(0));
    
    int placed=0;
    
    while(placed<MINES)
    {
        int row=rand()%SIZE;
        int col=rand()%SIZE;
        
        if(!field[row][col].mine)
        {
            field[row][col].mine=true;
            placed++;
        }
    }
    
}

int countMinesAround(int row, int col) // прототип считает мины вокруг клетки
{
    int count = 0;
    
    // Проходим по всем соседним клеткам (8 направлений)
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i==0 && j==0)
            {
                continue;
            }
            int newRow = row + i;
            int newCol = col + j;
            
            // Проверяем, что координаты в пределах поля
            if (newRow >= 0 && newRow < SIZE && 
                newCol >= 0 && newCol < SIZE)
            {
                if (field[newRow][newCol].mine)
                    count++;
            }
        }
    }   
    return count;
}

void openCell(int row,int col)
{
    // if((row<0||row>=SIZE|| col<0||col>=SIZE) && // проверка на границы поля
    //     ((field[row][col].opened) ||//если клетка уже открыта
    //     (field[row][col].flagged) || //если флаг
    //     (field[row][col].mine)))//проверка на мину
    // {
    //     return;
    // }

    if(row<0||row>=SIZE|| col<0||col>=SIZE)// проверка на границы поля
    {
       return;
    }
    if (field[row][col].opened) 
    {
        return;
    }
    if (field[row][col].flagged)//если флаг
    {
        return;
    }
    if (field[row][col].mine)//проверка на мину
    {
        return;
    }

    field[row][col].opened=true;//открываю клетку

    if (field[row][col].minesAround > 0)// если вокруг есть мина то больше открывать не нужно
    {
        return;
    }

    for (int i = -1; i <= 1; i++)//если мин вокруг 0 то открываю соседние
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            openCell(row + i, col + j);
        }
    }
}

bool checkVictory()//проверка на открытые клетки и на мины =>   победа 
{
    for(int i=0; i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(!field[i][j].mine && !field[i][j].opened)
            {
                return false;
            }
        }
    }
    return true;
}

void resetGame()
{
    for (int i = 0; i < SIZE; i++)//очищяю поле
    {
        for (int j = 0; j < SIZE; j++)
        {
            field[i][j] = Cell{};
        }
    }

     placeMines();

     for (int i = 0; i < SIZE; i++) // считаю мины вокруг каждой клетки по порядку
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (!field[i][j].mine)
            {
                field[i][j].minesAround = countMinesAround(i, j);
            }
        }
    }

    gamestate = GameState::Playing;
}

// void VictoryCheck()
// {
//     for(int i =0; i<SIZE;i++)
//         for(int j=0;j<SIZE;j++)
//         if((!field[i][j].opened || field[i][j].opened)&&field[i][j].mine)
//             NOopen+=(field[i][j].opened=false);
// }

// int countOpenCells()
// {
//     if(countOpenCells()==SIZE*SIZE-MINES)
//         gamestate=GameState::Win;
// }

int main()
{
    sf::RenderWindow window(sf::VideoMode({848,1000}), "Sapper");

    sf::Font font;
    if(!font.openFromFile("fnt_dotumche.ttf"))
    {
        return -1;
    }

    for(int i =0; i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            field[i][j]=Cell{};
    

    placeMines();

    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(!field[i][j].mine)
            {
                field[i][j].minesAround=countMinesAround(i,j);
            }
        }
    }
    
    while (window.isOpen())
    {
        while(const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>())// reset
            {
                if (key->scancode == sf::Keyboard::Scancode::R)
                {
                    resetGame();
                }
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>())//закрытие окна на esc
            {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();                
                }
            }

            // if(NOopen==(NOopen-MINES))
            // {
            //     gamestate=GameState::Win;
            // }
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {

                if(gamestate!=GameState::Playing)
                    continue;

                int col = mouse -> position.x/53;
                int row = mouse -> position.y/53;
                

                // проверка на мину 
                if (col>=0 && col<SIZE && row >=0 && row<SIZE)
                {
                    if (mouse->button == sf::Mouse::Button::Right)//обработка на пкм флаг 
                    {
                        if(!field[row][col].opened)
                        {
                            field[row][col].flagged=!field[row][col].flagged;

                            // if (checkVictory())
                            // {
                            //     gamestate=GameState::Win;
                            // }
                            // field[row][col].flagged=true;
                            // CountMines--;
                            // cout<<CountMines;
                        }
                        // if (!field[row][col].flagged)
                        // {
                        //     field[row][col].flagged=!field[row][col].flagged;
                        // }
                        // if (field[row][col].flagged=true)
                        // {
                        //     field[row][col].flagged=!field[row][col].flagged;
                        //     CountMines++;
                        // }
                        // else if ((field[row][col].opened)&&(field[row][col].mine=true))
                        // {
                        //     field[row][col].flagged=!field[row][col].flagged;
                        //     // CountMines--;
                        //     // cout<<CountMines<<endl;         // не выводит --------------------------------------------
                        // }
                    }

                    else if(mouse->button==sf::Mouse::Button::Left)
                    {
                        if(!field[row][col].opened && !field[row][col].flagged)
                        {
                            if(field[row][col].mine)
                            {
                                gamestate=GameState::GameOver;
                            }
                            // if (CountMines==0)// выигрышь
                            // {
                            //     gamestate=GameState::Win;
                            // }
                            else
                            {
                                openCell(row,col);
                                if (checkVictory())
                                {
                                    gamestate=GameState::Win;
                                }
                                // NOopen++;
                                // if(NOopen==(NOopen-MINES))
                                // {
                                //     gamestate=GameState::Win;
                                // }
                            }
                        }
                    }

                    // if (!field[row][col].opened)
                    // {
                    //     if (field[row][col].mine)
                    //     {    
                    //         fall=true;
                    //     }            
                    //     else
                    //     {
                    //         openCell(row,col);
                    //         // field[row][col].opened=true;

                    //         // field[row][col].opened=true;
                    //         //     countMinesAround(row,col);
                    //     }
                    // }
                }
            }
        }

        window.clear(sf::Color::White);

        for (int i =0; i<SIZE;i++)
        {
            for(int j =0; j<SIZE; j++){
                sf::RectangleShape cell(sf::Vector2f(53, 53));
                cell.setPosition(sf::Vector2f(j * 53, i * 53));

                // cell.setFillColor(field[i][j]==1 ? sf::Color(100,100,100) : sf::Color::White);
                cell.setOutlineThickness(2);
                cell.setOutlineColor(sf::Color::Black);

                if (field[i][j].opened)
                {
                    cell.setFillColor(sf::Color(100,100,100));
                }
                else
                {
                    cell.setFillColor(sf::Color::White);
                }

                window.draw(cell);

                if(gamestate ==GameState::GameOver && field[i][j].mine)
                {
                    sf::Text mine(font);

                    mine.setString("X");
                    mine.setCharacterSize(30);
                    mine.setFillColor(sf::Color::Black);

                    mine.setPosition(
                        sf::Vector2f(
                            j * 53 + 20,
                            i * 53 + 8
                        )
                    );

                    window.draw(mine);
                }

                if(field[i][j].flagged)
                {
                    sf::Text flag(font);

                    flag.setString("F");
                    flag.setCharacterSize(30);
                    flag.setFillColor(sf::Color::Red);

                    flag.setPosition(sf::Vector2f(j*53+20,i*53+8));

                    window.draw(flag);
                }
                
                if(field[i][j].opened && field[i][j].minesAround >0)
                {
                    sf::Text text(font);

                    text.setString(std::to_string(field[i][j].minesAround));

                    text.setCharacterSize(30);
                    text.setFillColor(sf::Color::White);

                    text.setPosition(sf::Vector2f(j*53+20,i*53+8));

                    window.draw(text);
                }
                // Определения цвета клетки/проигрыш 
                // Число мин вокруг 
                
                // Отрисовка клеток

                // if (field[i][j] == 0)  // Не открыта
                // {
                //     cell.setFillColor(sf::Color(200, 200, 200));
                // }

                // if (field[i][j] == -1)  // Скрытая мина (не показываем)
                // {
                //     //cell.setFillColor(sf::Color(200, 200, 200));  

                //     cell.setFillColor(sf::Color::White);// Как обычная клетка
                // }
                // else if (field[i][j] == -2)  // Нажатая мина (смерть)
                // {
                //     cell.setFillColor(sf::Color::Black);
                // }
                // else  // Открытая клетка с числом
                // {
                //     // Разные оттенки серого
                //     int shade = 255 - (field[i][j] * 20);
                //     if (shade < 100) shade = 100;
                //     cell.setFillColor(sf::Color(shade, shade, shade));
                // }

            }
        }

        // if (fall) 
        // {
        //     // Загружаем шрифт ДО цикла
        //     sf::Font font;
        //     if (!font.openFromFile("QuillScriptSsi.ttf")) {
        //         return -1; // Если шрифт не загрузился — выходим
        //     }
            
        //     // Создаем текст
        //     sf::Text text(font);
        //     text.setString("GAME OVER");
        //     text.setCharacterSize(30);
        //     text.setFillColor(sf::Color::White);
            
        //     // Создаем окно для Game Over
        //     sf::RenderWindow gameOverWindow(sf::VideoMode({300, 200}), "Game Over");
            
        //     while (gameOverWindow.isOpen()) 
        //     {
        //         while (const auto event = gameOverWindow.pollEvent()) 
        //         {
        //             if (event->is<sf::Event::Closed>()) 
        //             {
        //                 gameOverWindow.close();
        //             }
        //             // Можно добавить: нажатие Enter или клик для закрытия
        //             if (const auto* key = event->getIf<sf::Event::KeyPressed>()) 
        //             {
        //                 if (key->scancode == sf::Keyboard::Scancode::Enter) 
        //                 {
        //                     gameOverWindow.close();
        //                 }
        //             }
        //         }
                
        //         gameOverWindow.clear(sf::Color::Black); // Черный фон
        //         gameOverWindow.draw(text);              // Рисуем текст
        //         gameOverWindow.display();               // Показываем
        //     }
        // }

            // window.draw(overlay);

        if(gamestate== GameState::GameOver)
        {
            sf::RectangleShape overlay(sf::Vector2f(848,848));
            overlay.setFillColor(sf::Color(50,0,0,160));

            window.draw(overlay);

            sf::Text gameOverText(font);

            gameOverText.setString("GAME OVER");
            gameOverText.setCharacterSize(60);
            gameOverText.setFillColor(sf::Color::Red);

            gameOverText.setPosition(sf::Vector2f(250, 350));

            window.draw(gameOverText);

            sf::Text restartText(font);

            restartText.setString("Press R to restart");
            restartText.setCharacterSize(25);
            restartText.setFillColor(sf::Color::White);

            restartText.setPosition(sf::Vector2f(300, 430));

            window.draw(restartText);
        }

        if(gamestate== GameState::Win)
        {
            sf::RectangleShape overlay(sf::Vector2f(848,848));
            overlay.setFillColor(sf::Color(0,0,0,160));

            window.draw(overlay);

            sf::Text gameWinText(font);

            gameWinText.setString("VICTORY");
            gameWinText.setCharacterSize(60);
            gameWinText.setFillColor(sf::Color::Green);

            gameWinText.setPosition(sf::Vector2f(312, 350));

            window.draw(gameWinText);

            sf::Text restartText(font);

            restartText.setString("Press R to restart");
            restartText.setCharacterSize(25);
            restartText.setFillColor(sf::Color::White);

            restartText.setPosition(sf::Vector2f(300, 430));

            window.draw(restartText);
        }
        window.display();
    }

    
    return 0;
}
