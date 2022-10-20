#include <iostream>
#include "MSTextController.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>

int main()
{
    sf::RenderWindow win(sf::VideoMode(480, 480), "Minesweeper");
    win.setPosition(sf::Vector2i(640, 240));

    MinesweeperBoard board(15, 15, GameMode::EASY);
    MSSFMLView view{board};

    while (win.isOpen())
    {
        int w = 32;

        sf::Vector2i pos = sf::Mouse::getPosition(win);
        int x = pos.x / w;
        int y = pos.y / w;

        sf::Event e;
        while (win.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                win.close();

            view.play(x, y);

            win.clear();
            view.draw(win);

            win.display();
        }
    }
}