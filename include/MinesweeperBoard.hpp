#pragma once
#include <vector>

enum class GameMode
{
  DEBUG,
  EASY,
  NORMAL,
  HARD
};

enum class GameState
{
  RUNNING,
  FINISHED_WIN,
  FINISHED_LOSS
};

struct Field
{
  bool hasMine;
  bool hasFlag;
  bool isRevealed;
};

class MinesweeperBoard
{
  std::vector<std::vector<Field>> fields;
  GameMode gameMode;
  GameState gameState;
  int width;
  int height;

public:
  MinesweeperBoard(int, int, GameMode);

  void debug_display() const;

  int getBoardWidth() const;
  int getBoardHeight() const;
  int getMineCount() const;

  int countMines(int row, int col) const;

  bool hasFlag(int row, int col) const;
  void toggleFlag(int row, int col);
  void revealField(int row, int col);
  bool isRevealed(int row, int col) const;
  bool hasMine(int row, int col) const;

  GameState getGameState() const;
  char getFieldInfo(int row, int col) const;
};

class MSBoardTextView
{
  MinesweeperBoard &debugBoard;

public:
  MSBoardTextView(MinesweeperBoard &);
  void display() const;
};
