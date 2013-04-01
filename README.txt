This module is a showcase that will try to implement Games inside drupal.
The module uses entity as its base and create a "game" entity.
Each Game entity has a bundle that describ its base logic like "Board Game", "Card Game" etc..

Each game can be "played", whan you play the game you create a server side instance called "running_game",
this "running_game" will save all changes to current game being played.

We are using Rules module for logical implementation.
To view forther more just install the board_game module and go into rules ui,
There you will see example for 2 games TicTacToe and Sudoku.

Logic event for base triggers:
on Game Created
on GAME START
on GAME END

For Board Games there are more triggers
Tile clicked
Tile hoverd
Tile set

When action can be customize per game or for all games

Remember : this module is just a showcase and is not ment to use in production envirements


TODO:
1. Add a module that will connect to services module
2. Create an entity called "Pawn" that will be able to move on a board
