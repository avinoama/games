<?php

/**
 * Implementing Hook_default_rules_configuration
 * This function will create my default game TicTacToe rules
 * @return $rules 
 */
function board_games_default_rules_configuration() {

  $rules = array();

  $rules['rules_ticktacktoe_on_game_start'] = rules_import('{ "rules_ticktacktoe_on_game_start" : {
    "LABEL" : "TickTackToe On Game Start",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game" ],
    "ON" : [ "game_start" ],
    "IF" : [ { "data_is" : { "data" : [ "running-game:gid" ], "value" : "1" } } ],
    "DO" : [
      { "rules_game_send_message" : {
          "running_game" : [ "running_game" ],
          "message_text" : "Game started, its player1 turn."
        }
      }
    ]
  }
}');
  $rules['rules_ticktacktoe_checkwinner'] = rules_import('
 { "rules_ticktacktoe_checkwinner" : {
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player-id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
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
                "running_game_session" : [ "game-session" ],
                "player_id" : [ "player_id" ]
              }
            },
            { "rules_game_over" : { "running_game_session" : [ "game-session" ] } }
          ],
          "LABEL" : "CheckMatrix diagnal2"
        }
      }
    ]
  }
}');

  $rules['rules_ticktacktoe_switchplayer'] = rules_import('{ "rules_ticktacktoe_switchplayer" : {
    "LABEL" : "TickTackToe SwitchPlayer",
    "PLUGIN" : "rule",
    "REQUIRES" : [ "rules", "board_games" ],
    "USES VARIABLES" : { "running_game" : { "label" : "Running Game", "type" : "running_game" } },
    "IF" : [
      { "data_is" : { "data" : [ "running_game:status" ], "op" : "<", "value" : "3" } }
    ],
    "DO" : [
      { "rules_game_change_turn" : { "running_game" : [ "running_game:session" ] } }
    ]
  }
}');

  $rules['rules_ticktacktoe_game_rules'] = rules_import('{ "rules_ticktacktoe_game_rules" : {
    "LABEL" : "TickTackToe Game Rules",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "board_games" ],
    "ON" : [ "tile_click" ],
    "IF" : [
      { "data_is" : { "data" : [ "running_game:gid" ], "value" : "1" } },
      { "NOT data_is" : { "data" : [ "site:current-player-id" ], "value" : "0" } },
      { "data_is" : {
          "data" : [ "site:current-player-id" ],
          "value" : [ "site:current-player-turn" ]
        }
      },
      { "data_is" : {
          "data" : [ "site:current-tile-clicked-value" ],
          "op" : "<",
          "value" : "1"
        }
      },
      { "data_is" : {
          "data" : [ "running_game:status" ],
          "op" : "<",
          "value" : "3"
        }
      }
    ],
    "DO" : [
      { "rules_tile_set_owner" : {
          "running_game" : [ "running_game:session" ],
          "tile_position" : [ "site:current-tile-clicked" ]
        }
      },
      { "component_rules_ticktacktoe_checkwinner" : {
          "player_id" : [ "site:current-player-id" ],
          "game_session" : [ "running_game:session" ],
          "game_matrix" : [ "site:current-game-matrix" ]
        }
      },
      { "component_rules_ticktacktoe_switchplayer" : { "running_game" : [ "running_game" ] } }
    ]
  }
}');
  $rules['rules_sudoku_build_board'] = rules_import('{ "rules_sudoku_build_board" : {
    "LABEL" : "Sudoku build board",
    "PLUGIN" : "action set",
    "REQUIRES" : [ "board_games" ],
    "USES VARIABLES" : { "running_game" : { "label" : "running game", "type" : "running_game" } },
    "ACTION SET" : [
      { "rules_game_set_matrix" : {
          "running_game" : [ "running_game" ],
          "matrix_jason" : "[{\u00220\u0022: 5},{\u00221\u0022: 3},{\u00224\u0022: 7},{\u00229\u0022: 6},{\u002212\u0022: 1},{\u002213\u0022: 9},{\u002214\u0022: 5},{\u002219\u0022: 9},{\u002220\u0022: 8},{\u002225\u0022: 6},{\u002227\u0022: 8},{\u002231\u0022: 6},{\u002235\u0022: 3},{\u002236\u0022: 4},{\u002239\u0022: 8},{\u002241\u0022: 3},{\u002244\u0022: 1},{\u002245\u0022: 7},{\u002249\u0022: 2},{\u002253\u0022: 6},{\u002255\u0022: 6},{\u002260\u0022: 2},{\u002261\u0022: 8},{\u002266\u0022: 4},{\u002267\u0022: 1},{\u002268\u0022: 9},{\u002271\u0022: 5},{\u002276\u0022: 8},{\u002279\u0022: 7},{\u002280\u0022: 9}]"
        }
      }
    ]
  }
}');

  $rules['rules_sudoku_game_rules'] = rules_import('{ "rules_sudoku_game_rules" : {
    "LABEL" : "Sudoku Game Rules",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "board_games" ],
    "ON" : [ "tile_set" ],
    "IF" : [
      { "data_is" : { "data" : [ "running-game:gid" ], "value" : "2" } },
      { "data_is" : { "data" : [ "tile-value" ], "op" : "\u003C", "value" : "10" } },
      { "data_is" : { "data" : [ "tile-position" ], "op" : "\u003C", "value" : "81" } }
    ],
    "DO" : [
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : [ "tile-position" ],
          "tile_value" : [ "tile_value" ]
        }
      }
    ]
  }
}');

  $rules['rules_sudoku_on_game_start'] = rules_import('{ "rules_sudoku_on_game_start" : {
    "LABEL" : "Sudoku On Game Start",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game" ],
    "ON" : [ "game_start" ],
    "IF" : [ { "data_is" : { "data" : [ "running-game:gid" ], "value" : "2" } } ],
    "DO" : [
      { "rules_game_send_message" : {
          "running_game" : [ "running_game" ],
          "message_text" : "game started yipikaye motherfucker"
        }
      },
      { "component_rules_sudoku_build_board" : { "running_game" : [ "running_game" ] } }
    ]
  }
}');

  return $rules;
}

