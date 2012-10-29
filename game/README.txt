This module is a show case that will try to implement a logical game.
The module uses entity as its base and create a game entity.
Game entity has a bundle that describ its base logic like "Board Game", "Card Game" etc..

Each game can be "played", whan you play the game you create a server side instance that will save all changes to the game.


For now we use Trigger and Action to implement logic
whan you can trigger a logic event for base triggers:
on CREATING A NEW GAME
on GAME START
on GAME END

For base turn module there are 2 more triggers
on TURN STARTS
on TURN ENDS

For Board Game there are 2 more triggers
on CLICK EVENT IS CALLED
on HOVER EVENT IS CALLED

Whan action can be costumize per game or for all games
for now i have 2 actions custom
message => a dynamic message that can be set to a certine game or all games
TileSetOwner => that will take a certine tile and make player own it

This module is build to be expended and not to use as is.


TODO:
1. Seperate UI from code and build 2 different modules for that
2. Change The player Join/leave in to the trigger circle
3. Add a module that will connect to services module
4. Think about moving to rules module api
5. Make Turn base game a bolean option
