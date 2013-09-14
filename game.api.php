<?php
/**
 * @file
 * Hooks provided by this module.
 * Notice in this module we have a couple of entities that can b used with entity regular Hooks
 * game
 * game_type
 * running_game
 * running_game_command
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * in this module there are 2 interfaces that allow you to consume game 
 * 1. game_ui
 * 2. game_service
 * does modules use the same set of hooks that i define here
 */


/**
 * this Hook is used only by game ui to build the game interface for html && js base games
 * on this function each class defines a set of js class needed for the module to function
 */
function hook_game_init_load(&$game, &$running_game) {

}