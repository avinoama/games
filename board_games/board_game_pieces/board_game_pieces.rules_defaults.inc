<?php

/**
 * Implementing Hook_default_rules_configuration
 * This function will create my default game TicTacToe rules
 * @return $rules 
 */
function board_game_pieces_default_rules_configuration() {

  $rules = array();

  $rules['rules_ticktacktoe_on_game_start'] = rules_import('');
  
  return $rules;
}

