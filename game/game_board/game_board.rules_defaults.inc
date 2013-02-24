<?php

function game_board_default_rules_configuration() {
  $rule = '{ "rules_ticktacktoe_logic" : {
    "LABEL" : "TickTackToe Logic",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game_board" ],
    "ON" : [ "tile_click" ],
    "IF" : [ { "data_is" : { "data" : [ "site:current-game-id" ], "value" : "1" } } ],
    "DO" : [
      { "rules_tile_set_owner" : {
          "game_instance" : "[site:current-game-instance]",
          "tile_position" : [ "site:current-tile-clicked" ]
        }
      }
    ]
  }
}';
  $configs['rules_ticktacktoe_logic'] = $rule;
  return $configs;
}