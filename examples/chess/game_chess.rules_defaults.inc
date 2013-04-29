<?php

/**
 * Implementing Hook_default_rules_configuration
 * This function will create game Chess rules
 * @return $rules
 */
function game_chess_default_rules_configuration() {

  $rules = array();

  $rules['rules_chess_on_game_start'] = rules_import('{ "rules_chess_on_game_start" : {
    "LABEL" : "Chess on game Starts",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game_pieces", "game" ],
    "ON" : [ "game_start" ],
    "IF" : [
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "chess" } }
    ],
    "DO" : [
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "8"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "9"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "10"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "11"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "12"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "13"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "14"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "15"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "48"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "49"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "50"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "51"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "52"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "53"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "54"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "55"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "tile_position" : "0"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "tile_position" : "7"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_black",
          "tile_position" : "56"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_black",
          "tile_position" : "63"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_white",
          "tile_position" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_white",
          "tile_position" : "6"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "tile_position" : "57"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "tile_position" : "62"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "tile_position" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "tile_position" : "5"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "tile_position" : "58"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "tile_position" : "61"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_white",
          "tile_position" : "4"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_black",
          "tile_position" : "60"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_white",
          "tile_position" : "3"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_black",
          "tile_position" : "59"
        }
      }
    ]
  }
}');

  return $rules;
}

