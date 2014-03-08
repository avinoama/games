
<?php

/**
 * @file
 * Contains Drupal\Game\VisualGameInterface.
 */

namespace Drupal\Game;

/**
 * Defines a common interface for classed games.
 */
interface VisualGameInterface {
	abstract function game_display_pre_load($game, $running_game);

}