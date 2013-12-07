This module is a showcase that implement a logical game.
This module is not complate and is not advice to run on production envirement.
The module create a game entity.
Game entity has a bundle that describe its base logic like "Board Game", "Card Game" etc..
We only implemented only board game.

Each game can be "played", when you play the game you create a server side instance called "running game" that will save all changes to the game.

We are using Rules module for logical implementation
When you can trigger a logic event for base triggers:
on CREATING A NEW GAME
on GAME START
on GAME END

For Board Game there are more triggers
on Tile click EVENT IS CALLED
on Tile hover EVENT IS CALLED
on Tile set EVENT IS CALLED

When action can be customize per game by using conditions and actions
game message => a dynamic message that can be set to a certain game or all games
TileSetOwner => that will take a certain tile and make player own it

This module is build to be expended and not to use as is.

There are some example games already pre built with this module.
Tic Tac Toe
Sudoku
Chess


example : www.dgms.co

Maintainer : Avinoam
avinoama2@gmail.com



TODO:
1. Add a module that will be an interface to services module
2. Write test cases and Add game.test using simpletest
3. building ratchet web socket engine for games
4. creating installation profile
5. Implement a UI for editing game rules more simple from now.
6. D8 convertion
