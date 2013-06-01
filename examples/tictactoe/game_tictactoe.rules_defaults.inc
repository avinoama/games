<?php

/**
 * Implementing Hook_default_rules_configuration
 * This function will create my default game TicTacToe rules
 * @return $rules
 */
function game_tictactoe_default_rules_configuration() {

  $rules = array();

  $rules['rules_ticktacktoe_on_game_start'] = rules_import('{ "rules_ticktacktoe_on_game_start" : {
    "LABEL" : "TickTackToe On Game Start",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game", "board_games" ],
    "ON" : [ "game_start" ],
    "IF" : [
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "tic-tac-toe" } }
    ],
    "DO" : [
      { "rules_start_game" : { "running_game" : [ "running_game" ], "game" : [ "game" ] } },
      { "rules_game_send_message" : {
          "running_game" : [ "running_game" ],
          "message_text" : "Game started, its player1 turn."
        }
      },
      { "rules_tile_lisiten_to_click" : { "running_game" : [ "running_game" ] } }
    ]
  }
}');
  $rules['rules_ticktacktoe_checkwinner'] = rules_import('{ "rules_ticktacktoe_checkwinner" : {
    "LABEL" : "TickTackToe CheckWinner",
    "PLUGIN" : "rule set",
    "REQUIRES" : [ "board_games", "game" ],
    "USES VARIABLES" : {
      "player_id" : { "label" : "player id", "type" : "integer" },
      "game_running" : { "label" : "Running Game", "type" : "running_game" },
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player-id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player_id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player_id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player_id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player_id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player_id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player_id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
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
            { "rules_game_set_winners" : { "running_game" : [ "game-running" ], "player_id" : [ "player_id" ] } },
            { "rules_game_over" : { "running_game" : [ "game-running" ] } }
          ],
          "LABEL" : "CheckMatrix diagnal2"
        }
      }
    ]
  }
}');




  $rules['rules_tictactoe_checkwinner_2_addition'] = rules_import('{ "rules_tictactoe_checkwinner_2_addition" : {
    "LABEL" : "TickTackToe CheckWinner 2 addition",
    "PLUGIN" : "rule",
    "REQUIRES" : [ "board_games", "game_players", "game" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "RunningGame", "type" : "running_game" },
      "player_id" : { "label" : "PlayerID", "type" : "integer" }
    },
    "IF" : [
      { "OR" : [
          { "board_games_rules_condition_check_row_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "1",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_rules_condition_check_row_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "2",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_rules_condition_check_row_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "3",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_rules_condition_check_column_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "1",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_rules_condition_check_column_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "2",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_rules_condition_check_column_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "3",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_rules_condition_check_diagonal_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "1-1",
              "position_diagonal_type" : "0",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_rules_condition_check_diagonal_equal" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "position" : "1-3",
              "position_diagonal_type" : "1",
              "equal_to" : [ "player-id" ]
            }
          }
        ]
      }
    ],
    "DO" : [
      { "rules_game_set_winners" : { "running_game" : [ "running_game" ], "player_id" : [ "player_id" ] } },
      { "rules_game_over" : { "running_game" : [ "running_game" ] } }
    ]
  }
}');

$rules['rules_tictactoe_checkwinner_3_addition'] = rules_import('{ "rules_ticktacktoe_checkwinner_3_addition" : {
    "LABEL" : "TickTackToe CheckWinner 3 addition",
    "PLUGIN" : "rule",
    "REQUIRES" : [ "board_games", "game_players", "game" ],
    "USES VARIABLES" : {
      "game" : { "label" : "Game", "type" : "game" },
      "running_game" : { "label" : "RunningGame", "type" : "running_game" },
      "player_id" : { "label" : "PlayerID", "type" : "integer" }
    },
    "IF" : [
      { "OR" : [
          { "board_games_check_pattern" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "pattern" : "1",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_check_pattern" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "pattern" : "2",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_check_pattern" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "pattern" : "3",
              "equal_to" : [ "player-id" ]
            }
          },
          { "board_games_check_pattern" : {
              "running_game" : [ "running_game" ],
              "game" : [ "game" ],
              "pattern" : "4",
              "equal_to" : [ "player-id" ]
            }
          }
        ]
      }
    ],
    "DO" : [
      { "rules_game_set_winners" : { "running_game" : [ "running_game" ], "player_id" : [ "player_id" ] } },
      { "rules_game_over" : { "running_game" : [ "running_game" ] } }
    ]
  }
}');


  $rules['rules_ticktacktoe_switchplayer'] = rules_import('{ "rules_ticktacktoe_switchplayer" : {
    "LABEL" : "TickTackToe SwitchPlayer",
    "PLUGIN" : "rule",
    "REQUIRES" : [ "rules", "board_games" ],
    "USES VARIABLES" : { "running_game" : { "label" : "Running Game", "type" : "running_game" } },
    "IF" : [
      { "data_is" : { "data" : [ "running_game:status" ], "op" : "\u003C", "value" : "3" } }
    ],
    "DO" : [ { "rules_game_change_turn" : { "running_game" : [ "running_game" ] } } ]
  }
}');

  $rules['rules_ticktacktoe_game_rules'] = rules_import('{ "rules_ticktacktoe_game_rules" : {
    "LABEL" : "TickTackToe Game Rules",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "board_games" ],
    "ON" : [ "tile_click" ],
    "IF" : [
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
      },
      { "data_is" : { "data" : [ "running_game:status" ], "op" : "\u003C", "value" : "3" } },
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "tic-tac-toe" } }
    ],
    "DO" : [
      { "rules_tile_set_owner" : {
          "running_game" : [ "running_game" ],
          "tile_position" : [ "site:current-tile-clicked" ]
        }
      },
      { "component_rules_ticktacktoe_checkwinner" : {
          "player_id" : [ "site:current-player-id" ],
          "game_running" : [ "running-game" ],
          "game_matrix" : [ "site:current-game-matrix" ]
        }
      },
      { "component_rules_ticktacktoe_switchplayer" : { "running_game" : [ "running_game" ] } }
    ]
  }
}');
 $rules['rules_ticktacktoe_game_join'] = rules_import('{ "rules_ticktacktoe_game_join" : {
    "LABEL" : "TickTackToe Game Join",
    "PLUGIN" : "reaction rule",
    "REQUIRES" : [ "rules", "game_players" ],
    "ON" : [ "game_join" ],
    "IF" : [
      { "data_is" : { "data" : [ "game:machine-name" ], "value" : "tic-tac-toe" } }
    ],
    "DO" : [
      { "rules_player_join_game" : { "running_game" : [ "running_game" ], "game" : [ "game" ] } }
    ]
  }
}');

  return $rules;
}