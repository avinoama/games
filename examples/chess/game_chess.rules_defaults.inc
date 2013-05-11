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
          "piece_type" : "pawn_black",
          "tile_position" : "51",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "52",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "53",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "54",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "55",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "tile_position" : "0",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "tile_position" : "7",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_black",
          "tile_position" : "56",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_black",
          "tile_position" : "63",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_white",
          "tile_position" : "1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_white",
          "tile_position" : "6",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "tile_position" : "57",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "tile_position" : "62",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "tile_position" : "2",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "tile_position" : "5",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "tile_position" : "58",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "tile_position" : "61",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_white",
          "tile_position" : "4",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_black",
          "tile_position" : "60",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_white",
          "tile_position" : "3",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_black",
          "tile_position" : "59",
          "owned" : "2"
        }
      },
      { "rules_start_game" : { "running_game" : [ "running_game" ], "game" : [ "game" ] } },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "9",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "10",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "11",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "12",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "13",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "14",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "tile_position" : "15",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "48",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "49",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "tile_position" : "50",
          "owned" : "2"
        }
      }
    ]
  }
}');





  $rules['rules_chess_on_move_piece'] = rules_import('{ "rules_rules_chess_on_move_piece" : {
    "LABEL" : "rules chess on move piece",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "game_pieces" ],
    "ON" : [ "piece_move_to_tile" ],
    "DO" : [
      { "piece_move" : {
          "running_game" : [ "running_game" ],
          "piece" : [ "piece" ],
          "tile_position" : [ "tile_position" ]
        }
      }
    ]
  }
}');

  $rules['rules_pawn_white_move_conditions'] = rules_import('{ "rules_pawn_white_move_conditions" : {
    "LABEL" : "pawn white move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "rules" ],
    "USES VARIABLES" : {
      "piece" : { "label" : "Piece", "type" : "piece" },
      "move_to" : { "label" : "move_to", "type" : "integer" }
    },
    "OR" : [
      { "data_is" : {
          "data" : [ "piece:position" ],
          "value" : { "select" : "move-to", "num_offset" : { "value" : "8" } }
        }
      }
    ]
  }
}');

  $rules['rules_chess_game'] = rules_import('{ "rules_chess_game" : {
    "LABEL" : "Chess Game",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "game" ],
    "ON" : [ "game_create_running_instance" ],
    "DO" : []
  }
}');

  $rules['rules_chess_on_join'] = rules_import('{ "rules_chess_on_join" : {
    "LABEL" : "Chess on join",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game_players" ],
    "ON" : [ "game_join" ],
    "IF" : [
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "chess" } },
      { "entity_has_field" : { "entity" : [ "game" ], "field" : "field_min_num_players" } },
      { "entity_has_field" : { "entity" : [ "game" ], "field" : "field_max_num_players" } },
      { "entity_has_field" : { "entity" : [ "running-game" ], "field" : "field_players" } }
    ],
    "DO" : [
      { "rules_player_join_game" : { "running_game" : [ "running_game" ], "game" : [ "game" ] } }
    ]
  }
}');

  
  $rules['rules_chess_on_piece_initiate'] = rules_import('{ "rules_chess_on_piece_initiate" : {
    "LABEL" : "Chess on piece initiate",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game_pieces" ],
    "ON" : [ "piece_initiate" ],
    "IF" : [
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "chess" } },
      { "NOT data_is" : { "data" : [ "initiator:id" ], "value" : [ "initiated:id" ] } },
      { "NOT data_is" : { "data" : [ "initiator:uid" ], "value" : [ "initiated:uid" ] } }
    ],
    "DO" : [
      { "piece_move" : {
          "running_game" : [ "running_game" ],
          "piece" : [ "initiator" ],
          "tile_position" : [ "initiated:position" ]
        }
      },
      { "piece_remove" : { "running_game" : [ "running_game" ], "piece" : [ "initiated" ] } }
    ]
  }
}');
  
  return $rules;
}

