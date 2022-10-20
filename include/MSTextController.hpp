#pragma once
#include "MinesweeperBoard.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class MSTextController
{
    MinesweeperBoard &debugBoard;
    MSBoardTextView &viewBoard;

public:
    MSTextController(MinesweeperBoard &, MSBoardTextView &);
    void play();
};

class MSSFMLView
{
    MinesweeperBoard &debugBoard;

public:
    MSSFMLView(MinesweeperBoard &);
    void draw(sf::RenderWindow &);
    void play(int x, int y);
};