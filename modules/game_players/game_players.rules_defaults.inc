<?php

/**
 * Implementing Hook_default_rules_configuration
 * This function will create my default game TicTacToe rules
 * @return $rules 
 */
function game_players_default_rules_configuration() {

  $rules = array();
  $rules['rules_notifiy_idle_players'] = rules_import('{ "rules_notifiy_idle_players" : {
    "LABEL" : "notifiy idle players",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game", "game_players" ],
    "ON" : [ "player_idle" ],
    "DO" : [
      { "rules_game_send_message" : {
          "running_game" : [ "running_game" ],
          "message_text" : "[running-game-player:player-name] is idle"
        }
      }
    ]
  }
}');
  return $rules;
}

