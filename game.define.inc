<?php

define("GAME_STATUS_NOT_STARTED", 1); // Wating for players to join
define("GAME_STATUS_STARTED", 2); // Game is in progress
define("GAME_STATUS_ENDED", 3); // Game Ended

define("PLAYER_STATUS_JOINED", 1);
define("PLAYER_STATUS_PLAYING", 2);
define("PLAYER_STATUS_IDLE", 3);
define("PLAYER_STATUS_LEFT", 3);
define("PLAYER_STATUS_WON", 4);


/**
 * General function
 */


/**
 * function calculate_string
 *
 * instead of eval actually does the same thing but with only numbers
 * 
 * @param type $mathString
 * @return number
 */
function calculate_string($mathString) {
  $mathString = trim($mathString);     // trim white spaces
  $mathString = preg_replace('[^0-9\+-\*\/\(\) ]', '', $mathString);    // remove any non-numbers chars; exception for math operators

  $compute = create_function("", "return (" . $mathString . ");");
  return 0 + $compute();
}