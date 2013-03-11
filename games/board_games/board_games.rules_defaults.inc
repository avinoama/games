<?php

function board_games_default_rules_configuration() {

  $rules = array();

  $rule->label = t('TickTackToe Game Rules');
  $rule->active = TRUE;

  $rule->event('tile_click')
          ->condition(rules_condition('data_is', array(
                      'data:select' => 'site:current-game-id',
                      'value' => '1',
                  )))
          ->condition(rules_condition('data_is', array(
                      'data:select' => 'site:current-player-id',
                      'value' => '0',
                  ))->negate())
          ->condition(rules_condition('data_is', array(
                      'data:select' => 'site:current-player-id',
                      'value:select' => 'site:current-player-turn',
                  )))
          ->condition(rules_condition('data_is', array(
                      'data:select' => 'site:current-tile-clicked-value',
                      'op' => '<',
                      'value' => '1',
                  )))
          ->action('rules_tile_set_owner', array(
              'game_instance:select' => 'site:current-game-instance',
              'tile_position:select' => 'site:current-tile-clicked',
          ))
          ->action('rules_ticktacktoe_checkwinner', array(
              'player_id:select' => 'site:current-player-id',
              'game_session:select' => 'site:current-game-instance',
              'game_matrix:select' => 'site:current-game-matrix',
          ))
          ->action('rules_game_change_turn', array(
              'game_instance:select' => 'site:current-game-instance',
          ));

  
  
  
  $rule= rule();
  $rule = rules_import(
  '{ "rules_ticktacktoe_game_rules" : {
    "LABEL" : "TickTackToe Game Rules",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "board_games" ],
    "ON" : [ "tile_click" ],
    "IF" : [
      { "data_is" : { "data" : [ "site:current-game-id" ], "value" : "1" } },
      { "NOT data_is" : { "data" : [ "site:current-player-id" ], "value" : "0" } },
      { "data_is" : {
          "data" : [ "site:current-player-id" ],
          "value" : [ "site:current-player-turn" ]
        }
      },
      { "data_is" : {
          "data" : [ "site:current-tile-clicked-value" ],
          "op" : "\u003C",
          "value" : "1"
        }
      }
    ],
    "DO" : [
      { "rules_tile_set_owner" : {
          "game_instance" : [ "site:current-game-instance" ],
          "tile_position" : [ "site:current-tile-clicked" ]
        }
      },
      { "component_rules_ticktacktoe_checkwinner" : {
          "player_id" : [ "site:current-player-id" ],
          "game_session" : [ "site:current-game-instance" ],
          "game_matrix" : [ "site:current-game-matrix" ]
        }
      },
      { "rules_game_change_turn" : { "game_instance" : [ "site:current-game-instance" ] } }
    ]
  }
}');

 $rule2 = rules_import('{ "rules_ticktacktoe_checkwinner" : {
    "LABEL" : "TickTackToe CheckWinner",
    "PLUGIN" : "rule set",
    "REQUIRES" : [ "board_games", "game" ],
    "USES VARIABLES" : {
      "player_id" : { "label" : "player id", "type" : "integer" },
      "game_session" : { "label" : "Game session", "type" : "text" },
      "game_matrix" : { "label" : "Game matrix", "type" : "list\u003Cinteger\u003E" }
    },
    "RULES" : [
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "site:current-player-id" ], "item2" : [ "game-matrix:0" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:1" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:2" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player-id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix row1"
        }
      },
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:3" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:4" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:5" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix row2"
        }
      },
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:6" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:7" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:8" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix row3"
        }
      },
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:0" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:3" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:6" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix col1"
        }
      },
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:1" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:4" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:7" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix col2"
        }
      },
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:2" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:5" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:8" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix col3"
        }
      },
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:0" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:4" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:8" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix diagnal1"
        }
      },
      { "RULE" : {
          "IF" : [
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:2" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:4" ] } },
            { "board_games_rules_condition_check_matrix" : { "item1" : [ "player-id" ], "item2" : [ "game-matrix:6" ] } }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix diagnal2"
        }
      }
    ]
  }
}');

  $rules['rules_ticktacktoe_game_rules'] = $rule;
  $rules['rules_ticktacktoe_checkwinner'] = $rule2;

  return $rules;

}