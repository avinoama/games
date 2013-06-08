<?php

function game_pieces_rules_condition_info() {
  return array(
      'piece_check_valid_move' => array(
          'group' => 'Piece',
          'label' => t('Piece check valide move'),
          'arguments' => array(
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
      'piece_move_to_element' => array(
          'label' => t('piece move to element'),
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
              'element_id' => array(
                  'type' => 'text',
                  'label' => 'element_id',
                  'optional' => FALSE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'piece_move_to_element',
          'callbacks' => array(
              'validate' => 'piece_move_to_element_validation',
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
 * get_all_piece_types
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

function piece_move_to_element_validation($running_game = null, $piece_type = null, $element_id = -1) {
  
}

function piece_move_to_element($running_game = null, $piece_type = null, $element_id = -1) {

}

function piece_remove_validation($running_game = null, $piece = null) {
  return true;
}

function piece_remove($running_game = null, $piece = null) {

  $running_game_command = array();
  $running_game_command['running_game_id'] = $running_game->id;
  $running_game_command['command_id'] = 1;
  $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "GamePieces", "fn" => "remove_piece", "params" => array("piece" => $piece)), "time" => time()));
  $running_game_command_entity = entity_create("running_game_command", $running_game_command);
  $running_game_command_entity->save();
  piece_delete($piece);
}

/**
 * function piece_create_validation() {
 * @return boolean
 */
function piece_create_validation($running_game = null, $piece_type = null, $position = -1) {
  if (property_exists($running_game, "field_pieces")) {
    return false;
  }
  return true;
}

function piece_create($running_game = null, $piece_type = null, $element = '', $position = '', $owend = -1) {

  // create piece
  $entity_type = "piece";
  $piece = entity_create($entity_type, array());

  $piece_type_entity = reset(entity_load("piece_type", FALSE, array("type" => $piece_type)));

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
    $running_game_command['command_data'] = drupal_json_encode(array("callback" =>
        array("module" => "GamePieces",
            "fn" => "create_piece",
            "params" => array("position" => $position,
                'element' => $element,
                "piece" => $piece,
                "piece_type" => $piece_type)),
        "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }
}

function piece_move_validation($running_game = null, $piece = null, $position = -1) {

  if ($position < 0) {
    return false;
  }


  return true;
}

/**
 *
 * @param type $running_game
 * @param type $piece
 * @param type $position
 */
function piece_move($running_game = null, $piece = null, $position = array()) {
  $piece->field_position[LANGUAGE_NONE] = array();
  $i = 0;
  foreach ($position as $val) {
    $piece->field_position[LANGUAGE_NONE][$i] = array('value' => $val);
    $i++;
  }


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
  return true;
}

/**
 *
 * @param type $piece
 * @param type $position
 * @return boolean
 */
function piece_check_valid_move($piece = null, $position = array()) {

  $c = 'rules_' . $piece->type . '_move_conditions';
  $return = rules_invoke_component($c, $piece, $position);

  if (!$return) {
    return false;
  }
  return true;
}

function piece_check_initiate_pattern($initiator, $initiated) {

}

function piece_check_move_pattern($piece, $position) {
  $piece_type = piece_types($piece->type);
  if (!property_exists($piece_type, "move_pattern")) {
    return false;
  }
  $id = $piece_type->move_pattern;
  $patterns = game_pattern_load($id);
  if (empty($patterns)) {
    return false;
  }
  foreach ($patterns->field_pattern[LANGUAGE_NONE] as $key => $var) {
    
    $var['value'] = str_replace("px", $piece->field_position[LANGUAGE_NONE][0]['value'], $var['value']);
    $var['value'] = str_replace("py", $piece->field_position[LANGUAGE_NONE][1]['value'], $var['value']);

    $pattern = drupal_json_decode($var['value']);

    if (empty($pattern)) {
      // error json didnot eval correct
      return false;
    }
    if (isset($pattern['start'])) {
      game_piece_evaluate_pattern($pattern);
      $x = $pattern['start']['x'];
      $y = $pattern['start']['y'];
      if ($x == $position[0]
              && $y == $position[1]) {
        return TRUE;
      }
    }
  }

  return FALSE;
}
function game_piece_evaluate_pattern(&$pattern) {

  if (!is_numeric($pattern['start']['x']) && !empty($pattern['start']['x'])) {
    //$pattern['start']['x'] = eval("return (".$pattern['start']['x'].");");
    $pattern['start']['x'] = calculate_string($pattern['start']['x']);
  }
  if (!is_numeric($pattern['start']['y'])  && !empty($pattern['start']['y'])) {
    //$pattern['start']['y'] = eval("return (".$pattern['start']['y'].");");
    $pattern['start']['y'] = calculate_string($pattern['start']['y']);
  }
  if (!is_numeric($pattern['end']['x']) && !empty($pattern['end']['x'])) {
    //$pattern['end']['x'] = eval("return (".$pattern['end']['x'].");");
    $pattern['end']['x'] = calculate_string($pattern['end']['x']);
  }
  if (!is_numeric($pattern['end']['y']) && !empty($pattern['end']['y'])) {
    //$pattern['end']['y'] = eval("return (".$pattern['end']['y'].");");
    $pattern['end']['y'] = calculate_string($pattern['end']['y']);
  }
}
function calculate_string( $mathString )    {
    $mathString = trim($mathString);     // trim white spaces
    $mathString = ereg_replace ('[^0-9\+-\*\/\(\) ]', '', $mathString);    // remove any non-numbers chars; exception for math operators

    $compute = create_function("", "return (" . $mathString . ");" );
    return 0 + $compute();
}
/**
 * Hook_rules_event_info
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