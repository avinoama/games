<?php

function game_pieces_rules_condition_info() {
  return array(
      'piece_check_initiated_can_evade' => array(
          'group' => 'Piece',
          'label' => t('Piece can evade beaing initiated'),
          'arguments' => array(
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'initiator' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'initiated_piece_type' => array(
                  'type' => 'text',
                  'label' => 'piece_type',
                  'optional' => FALSE,
                  'descritpion' => 'Machine name of piece type',
                  'options list' => 'get_all_piece_types_and_extra_options',
              ),
          ),
          'module' => 'game_pieces',
      ),
      'piece_check_initator_can_be_initiated' => array(
          'group' => 'Piece',
          'label' => t('Initiator can be initiated'),
          'arguments' => array(
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'initiator' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              )
          ),
          'module' => 'game_pieces',
      ),
      'piece_check_valid_move' => array(
          'group' => 'Piece',
          'label' => t('Piece check valide move'),
          'arguments' => array(
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'piece' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'position' => array(
                  'type' => 'list<integer>',
                  'label' => 'Position',
                  'optional' => FALSE,
              )
          ),
          'module' => 'game_pieces',
      ),
      'piece_check_move_pattern' => array(
          'group' => 'Piece',
          'label' => t('Piece check move pattern'),
          'arguments' => array(
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'piece' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'position' => array(
                  'type' => 'list<integer>',
                  'label' => 'Position',
                  'optional' => FALSE,
              )
          ),
          'module' => 'game_pieces',
      ),
      'piece_check_initiate_pattern' => array(
          'group' => 'Piece',
          'label' => t('Piece check initiate pattern'),
          'arguments' => array(
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'initiator' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'initiated' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
          ),
          'module' => 'game_pieces',
      ),
      'piece_can_initiate_piece' => array(
          'group' => 'Piece',
          'label' => t('Piece can initiate piece'),
          'arguments' => array(
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'initiator' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'initiated_piece_type' => array(
                  'type' => 'text',
                  'label' => 'piece_type',
                  'optional' => FALSE,
                  'descritpion' => 'Machine name of piece type',
                  'options list' => 'get_all_piece_types_and_extra_options',
              ),
          ),
          'module' => 'game_pieces',
      ),
  );
}

function game_pieces_rules_action_info() {

  return array(
      'piece_move' => array(
          'label' => t('piece move'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'piece' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'position' => array(
                  'type' => 'list<integer>',
                  'label' => 'position',
                  'optional' => FALSE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'piece_move',
          'callbacks' => array(
              'validate' => 'piece_move_validation',
          ),
      ),
      'piece_remove' => array(
          'label' => t('piece remove'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'piece' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
          ),
          'group' => t('Game Board'),
          'base' => 'piece_remove',
          'callbacks' => array(
              'validate' => 'piece_remove_validation',
          ),
      ),
      'piece_create' => array(
          'label' => t('piece Create'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'piece_type' => array(
                  'type' => 'text',
                  'label' => 'piece_type',
                  'optional' => FALSE,
                  'descritpion' => "Machine name of piece type",
                  'options list' => "get_all_piece_types",
              ),
              'element' => array(
                  'type' => 'text',
                  'label' => 'element',
                  'optional' => TRUE,
              ),
              'position' => array(
                  'type' => 'text',
                  'label' => 'position',
                  'optional' => TRUE,
              ),
              'owned' => array(
                  'type' => 'integer',
                  'label' => 'owned',
                  'optional' => TRUE,
              ),
          ),
          'group' => t('Game Board'),
          'base' => 'piece_create',
          'callbacks' => array(
              'validate' => 'piece_create_validation',
          ),
      ),
  );
}

/**
 * function get_all_piece_types
 * @return array
 */
function get_all_piece_types() {
  $r = array();
  $e = entity_load("piece_type");
  foreach ($e as $val) {
    $r[$val->type] = $val->label;
  }
  return $r;
}

/**
 * function get_all_piece_types_and_extra_options
 * 
 * 
 * @return array
 */
function get_all_piece_types_and_extra_options() {
  $delimiter = "_";
  $r = array();
  $r += module_invoke_all("piece_extra_options");
  $e = entity_load("piece_type");
  foreach ($e as $val) {
    $type = explode($delimiter, $val->type);
    $label = explode(' ', $val->label);
    $r[$type[0]] = $label[0];
  }
  return $r;
}

/**
 * function piece_remove_validation
 *
 * Can always remove piece
 *
 * @todo check maybe we need validation
 *
 * @param type $running_game
 * @param type $piece
 * @return boolean
 */
function piece_remove_validation($running_game = null, $piece = null) {
  return true;
}

/**
 * function piece_remove
 *
 * removes a piece from the game
 *
 * @param type $running_game
 * @param type $piece
 */
function piece_remove($running_game = null, $piece = null) {
  $id = $piece;
  foreach ($running_game->field_pieces[LANGUAGE_NONE] as $key => $val) {
    if ($val['target_id'] == $id) {
      unset($running_game->field_pieces[LANGUAGE_NONE][$key]);
    }
  }
  $running_game->save();

  $running_game_command = array();
  $running_game_command['running_game_id'] = $running_game->id;
  $running_game_command['command_id'] = 1;
  $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "GamePieces", "fn" => "remove_piece", "params" => array("piece" => $piece)), "time" => time()));
  $running_game_command_entity = entity_create("running_game_command", $running_game_command);
  $running_game_command_entity->save();

  piece_delete($piece);
}

/**
 * function piece_create_validation()
 *
 * Validate if the running game can actually hold game pieces
 *
 * @return boolean
 */
function piece_create_validation($running_game = null, $piece_type = null, $position = -1) {
  if (property_exists($running_game, "field_pieces")) {
    return false;
  }
  return true;
}

/**
 * function piece_create()
 *
 * Create an entity called piece
 * In current game
 * By type "piece_type"
 * in position
 * and owned by player
 *
 * @param type $running_game
 * @param type $piece_type
 * @param type $element
 * @param type $position
 * @param type $owend
 */
function piece_create($running_game = null, $piece_type = null, $element = '', $position = '', $owend = -1) {

  // create piece
  $entity_type = "piece";
  $piece = entity_create($entity_type, array());


  $piece_type_entity = reset(entity_load("piece_type", FALSE, array("type" => $piece_type)));
  // load patterns
  $patterns = array();
  if (property_exists($piece_type_entity, 'move_pattern')) {
    if (!empty($piece_type_entity->move_pattern)) {
      $p = game_pattern_load_by_machine_name($piece_type_entity->move_pattern);
      if (!empty($p)) {
        $patterns[$piece_type_entity->move_pattern] = $p;
      }
    }
  }
  if (property_exists($piece_type_entity, 'initiate_pattern')) {
    if (!empty($piece_type_entity->initiate_pattern)) {
      $p = game_pattern_load_by_machine_name($piece_type_entity->initiate_pattern);
      if (!empty($p)) {
        $patterns[$piece_type_entity->initiate_pattern] = $p;
      }
    }
  }
  $piece->label = $piece_type_entity->symbol;
  $piece->type = $piece_type;
  $piece->uid = $owend;
  $positions = explode("-", $position);
  if (!empty($position)) {
    foreach ($positions as $val) {
      $piece->field_position[LANGUAGE_NONE][]['value'] = $val;
    }
  }

  piece_save($piece);

  // put it in running game
  $running_game->field_pieces[LANGUAGE_NONE][]["target_id"] = $piece->id;


  // notify exsting users
  if ($running_game->save()) {
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(array(
        'callback' =>
        array('module' => 'GamePieces',
            'fn' => 'create_piece',
            'params' => array(
                'position' => $position,
                'element' => $element,
                'piece' => $piece,
                'piece_type' => $piece_type_entity,
                'patterns' => $patterns,
        )),
        'time' => time()));
    $running_game_command_entity = entity_create('running_game_command', $running_game_command);
    $running_game_command_entity->save();
  }
}

/**
 * piece_move_validation()
 *
 * The move is valid only if position is positive
 * 
 * @param type $running_game
 * @param type $piece
 * @param type $position
 * @return boolean
 */
function piece_move_validation($running_game = null, $piece = null, $position = -1) {

  if ($position < 0) {
    return false;
  }


  return true;
}

/**
 * piece_move()
 *
 * Update piece to the new position 
 * Send updates to clients
 *
 * @param type $running_game
 * @param type $piece
 * @param type $position
 * 
 */
function piece_move($running_game = null, $piece = null, $position = array()) {

  $piece->field_position[LANGUAGE_NONE] = array();
  $i = 0;
  foreach ($position as $val) {
    $piece->field_position[LANGUAGE_NONE][$i] = array('value' => $val);
    $i++;
  }
  $piece->moved = 1;

  if ($piece->save()) {
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(
            array("callback" =>
                array("module" => "GamePieces", "fn" => "move_piece", "params" =>
                    array("position" => $position, "piece" => $piece)), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }
}

/**
 * function piece_check_can_evade
 * check if a piece evade beaing initiated by another piece can evade
 *
 * 
 * 
 * @param type $game
 * @param type $running_game
 * @param type $piece
 * @return boolean
 */
function piece_check_initiated_can_evade($game = null, $running_game = null, $initiator = null, $initiated_piece_type = null) {

  // take all pieces in game
  $pieces = $running_game->field_pieces[LANGUAGE_NONE];
  $ids = array();
  foreach ($pieces as $p) {
    $ids[] = $p['target_id'];
  }

  // load all game pieces
  $game_pieces = entity_load('piece', $ids);

  // find the one that starts with the word i want
  // example : king  will get king_white and king_black
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'piece')
          ->entityCondition('entity_id', $ids, 'IN')
          ->entityCondition('bundle', $initiated_piece_type, 'STARTS_WITH');
  $result = $query->execute();

  if (isset($result['piece'])) {
    $pids = array_keys($result['piece']);
    $current_initiated_pieces = entity_load('piece', $pids);
  }

  $initiated = null;
  foreach ($current_initiated_pieces as $piece) {
    if ($piece->uid != $initiator->uid) {
      $initiated = $piece;
    }
  }
  if (empty($initiated)) {// if no piece it cant evade
    return FALSE;
  }
  // found initiated
  // load matrix
  $matrix = array();
  foreach ($game_pieces as $game_piece) {
    draw_piece_on_board($game, $matrix, $game_piece);
    if ($initiator->uid == $game_piece->uid) {
      draw_piece_initiation_on_board($game, $matrix, $game_piece);
    }
  }
  // take initiated move pattern
  //
  $initiated_piece_type = piece_types($initiated->type);
  if (empty($initiated_piece_type)) {
    return FALSE;
  }
  $machine_name = $initiated_piece_type->move_pattern;
  $patterns = game_pattern_load_by_machine_name($machine_name);
  $position = array();
  foreach ($initiated->field_position[LANGUAGE_NONE] as $p) {
    $position[] = $p['value'];
  }

  // check if he can move to a diffrent location on board that is not initiated by enemy team
  foreach ($patterns->field_pattern[LANGUAGE_NONE] as $key => $var) {
    $var['value'] = _replace_default_patterns($game, $var['value'], $initiated);
    $pattern = drupal_json_decode($var['value']);

    if (empty($pattern)) {
      continue;
    }

    game_piece_evaluate_pattern($pattern);

    if (isset($pattern['start']) && isset($pattern['end'])) {
      if ($pattern['end']['x'] < $pattern['start']['x'] || $pattern['end']['y'] < $pattern['start']['y']) {
        for ($x = $pattern['start']['x']; $x >= $pattern['end']['x']; $x--) {
          for ($y = $pattern['start']['y']; $y >= $pattern['end']['y']; $y--) {
            if ($x == $position[0] && $y == $position[1] && !isset($matrix[$x][$y])) {
              return TRUE;
            }
            // this pattern cannot continue try another
            if ($over_piece == false && isset($positions[$x][$y])) {
              break 2;
            }
          }
        }
      } else {
        for ($x = $pattern['start']['x']; $x <= $pattern['end']['x']; $x++) {
          for ($y = $pattern['start']['y']; $y <= $pattern['end']['y']; $y++) {
            if ($x == $position[0] && $y == $position[1] && !isset($matrix[$x][$y])) {
              return TRUE;
            }
            // this pattern cannot continue try another
            if ($over_piece == false && isset($positions[$x][$y])) {
              break 2;
            }
          }
        }
      }
    } else if (isset($pattern['start'])) {


      if (isset($pattern['start']['repeat'])) {
        for ($i = 0; $i <= $pattern['start']['repeat']; $i++) {
          $x = ($pattern['start']['x'] + ($pattern ['start']['offsetx'] * $i));
          $y = ($pattern['start']['y'] + ($pattern['start']['offsety'] * $i));
          if ($x == $position[0] && $y == $position[1] && !isset($matrix[$x][$y])) {
            return TRUE;
          }
          // this pattern cannot continue try another
          if ($over_piece == false && isset($positions[$x][$y])) {
            break;
          }
        }
      } else {
        $x = $pattern['start']['x'];
        $y = $pattern['start']['y'];
        /* if ($over_piece == false && isset($positions[$x][$y])) {
          return FALSE;
          } */
        if (!isset($matrix[$x][$y])) {
          return TRUE;
        }
      }
    }
  }


  return FALSE;
}

/**
 *
 * @param type $game
 * @param array $matrix
 * @param type $piece
 */
function draw_piece_on_board(&$game, &$matrix, &$piece) {
  $position = $piece->field_position[LANGUAGE_NONE];
  $matrix[$position[0]['value']][$position[1]['value']] = $piece->id;
}

/**
 *
 * @param type $game
 * @param type $matrix
 * @param type $piece
 * @return boolean
 */
function draw_piece_initiation_on_board(&$game, &$matrix, &$piece) {
  $piece_type = piece_types($piece->type);
  if (empty($piece_type)) {
    return;
  }
  if (!property_exists($piece_type, "initiate_pattern")) {
    return;
  }
  $machine_name = $piece_type->initiate_pattern;
  $patterns = game_pattern_load_by_machine_name($machine_name);
  if (empty($patterns)) {
    return;
  }
  if (!empty($running_game) && property_exists($running_game, 'field_pieces')) {
    // take all pieces in game
    $pieces = $running_game->field_pieces[LANGUAGE_NONE];
    $ids = array();
    foreach ($pieces as $p) {
      if ($piece->id == $p['target_id']) {
        continue;
      }
      $ids[] = $p['target_id'];
    }
    // load all game pieces
    $game_pieces = entity_load('piece', $ids);
    $positions = array();
    foreach ($game_pieces as $game_piece) {
      $pos = $game_piece->field_position[LANGUAGE_NONE];
      $positions[$pos[0]['value']][$pos[1]['value']] = true;
    }
  }

  foreach ($patterns->field_pattern[LANGUAGE_NONE] as $key => $var) {
    if (property_exists($patterns, 'field_over_piece')) {
      $over_piece = $patterns->field_over_piece[LANGUAGE_NONE][0]['value'];
    }
    $var['value'] = _replace_default_patterns($game, $var['value'], $piece);


    $pattern = drupal_json_decode($var['value']);

    if (empty($pattern)) {
      continue;
    }

    game_piece_evaluate_pattern($pattern);

    if (isset($pattern['start']) && isset($pattern['end'])) {
      if ($pattern['end']['x'] < $pattern['start']['x'] || $pattern['end']['y'] < $pattern['start']['y']) {
        for ($x = $pattern['start']['x']; $x >= $pattern['end']['x']; $x--) {
          for ($y = $pattern['start']['y']; $y >= $pattern['end']['y']; $y--) {
            if (!isset($matrix[$x])) {
              $matrix[$x] = array();
            }
            if (!isset($matrix[$x][$y])) {
              $matrix[$x][$y] = 'initiation';
            }
            // this pattern cannot continue try another
            if ($over_piece == false && isset($positions[$x][$y])) {
              break 2;
            }
          }
        }
      } else {
        for ($x = $pattern['start']['x']; $x <= $pattern['end']['x']; $x++) {
          for ($y = $pattern['start']['y']; $y <= $pattern['end']['y']; $y++) {
            if (!isset($matrix[$x])) {
              $matrix[$x] = array();
            }
            if (!isset($matrix[$x][$y])) {
              $matrix[$x][$y] = 'initiation';
            }
            // this pattern cannot continue try another
            if ($over_piece == false && isset($positions[$x][$y])) {
              break 2;
            }
          }
        }
      }
    } else if (isset($pattern['start'])) {


      if (isset($pattern['start']['repeat'])) {
        for ($i = 0; $i <= $pattern['start']['repeat']; $i++) {
          $x = ($pattern['start']['x'] + ($pattern ['start']['offsetx'] * $i));
          $y = ($pattern['start']['y'] + ($pattern['start']['offsety'] * $i));
          if (!isset($matrix[$x])) {
            $matrix[$x] = array();
          }
          if (!isset($matrix[$x][$y])) {
            $matrix[$x][$y] = 'initiation';
          }
          // this pattern cannot continue try another
          if ($over_piece == false && isset($positions[$x][$y])) {
            break;
          }
        }
      } else {
        $x = $pattern['start']['x'];
        $y = $pattern['start']['y'];
        /* if ($over_piece == false && isset($positions[$x][$y])) {
          return FALSE;
          } */
        if (!isset($matrix[$x])) {
          $matrix[$x] = array();
        }
        if (!isset($matrix[$x][$y])) {
          $matrix[$x][$y] = 'initiation';
        }
      }
    }
  }
}

/**
 * function piece_check_valid_move
 *
 * will invoke component (Condition set) that describe the movment of the piece
 * 
 * @param type $piece
 * @param type $position
 * @return boolean
 */
function piece_check_valid_move($game = null, $running_game = null, $piece = null, $position = array()) {
  $c = 'rules_' . $piece->type . '_move_conditions';
  $return = rules_invoke_component($c, $game, $running_game, $piece, $position);
  return (!$return) ? FALSE : TRUE;
}

/**
 * function piece_can_initiate_piece
 * 
 * Check if piece can initiate on another piece type
 * Other player can have many piece types
 *
 * @todo maybe alllow to initiate an action on initiator pieces or just another single player
 *
 * @param type $game
 * @param type $running_game
 * @param type $initiator
 * @param type $initiated_piece_type
 * @return boolean
 */
function piece_can_initiate_piece($game, $running_game, $initiator, $initiated_piece_type) {

  // take all pieces in game
  $pieces = $running_game->field_pieces[LANGUAGE_NONE];
  $ids = array();
  foreach ($pieces as $p) {
    $ids[] = $p['target_id'];
  }
  // find the one that starts with the word i want
  // example : king  will get king_white and king_black
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'piece')
          ->entityCondition('entity_id', $ids, 'IN')
          ->entityCondition('bundle', $initiated_piece_type, 'STARTS_WITH');
  $result = $query->execute();

  if (isset($result['piece'])) {
    $pids = array_keys($result['piece']);
    $current_pieces = entity_load('piece', $pids);
  }

  // Foreach player that is of "piece type" in the game
  // check if piece is not the owned by the initiator
  // try to initiate from $initiator to this given piece

  foreach ($current_pieces as $piece) {
    if ($piece->uid != $initiator->uid) {
      if (piece_check_initiate_pattern($game, $running_game, $initiator, $piece)) {
        return TRUE;
      }
    }
  }

  return FALSE;
}

function piece_check_initiate_pattern($game = null, $running_game, $initiator, $initiated) {
  $piece_type = piece_types($initiator->type);
  if (!property_exists($piece_type, "initiate_pattern")) {
    return FALSE;
  }
  $machine_name = $piece_type->initiate_pattern;
  $patterns = game_pattern_load_by_machine_name($machine_name);
  if (empty($patterns)) {
    return FALSE;
  }

  $position = array(
      0 => $initiated->field_position[LANGUAGE_NONE][0]['value'],
      1 => $initiated->field_position[LANGUAGE_NONE][1]['value']
  );


  $re = piece_check_valid_patterns($game, $running_game, $patterns, $initiator, $position);
  return $re;
}

function piece_check_move_pattern($game = null, $running_game, $piece, $position) {
  $piece_type = piece_types($piece->type);
  if (!property_exists($piece_type, "move_pattern")) {
    return FALSE;
  }
  $machine_name = $piece_type->move_pattern;
  $patterns = game_pattern_load_by_machine_name($machine_name);
  //$patterns = game_pattern_load($id);
  if (empty($patterns)) {
    return FALSE;
  }
  $re = piece_check_valid_patterns($game, $running_game, $patterns, $piece, $position);
  return $re;
}

/**
 * function piece_check_valid_patterns
 *
 * @param type $game
 * @param type $patterns
 * @param type $piece
 * @param type $position
 * @return boolean
 */
function piece_check_valid_patterns($game, $running_game = null, $patterns, $piece, $position) {
  if (!empty($running_game) && property_exists($running_game, 'field_pieces')) {
    // take all pieces in game
    $pieces = $running_game->field_pieces[LANGUAGE_NONE];
    $ids = array();
    foreach ($pieces as $p) {
      if ($piece->id == $p['target_id']) {
        continue;
      }
      $ids[] = $p['target_id'];
    }
    // load all game pieces
    $game_pieces = entity_load('piece', $ids);
    $positions = array();
    foreach ($game_pieces as $game_piece) {
      $pos = $game_piece->field_position[LANGUAGE_NONE];
      $positions[$pos[0]['value']][$pos[1]['value']] = true;
    }
  }


  foreach ($patterns->field_pattern[LANGUAGE_NONE] as $key => $var) {
    if (property_exists($patterns, 'field_over_piece')) {
      $over_piece = $patterns->field_over_piece[LANGUAGE_NONE][0]['value'];
    }

    $var['value'] = str_replace("px", $piece->field_position[LANGUAGE_NONE][0]['value'], $var['value']);
    $var['value'] = str_replace("py", $piece->field_position[LANGUAGE_NONE][1]['value'], $var['value']);
    if (!empty($game) && property_exists($game, 'field_board_dimension_amount')) {
      //
      $var['value'] = str_replace("left", '1', $var['value']);
      $var['value'] = str_replace("right", $game->field_board_dimension_amount[LANGUAGE_NONE][0]['value'], $var['value']);
      //
      $var['value'] = str_replace("top", '1', $var['value']);
      $var['value'] = str_replace("bottom", $game->field_board_dimension_amount[LANGUAGE_NONE][1]['value'], $var['value']);
      // prepering for 3d z exis
      if (isset($game->field_board_dimension_amount[LANGUAGE_NONE][2])) {
        $var['value'] = str_replace("back", '1', $var['value']);
        $var['value'] = str_replace("front", $game->field_board_dimension_amount[LANGUAGE_NONE][2]['value'], $var['value']);
      }
    }

    $pattern = drupal_json_decode($var['value']);

    if (empty($pattern)) {
      // error json didnot eval correct
      return FALSE;
    }

    game_piece_evaluate_pattern($pattern);

    if (isset($pattern['start']) && isset($pattern['end'])) {
      if ($pattern['end']['x'] < $pattern['start']['x'] || $pattern['end']['y'] < $pattern['start']['y']) {
        for ($x = $pattern['start']['x']; $x >= $pattern['end']['x']; $x--) {
          for ($y = $pattern['start']['y']; $y >= $pattern['end']['y']; $y--) {
            if ($x == $position[0] && $y == $position[1]) {
              return TRUE;
            }
            // this pattern cannot continue try another
            if ($over_piece == false && isset($positions[$x][$y])) {
              break 2;
            }
          }
        }
      } else {
        for ($x = $pattern['start']['x']; $x <= $pattern['end']['x']; $x++) {
          for ($y = $pattern['start']['y']; $y <= $pattern['end']['y']; $y++) {
            if ($x == $position[0] && $y == $position[1]) {
              return TRUE;
            }
            // this pattern cannot continue try another
            if ($over_piece == false && isset($positions[$x][$y])) {
              break 2;
            }
          }
        }
      }
    } else if (isset($pattern['start'])) {


      if (isset($pattern['start']['repeat'])) {
        for ($i = 0; $i <= $pattern['start']['repeat']; $i++) {
          $x = ($pattern['start']['x'] + ($pattern ['start']['offsetx'] * $i));
          $y = ($pattern['start']['y'] + ($pattern['start']['offsety'] * $i));
          if ($x == $position[0] && $y == $position[1]) {
            return TRUE;
          }
          // this pattern cannot continue try another
          if ($over_piece == false && isset($positions[$x][$y])) {
            break;
          }
        }
      } else {
        $x = $pattern['start']['x'];
        $y = $pattern['start']['y'];
        /* if ($over_piece == false && isset($positions[$x][$y])) {
          return FALSE;
          } */
        if ($x == $position[0] && $y == $position[1]) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/**
 * function game_piece_evaluate_pattern
 *
 * Designed to take a pattern and evaluate the answer
 *
 * @param type $pattern
 */
function game_piece_evaluate_pattern(&$pattern) {

  if (!is_numeric($pattern['start']['x']) && !empty($pattern['start']['x'])) {
    //$pattern['start']['x'] = eval("return (".$pattern['start']['x'].");");
    $pattern['start']['x'] = calculate_string($pattern['start']['x']);
  }
  if (!is_numeric($pattern['start']['y']) && !empty($pattern['start']['y'])) {
    //$pattern['start']['y'] = eval("return (".$pattern['start']['y'].");");
    $pattern['start']['y'] = calculate_string($pattern['start']['y']);
  }
  if (isset($pattern['end'])) {
    if (!is_numeric($pattern['end']['x']) && !empty($pattern['end']['x'])) {
      //$pattern['end']['x'] = eval("return (".$pattern['end']['x'].");");
      $pattern['end']['x'] = calculate_string($pattern['end']['x']);
    }
    if (!is_numeric($pattern['end']['y']) && !empty($pattern['end']['y'])) {
      //$pattern['end']['y'] = eval("return (".$pattern['end']['y'].");");
      $pattern['end']['y'] = calculate_string($pattern['end']['y']);
    }
  }
}

/**
 * function calculate_string
 *
 * instead of eval actually does the same thing but with only numbers
 * 
 * @param type $mathString
 * @return number
 */
function calculate_string($mathString) {
  $mathString = trim($mathString);     // trim white spaces
  $mathString = preg_replace('[^0-9\+-\*\/\(\) ]', '', $mathString);    // remove any non-numbers chars; exception for math operators

  $compute = create_function("", "return (" . $mathString . ");");
  return 0 + $compute();
}

/**
 * function Hook_rules_event_info
 * @return array
 */
function game_pieces_rules_event_info() {
  $items = array(
      'piece_move_to_position' => array(
          'label' => t('Piece Move to Position'),
          'group' => t('Game Rules'),
          'variables' => array(
              'piece' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'position' => array(
                  'type' => 'list<integer>',
                  'label' => t('position'),
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => t('Running Game'),
              ),
              'game' => array(
                  'type' => 'game',
                  'label' => t('Game'),
              ),
          ),
      ),
      'piece_initiate' => array(
          'label' => t('Piece Initiate'),
          'group' => t('Game Rules'),
          'variables' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => t('Running Game'),
              ),
              'game' => array(
                  'type' => 'game',
                  'label' => t('Game'),
              ),
              'initiator' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'initiated' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
          ),
      ),
  );

  return $items;
}

function _replace_default_patterns(&$game, $pattern, &$piece) {
  $pattern = str_replace("px", $piece->field_position[LANGUAGE_NONE][0]['value'], $pattern);
  if (isset($piece->field_position[LANGUAGE_NONE][1])) {
    $pattern = str_replace("py", $piece->field_position[LANGUAGE_NONE][1]['value'], $pattern);
  }
  if (isset($piece->field_position[LANGUAGE_NONE][2])) {
    $pattern = str_replace("pz", $piece->field_position[LANGUAGE_NONE][2]['value'], $pattern);
  }
  if (!empty($game) && property_exists($game, 'field_board_dimension_amount')) {
    if (isset($game->field_board_dimension_amount[LANGUAGE_NONE][0])) {
      $pattern = str_replace("left", '1', $pattern);
      $pattern = str_replace("right", $game->field_board_dimension_amount[LANGUAGE_NONE][0]['value'], $pattern);
    }
    if (isset($game->field_board_dimension_amount[LANGUAGE_NONE][1])) {
      $pattern = str_replace("top", '1', $pattern);
      $pattern = str_replace("bottom", $game->field_board_dimension_amount[LANGUAGE_NONE][1]['value'], $pattern);
    }
    // prepering for 3d z exis
    if (isset($game->field_board_dimension_amount[LANGUAGE_NONE][2])) {
      $pattern = str_replace("back", '1', $pattern);
      $pattern = str_replace("front", $game->field_board_dimension_amount[LANGUAGE_NONE][2]['value'], $pattern);
    }
  }
  return $pattern;
}