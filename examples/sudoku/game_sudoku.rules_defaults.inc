<?php



/**
 * Implementing Hook_default_rules_configuration
 * This function will create my default game TicTacToe rules
 * @return $rules
 */
function game_sudoku_default_rules_configuration() {

  $rules['rules_sudoku_build_board'] = rules_import('{ "rules_sudoku_build_board" : {
    "LABEL" : "Sudoku build board",
    "PLUGIN" : "action set",
    "REQUIRES" : [ "board_games" ],
    "USES VARIABLES" : { "running_game" : { "label" : "running game", "type" : "running_game" } },
    "ACTION SET" : [
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "0",
          "tile_value" : "5"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "1",
          "tile_value" : "3"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "4",
          "tile_value" : "7"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "9",
          "tile_value" : "6"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "12",
          "tile_value" : "1"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "13",
          "tile_value" : "9"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "14",
          "tile_value" : "5"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "19",
          "tile_value" : "9"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "20",
          "tile_value" : "8"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "25",
          "tile_value" : "6"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "27",
          "tile_value" : "8"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "31",
          "tile_value" : "6"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "35",
          "tile_value" : "3"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "36",
          "tile_value" : "4"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "39",
          "tile_value" : "8"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "41",
          "tile_value" : "3"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "44",
          "tile_value" : "1"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "45",
          "tile_value" : "7"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "49",
          "tile_value" : "2"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "53",
          "tile_value" : "6"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "55",
          "tile_value" : "6"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "60",
          "tile_value" : "2"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "61",
          "tile_value" : "8"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "66",
          "tile_value" : "4"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "67",
          "tile_value" : "1"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "68",
          "tile_value" : "9"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "71",
          "tile_value" : "5"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "76",
          "tile_value" : "8"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "79",
          "tile_value" : "7"
        }
      },
      { "rules_game_set_tile_in_matrix" : {
          "running_game" : [ "running_game" ],
          "tile_postion" : "80",
          "tile_value" : "9"
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
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "sudoku" } },
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
    "IF" : [
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "sudoku" } }
    ],
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
