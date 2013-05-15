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
          "position" : "2-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "2-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "2-3",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "2-4",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "2-5",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "position" : "8-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "position" : "8-8",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_black",
          "position" : "1-8",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_black",
          "position" : "1-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_white",
          "position" : "8-7",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_white",
          "position" : "8-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "position" : "1-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "position" : "1-7",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "position" : "8-3",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "position" : "8-6",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "position" : "1-3",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "position" : "1-6",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_white",
          "position" : "8-4",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_black",
          "position" : "1-4",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_white",
          "position" : "8-5",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_black",
          "position" : "1-5",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-1",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-2",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-3",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-4",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-5",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-6",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-7",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "7-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "2-6",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "2-7",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "2-8",
          "owned" : "2"
        }
      },
      { "rules_start_game" : { "running_game" : [ "running_game" ], "game" : [ "game" ] } }
    ]
  }
}');





  $rules['rules_chess_on_move_piece'] = rules_import('{ "rules_chess_on_move_piece" : {
    "LABEL" : "rules chess on move piece",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "game_pieces" ],
    "ON" : [ "piece_move_to_position" ],
    "IF" : [
      { "piece_check_valid_move" : { "piece" : [ "piece" ], "position" : [ "position" ] } }
    ],
    "DO" : [
      { "piece_move" : {
          "running_game" : [ "running_game" ],
          "piece" : [ "piece" ],
          "position" : [ "position" ]
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
      "position" : { "label" : "Position", "type" : "list" }
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
      { "NOT data_is" : { "data" : [ "initiator:uid" ], "value" : [ "initiated:uid" ] } },
      { "entity_has_field" : { "entity" : [ "initiated" ], "field" : "field_position" } }
    ],
    "DO" : [
      { "piece_move" : {
          "running_game" : [ "running_game" ],
          "piece" : [ "initiator" ],
          "position" : [ "initiated:field-position" ]
        }
      },
      { "piece_remove" : { "running_game" : [ "running_game" ], "piece" : [ "initiated" ] } }
    ]
  }
}');
  
  return $rules;
}

