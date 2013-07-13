This module is a showcase that implement a logical game.
The module uses entity as its base and create a game entity.
Game entity has a bundle that describe its base logic like "Board Game", "Card Game" etc..
We implemented only board game.

Each game can be "played", when you play the game you create a server side instance that will save all changes to the game.

We are using Rules module for logical implementation
When you can trigger a logic event for base triggers:
on CREATING A NEW GAME
on GAME START
on GAME END

For Board Game there are 2 more triggers
on CLICK EVENT IS CALLED
on HOVER EVENT IS CALLED

When action can be customize per game
for now i have 2 actions custom
game message => a dynamic message that can be set to a certain game or all games
TileSetOwner => that will take a certain tile and make player own it

This module is build to be expended and not to use as is.


TODO:
1. Add a module that will connect to services module


