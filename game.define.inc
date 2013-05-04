<?php

define("GAME_STATUS_NOT_STARTED", 1); // Wating for players to join
define("GAME_STATUS_STARTED", 2); // Game is in progress
define("GAME_STATUS_ENDED", 3); // Game Ended

define("PLAYER_STATUS_JOINED", 1);
define("PLAYER_STATUS_PLAYING", 2);
define("PLAYER_STATUS_IDLE", 3);
define("PLAYER_STATUS_LEFT", 3);
define("PLAYER_STATUS_WON", 4);
define("PLAYER_MAX_IDLE_TIME", 120); // in seconds