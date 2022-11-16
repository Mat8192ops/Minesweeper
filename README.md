# Minesweeper

Project created by Maciej Matusiak. The game was designed and created as a part of academic programming classes in 2022. The rules of the game and the mechanism that supports the user's movements are based on the OPP paradigm and implemented in game files divided according to the structure of object-oriented programs. The configured CMake file was used for the compilation and project management process. This application uses the SFML library to run the game in graphics mode based on the textures used in the original minesweeper version.

# Rules:

- The cells depicted on the board have three states: obscured, flagged, and discoverd.
- If a given cell has been discovered and the field on it is empty, it means that there is no mine in its vicinity.
- If a digit is displayed on a given cell, it means the number of mines in the vicinity.
- If a cell displays a bomb symbol, the entire board is revealed and the game is unsuccessful.
- The board does not wrap around the edges so Squares on the sides of the board or in a corner have fewer neighbors.
- You don't have to mark all the mines to win, you just need to open all non-mine squares.
- If you mark a mine incorrectly, you will have to correct the mistake before you can win. Incorrect mine marking doesn't kill you, but it can lead to mistakes which do.
