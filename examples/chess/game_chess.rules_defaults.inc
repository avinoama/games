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
          "position" : "1-2",
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
          "position" : "3-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "4-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "5-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "position" : "1-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_white",
          "position" : "8-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "rook_black",
          "position" : "8-1",
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
          "position" : "7-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_white",
          "position" : "2-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "position" : "2-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "knight_black",
          "position" : "7-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "position" : "3-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_white",
          "position" : "6-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "position" : "3-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "bishop_black",
          "position" : "6-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_white",
          "position" : "4-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "king_black",
          "position" : "4-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_white",
          "position" : "5-8",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "queen_black",
          "position" : "5-1",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "1-7",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "2-7",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "3-7",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "4-7",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "5-7",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_white",
          "position" : "6-7",
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
          "position" : "8-7",
          "owned" : "1"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "6-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "7-2",
          "owned" : "2"
        }
      },
      { "piece_create" : {
          "running_game" : [ "running_game" ],
          "piece_type" : "pawn_black",
          "position" : "8-2",
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
    "REQUIRES" : [ "game_pieces", "rules" ],
    "ON" : [ "piece_move_to_position" ],
    "IF" : [
      { "piece_check_valid_move" : {
          "game" : [ "game" ],
          "running_game" : [ "running_game" ],
          "piece" : [ "piece" ],
          "position" : [ "position" ]
        }
      }
    ],
    "DO" : [
      { "piece_move" : {
          "running_game" : [ "running_game" ],
          "piece" : [ "piece" ],
          "position" : [ "position" ]
        }
      },
      { "component_rules_chess_check_winner" : {
          "game" : [ "game" ],
          "running_game" : [ "running_game" ],
          "last_piece" : [ "piece" ],
          "current_player_id" : [ "piece:uid" ]
        }
      }
    ]
  }
}');

  $rules['rules_pawn_white_move_conditions'] = rules_import('{ "rules_pawn_white_move_conditions" : {
    "LABEL" : "pawn white move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces", "rules" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : {
          "game" : [ "game" ],
          "running_game" : [ "running_game" ],
          "piece" : [ "piece" ],
          "position" : [ "position" ]
        }
      },
      { "OR" : [ { "data_is" : { "data" : [ "piece:moved" ], "value" : "0" } } ] }
    ]
  }
}');

  $rules['rules_pawn_black_move_conditions'] = rules_import('{ "rules_pawn_black_move_conditions" : {
    "LABEL" : "pawn black move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ],  "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');

  $rules['rules_king_white_move_conditions'] = rules_import('{ "rules_king_white_move_conditions" : {
    "LABEL" : "king white move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');

  $rules['rules_king_black_move_conditions'] = rules_import('{ "rules_king_black_move_conditions" : {
    "LABEL" : "king black move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');

  $rules['rules_queen_white_move_conditions'] = rules_import('{ "rules_queen_white_move_conditions" : {
    "LABEL" : "queen white move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');
  $rules['rules_queen_black_move_conditions'] = rules_import('{ "rules_queen_black_move_conditions" : {
    "LABEL" : "queen black move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');
//----------------------------------
  $rules['rules_bishop_white_move_conditions'] = rules_import('{ "rules_bishop_white_move_conditions" : {
    "LABEL" : "bishop white move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');
  $rules['rules_bishop_black_move_conditions'] = rules_import('{ "rules_bishop_black_move_conditions" : {
    "LABEL" : "bishop black move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');
//----------------------------------
  $rules['rules_rook_white_move_conditions'] = rules_import('{ "rules_rook_white_move_conditions" : {
    "LABEL" : "rook white move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');
  $rules['rules_rook_black_move_conditions'] = rules_import('{ "rules_rook_black_move_conditions" : {
    "LABEL" : "rook black move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');

//---------------------------
  $rules['rules_knight_white_move_conditions'] = rules_import('{ "rules_knight_white_move_conditions" : {
    "LABEL" : "knight white move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
    ]
  }
}');

  $rules['rules_knight_black_move_conditions'] = rules_import('{ "rules_knight_black_move_conditions" : {
    "LABEL" : "knight black move conditions",
    "PLUGIN" : "or",
    "REQUIRES" : [ "game_pieces" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "running_game", "type" : "running_game" },
      "piece" : { "label" : "Piece", "type" : "piece" },
      "position" : { "label" : "Position", "type" : "list\u003Cinteger\u003E" }
    },
    "OR" : [
      { "piece_check_move_pattern" : { "game" : [ "game" ], "running_game" : [ "running_game" ], "piece" : [ "piece" ], "position" : [ "position" ] } }
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
      { "entity_has_field" : { "entity" : [ "initiated" ], "field" : "field_position" } },
      { "piece_check_initiate_pattern" : {
          "game" : [ "game" ],
          "running_game" : [ "running_game" ],
          "initiator" : [ "initiator" ],
          "initiated" : [ "initiated" ]
        }
      }
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




  $rules['rules_chess_check_winner'] = rules_import('{ "rules_chess_check_winner" : {
    "LABEL" : "chess check winner",
    "PLUGIN" : "rule set",
    "REQUIRES" : [ "game_pieces", "rules", "game" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "RunningGame", "type" : "running_game" },
      "last_piece" : { "label" : "Last Piece Moved Or Initiated", "type" : "piece" },
      "current_player_id" : { "label" : "CurrentPlayerID", "type" : "integer" }
    },
    "RULES" : [
      { "RULE" : { "DO" : [], "LABEL" : "Two knights endgame" } },
      { "RULE" : {
          "IF" : [
            { "piece_can_initiate_piece" : {
                "game" : [ "game" ],
                "running_game" : [ "running_game" ],
                "initiator" : [ "last-piece" ],
                "initiated_piece_type" : "king"
              }
            }
          ],
          "DO" : [
            { "rules_game_send_message" : {
                "running_game" : [ "running_game" ],
                "message_text" : "Check from [last-piece:label]"
              }
            },
            { "component_rules_chess_check_checkmate" : {
                "game" : [ "game" ],
                "running_game" : [ "running_game" ],
                "last_piece" : [ "last_piece" ],
                "current_player_id" : [ "current_player_id" ]
              }
            }
          ],
          "LABEL" : "Check"
        }
      }
    ]
  }
}');

 $rules['rules_chess_check_checkmate'] = rules_import('{ "rules_chess_check_checkmate" : {
    "LABEL" : "chess check mate",
    "PLUGIN" : "rule",
    "REQUIRES" : [ "game_pieces", "game", "game_players" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "RunningGame", "type" : "running_game" },
      "last_piece" : { "label" : "Last Piece Moved Or Initiated", "type" : "piece" },
      "current_player_id" : { "label" : "CurrentPlayerID", "type" : "integer" }
    },
    "IF" : [
      { "NOT piece_check_initiated_can_evade" : {
          "game" : [ "game" ],
          "running_game" : [ "running_game" ],
          "initiator" : [ "last-piece" ],
          "initiated_piece_type" : "king"
        }
      },
      { "NOT piece_check_initator_can_be_initiated" : {
          "game" : [ "game" ],
          "running_game" : [ "running_game" ],
          "initiator" : [ "last-piece" ]
        }
      },
      { "NOT piece_check_initiation_can_be_blocked" : {
          "game" : [ "game" ],
          "running_game" : [ "running_game" ],
          "initiator" : [ "last-piece" ],
          "initiated_piece_type" : "king"
        }
      }
    ],
    "DO" : [
      { "rules_game_send_message" : { "running_game" : [ "running_game" ], "message_text" : "Mate" } },
      { "rules_game_set_winners" : {
          "running_game" : [ "running_game" ],
          "player_id" : [ "current-player-id" ]
        }
      }
    ]
  }
}');





  return $rules;
}

