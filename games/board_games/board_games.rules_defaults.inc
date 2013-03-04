<?php

function board_games_default_rules_configuration() {
  $rule = '{ "rules_ticktacktoe_checkwinner" : {
    "LABEL" : "TickTackToe CheckWinner",
    "PLUGIN" : "rule set",
    "REQUIRES" : [ "rules", "game" ],
    "RULES" : [
      { "RULE" : {
          "IF" : [
            { "OR" : [
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "0" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "1" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "2" } }
              ]
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:0" ],
                "value" : [ "site:current-game-matrix:1" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:1" ],
                "value" : [ "site:current-game-matrix:2" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-tile-clicked-value" ],
                "value" : [ "site:current-player-id" ]
              }
            }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "site:current-game-instance" ],
                "player_id" : [ "site:current-player-id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "site:current-game-instance" ] } }
          ],
          "LABEL" : "CheckMatrix row1"
        }
      },
      { "RULE" : {
          "IF" : [
            { "OR" : [
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "3" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "4" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "5" } }
              ]
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:3" ],
                "value" : [ "site:current-game-matrix:4" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:4" ],
                "value" : [ "site:current-game-matrix:5" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-tile-clicked-value" ],
                "value" : [ "site:current-player-id" ]
              }
            }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "site:current-game-instance" ],
                "player_id" : [ "site:current-player-id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "site:current-game-instance" ] } }
          ],
          "LABEL" : "CheckMatrix row2"
        }
      },
      { "RULE" : {
          "IF" : [
            { "OR" : [
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "6" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "7" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "8" } }
              ]
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:6" ],
                "value" : [ "site:current-game-matrix:7" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:7" ],
                "value" : [ "site:current-game-matrix:8" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-tile-clicked-value" ],
                "value" : [ "site:current-player-id" ]
              }
            }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "site:current-game-instance" ],
                "player_id" : [ "site:current-player-id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "site:current-game-instance" ] } }
          ],
          "LABEL" : "CheckMatrix row3"
        }
      },
      { "RULE" : {
          "IF" : [
            { "OR" : [
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "0" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "3" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "6" } }
              ]
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:0" ],
                "value" : [ "site:current-game-matrix:3" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:3" ],
                "value" : [ "site:current-game-matrix:6" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-tile-clicked-value" ],
                "value" : [ "site:current-player-id" ]
              }
            }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "site:current-game-instance" ],
                "player_id" : [ "site:current-game-id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "site:current-game-instance" ] } }
          ],
          "LABEL" : "CheckMatrix col1"
        }
      },
      { "RULE" : {
          "IF" : [
            { "OR" : [
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "1" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "4" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "7" } }
              ]
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:1" ],
                "value" : [ "site:current-game-matrix:4" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:4" ],
                "value" : [ "site:current-game-matrix:7" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-tile-clicked-value" ],
                "value" : [ "site:current-player-id" ]
              }
            }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "site:current-game-instance" ],
                "player_id" : [ "site:current-game-id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "site:current-game-instance" ] } }
          ],
          "LABEL" : "CheckMatrix col2"
        }
      },
      { "RULE" : {
          "IF" : [
            { "OR" : [
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "2" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "5" } },
                { "data_is" : { "data" : [ "site:current-tile-clicked" ], "value" : "8" } }
              ]
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:2" ],
                "value" : [ "site:current-game-matrix:5" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-game-matrix:5" ],
                "value" : [ "site:current-game-matrix:8" ]
              }
            },
            { "data_is" : {
                "data" : [ "site:current-tile-clicked-value" ],
                "value" : [ "site:current-player-id" ]
              }
            }
          ],
          "DO" : [
            { "rules_game_set_winners" : {
                "game_instance_session" : [ "site:current-game-instance" ],
                "player_id" : [ "site:current-player-id" ]
              }
            },
            { "rules_game_over" : { "game_instance_session" : [ "site:current-game-instance" ] } }
          ],
          "LABEL" : "CheckMatrix col3"
        }
      }
    ]
  }
}';

  $rule2 = '{ "rules_ticktacktoe_game_rules" : {
    "LABEL" : "TickTackToe Game Rules",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "board_games" ],
    "ON" : [ "tile_click" ],
    "IF" : [
      { "data_is" : { "data" : [ "site:current-game-id" ], "value" : "1" } },
      { "NOT data_is" : { "data" : [ "site:current-player-id" ], "value" : "0" } }
    ],
    "DO" : [
      { "rules_tile_set_owner" : {
          "game_instance" : [ "site:current-game-instance" ],
          "tile_position" : [ "site:current-tile-clicked" ]
        }
      },
      { "component_rules_ticktacktoe_checkwinner" : [] }
    ]
  }
}';
  $rules = array();
  // Add a reaction rule to display the default Add to Cart message.
  $rule = rules_reaction_rule();

  $rule->label = t('TickTackToe Game Rules');
  $rule->active = TRUE;

  $rule->event('tile_click')
          ->condition(rules_condition('data_is', array(
              'data' => 'site:current-game-id',
              'value' => '1',
          )))
          ->condition(rules_condition('data_is', array(
              'data' => 'site:current-player-id',
              'value' => '0',
          ))->negate())
          ->action('rules_tile_set_owner', array(
              'game_instance' => 'site:current-game-instance',
              'tile_position' => 'site:current-tile-clicked',
          ));
  $rules['rules_ticktacktoe_game_rules'] = $rule;
  // $configs['rules_ticktacktoe_checkwinner'] = $rule;
  $configs['rules_ticktacktoe_game_rules'] = $rule2;

  return null;
}