#include "MSTextController.hpp"
#include "MinesweeperBoard.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

MSTextController::MSTextController(MinesweeperBoard &adm, MSBoardTextView &vie)
    : debugBoard(adm), viewBoard(vie)
{
}

void MSTextController::play()
{
    int row, col;
    char choice;
    while (debugBoard.getGameState() == GameState::RUNNING)
    {
        viewBoard.display();
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            std::cout << "      SELECT FIELD" << std::endl;

            std::cout << "      Row number: ";
            std::cin >> row;
            std::cout << std::endl;

            std::cout << "      Column number: ";
            std::cin >> col;
            std::cout << std::endl;

            debugBoard.revealField(row, col);
            break;

        case '2':
            std::cout << "      SELECT FIELD" << std::endl;

            std::cout << "      Row number: ";
            std::cin >> row;
            std::cout << std::endl;

            std::cout << "      Column number: ";
            std::cin >> col;
            std::cout << std::endl;

            debugBoard.toggleFlag(row, col);
            break;

        default:
            std::cout << "      INCORRECT SELECTION, PLEASE TRY AGAIN..." << std::endl;
        }
        if (debugBoard.getGameState() == GameState::FINISHED_LOSS)
        {
            viewBoard.display();
            std::cout << "      MINE! YOU LOST!" << std::endl;
        }
    };
}

MSSFMLView::MSSFMLView(MinesweeperBoard &view_sfml) : debugBoard(view_sfml)
{
}

namespace
{
    const int GFX_EMPTY_FIELD_INDEX = 0;
    const int GFX_HIDE_FIELD_INDEX = 10;
    const int GFX_FLAG_INDEX = 11;
}

void MSSFMLView::draw(sf::RenderWindow &win)
{
    int w = 32;
    int sgrid[15][15];

    sf::Texture t;
    t.loadFromFile("/home/paro/minesweeper/tiles.jpg");
    sf::Sprite s(t);

    for (int i = 0; i < debugBoard.getBoardHeight(); i++)
        for (int j = 0; j < debugBoard.getBoardWidth(); j++)
        {
            if (!debugBoard.isRevealed(i, j))
                sgrid[i][j] = GFX_HIDE_FIELD_INDEX;
            if (debugBoard.hasFlag(i, j))
                sgrid[i][j] = GFX_FLAG_INDEX;
            if (debugBoard.isRevealed(i, j) && debugBoard.countMines(i, j) == 0)
                sgrid[i][j] = GFX_EMPTY_FIELD_INDEX;
            if (debugBoard.isRevealed(i, j) && debugBoard.countMines(i, j) != 0)
                sgrid[i][j] = debugBoard.countMines(i, j);
            if (debugBoard.hasMine(i, j) && debugBoard.isRevealed(i, j))
            {
                sgrid[i][j] = 9;
                for (int i = 0; i < debugBoard.getBoardHeight(); i++)
                    for (int j = 0; j < debugBoard.getBoardWidth(); j++)
                        debugBoard.revealField(i, j);
            }
        }

    for (int i = 0; i < debugBoard.getBoardHeight(); i++)
        for (int j = 0; j < debugBoard.getBoardWidth(); j++)
        {
            s.setTextureRect(sf::IntRect(sgrid[i][j] * w, 0, w, w));
            s.setPosition(i * w, j * w);
            win.draw(s);
        }
}

void MSSFMLView::play(int x, int y)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        debugBoard.revealField(x, y);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        debugBoard.toggleFlag(x, y);
}
