#include "MSTextController.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode gameMode)
{
    this->gameMode = gameMode;
    this->height = height;
    this->width = width;

    for (int row = 0; row < height; ++row)
    {
        fields.push_back({});
        for (int col = 0; col < width; ++col)
        {
            fields[row].push_back(Field{false, false, false});
        }
    }

    if (gameMode == GameMode::DEBUG)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if ((i == j) || (i == 0) || ((i % 2 == 0) && (j == 0)))
                    fields[i][j].hasMine = true;
            }
        }
    }
    else if (gameMode == GameMode::EASY)
    {
        int MineCount = (height * width) * 0.1;
        bool exit = false;
        int column;
        int row;
        srand(time(NULL));
        for (int i = 0; i < MineCount; i++)
        {
            do
            {
                exit = false;
                column = (int)rand() % width;
                row = (int)rand() % height;
                if (fields[row][column].hasMine == false)
                    fields[row][column].hasMine = true;
                else
                    exit = true;
            } while (exit != false);
        }
    }
    else if (gameMode == GameMode::NORMAL)
    {
        int MineCount = (height * width) * 0.2;
        bool exit = false;
        int column;
        int row;
        srand(time(NULL));
        for (int i = 0; i < MineCount; i++)
        {
            do
            {
                exit = false;
                column = (int)rand() % width;
                row = (int)rand() % height;
                if (fields[row][column].hasMine == false)
                    fields[row][column].hasMine = true;
                else
                    exit = true;
            } while (exit != false);
        }
    }
    else if (gameMode == GameMode::HARD)
    {
        int MineCount = (height * width) * 0.3;
        bool exit = false;
        int column;
        int row;
        srand(time(NULL));
        for (int i = 0; i < MineCount; i++)
        {
            do
            {
                exit = false;
                column = (int)rand() % width;
                row = (int)rand() % height;
                if (fields[row][column].hasMine == false)
                    fields[row][column].hasMine = true;
                else
                    exit = true;
            } while (exit != false);
        }
    }
}

void MinesweeperBoard::debug_display() const
{
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            std::cout << "[";

            if (fields[row][col].hasMine)
                std::cout << "M";
            else
                std::cout << ".";

            if (fields[row][col].isRevealed)
                std::cout << "o";
            else
                std::cout << ".";

            if (fields[row][col].hasFlag)
                std::cout << "f";
            else
                std::cout << ".";

            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height;
}

int MinesweeperBoard::getMineCount() const
{
    return 0;
}

int MinesweeperBoard::countMines(int row, int col) const
{
    int Mines = 0;
    if ((row > height) || (col > width))
        return -1;
    else
    {
        for (int i = (row - 1); i <= (row + 1); i++)
        {
            for (int j = (col - 1); j <= (col + 1); j++)
            {
                if ((i < 0) || (j < 0) || (i >= height) || (j >= width))
                    continue;
                else if (fields[i][j].hasMine == true)
                    Mines++;
            }
        }
    }
    return Mines;
}

bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if (fields[row][col].hasFlag)
        return true;
    else
        return false;
}

void MinesweeperBoard::toggleFlag(int row, int col)
{
    if ((col < 0) || (row < 0) || (col >= width) || (row >= height))
        std::cout << "Out of Board" << std::endl;
    if (fields[row][col].isRevealed == false)
        fields[row][col].hasFlag = !fields[row][col].hasFlag;
}

void MinesweeperBoard::revealField(int row, int col)
{
    if ((col < 0) || (row < 0) || (col >= width) || (row >= height))
        return;
    if (fields[row][col].isRevealed == true)
        return;
    if (fields[row][col].hasFlag == true)
        return;
    if ((fields[row][col].isRevealed == false) && (fields[row][col].hasMine == false))
        fields[row][col].isRevealed = true;

    if ((fields[row][col].isRevealed == false) && (fields[row][col].hasMine == true))
    {
        fields[row][col].isRevealed = true;
        gameState = GameState::FINISHED_LOSS;
    }
}

bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if (fields[row][col].isRevealed == true)
        return true;
    else
        return false;
}

bool MinesweeperBoard::hasMine(int row, int col) const
{
    return fields[row][col].hasMine;
}

GameState MinesweeperBoard::getGameState() const
{
    if (gameState == GameState::FINISHED_LOSS)
        return GameState::FINISHED_LOSS;

    if (gameState == GameState::FINISHED_WIN)
        return GameState::FINISHED_WIN;

    else
        return GameState::RUNNING;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if ((fields[row][col].isRevealed == false) && (fields[row][col].hasFlag == true))
        return 'F';
    if ((fields[row][col].isRevealed == false) && (fields[row][col].hasFlag == false))
        return '_';
    if ((fields[row][col].isRevealed == true) && (fields[row][col].hasMine == true))
        return 'X';
    if ((fields[row][col].isRevealed == true) && (countMines(row, col) == 0))
        return ' ';
    if ((fields[row][col].isRevealed == true) && (countMines(row, col) != 0))
        return '0' + countMines(row, col);
    else
        return '#';
}

MSBoardTextView::MSBoardTextView(MinesweeperBoard &adminMine) : debugBoard(adminMine)
{
}

void MSBoardTextView::display() const
{
    for (int i = 0; i <= debugBoard.getBoardHeight(); i++)
    {
        for (int j = 0; j <= debugBoard.getBoardWidth(); j++)
        {
            if ((i == 0) && (j == 0))
                std::cout << "    ";
            else if (i == 0)
                std::cout << " " << j - 1 << "  ";
            else if (j == 0)
                std::cout << " " << i - 1 << "  ";
            else
                std::cout << "[" << debugBoard.getFieldInfo(i - 1, j - 1) << "] ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    if (debugBoard.getGameState() == GameState::RUNNING)
    {
        std::cout << "      TO DISCOVER THE FIELD,          PRESS 1" << std::endl;
        std::cout << "      TO PLACE / REMOVE THE FLAG,     PRESS 2" << std::endl;
        std::cout << std::endl;
    }
}
