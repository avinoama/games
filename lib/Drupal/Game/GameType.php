<?php
/**
 * @file
 * Contains \Drupal\Game\GameType.
 */

namespace Drupal\Game\GameType;

/**
 * Abstract Class Game Type
 *
 * Helps create a new game type
 *
 * 
 * 
 */
abstract class GameType {
	
	abstract function game_pre_load($game, $running_game);
	
}


