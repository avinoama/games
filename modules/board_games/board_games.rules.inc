<?php

/**
 *
 * @return type
 */
function board_games_rules_condition_info() {
  return array(
      'board_games_rules_condition_check_row_equal' => array(
          'group' => 'game',
          'label' => t('Board check row'),
          'description' => 'this rule evalutes a row for a number',
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'position' => array(
                  'type' => 'integer',
                  'label' => 'Position',
                  'optional' => TRUE,
                  'description' => 'the position of the row in 1d there is always one row in 2d its a number.',
              ),
              'equal_to' => array(
                  'type' => 'integer',
                  'label' => 'equal to',
                  'description' => 'the number you want to check the row for.',
                  'optional' => FALSE,
              ),
          ),
          'module' => 'board_games',
      ),
      'board_games_rules_condition_check_column_equal' => array(
          'group' => 'game',
          'label' => t('Board check column'),
          'description' => 'this rule evalutes a row for a number',
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'position' => array(
                  'type' => 'integer',
                  'label' => 'Position',
                  'optional' => TRUE,
                  'description' => 'the position of the column.',
              ),
              'equal_to' => array(
                  'type' => 'integer',
                  'label' => 'equal to',
                  'description' => 'the number you want to check the column for.',
                  'optional' => FALSE,
              ),
          ),
          'module' => 'board_games',
      ),
      'board_games_rules_condition_check_diagonal_equal' => array(
          'group' => 'game',
          'label' => t('Board check diagonal'),
          'description' => 'this rule evalutes a diagonal for a number',
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
                  'optional' => FALSE,
              ),
              'position' => array(
                  'type' => 'text',
                  'label' => 'Position',
                  'optional' => FALSE,
                  'description' => 'the position of the row in 1d there is always one row in 2d its a number.',
              ),
              'position_diagonal_type' => array(
                  'type' => 'integer',
                  'label' => 'Diagonal type',
                  'options list' => 'get_all_diagonal_types',
                  'optional' => FALSE,
                  'description' => 'how do you define the position of the diagonal',
              ),
              'equal_to' => array(
                  'type' => 'integer',
                  'label' => 'equal to',
                  'description' => 'the number you want to check the diagonal for.',
                  'optional' => FALSE,
              ),
          ),
          'module' => 'board_games',
      ),
      'board_games_rules_condition_check_matrix' => array(
          'group' => 'game',
          'label' => t('Board Check Matrix'),
          'arguments' => array(
              'item1' => array(
                  'type' => 'integer',
                  'label' => 'Item1',
                  'optional' => TRUE,
              ),
              'item2' => array(
                  'type' => 'integer',
                  'label' => 'Item2',
                  'optional' => TRUE,
              ),
          ),
          'module' => 'board_games',
      ),
  );
}

function board_games_rules_condition_check_matrix($item1 = 0, $item2 = 0, $options) {
  if ($item1 == $item2) {
    return TRUE;
  }
  return FALSE;
}

/**
 * board_games_rules_condition_check_row_equal
 * @param type $running_game
 * @param type $game
 * @param type $position
 * @param type $equal_to
 * @return boolean
 */
function board_games_rules_condition_check_row_equal($running_game = null, $game = null, $position = 0, $equal_to = 0) {

  if (empty($running_game)
          || empty($game)
          || !property_exists($running_game, "field_matrix")
          || !property_exists($game, "field_board_dimension_amount")) {
    return FALSE;
  }
  $dimensions = $game->field_board_dimension_amount[LANGUAGE_NONE];
  $dimension_count = count($dimensions);
  $matrix = $running_game->field_matrix[LANGUAGE_NONE];

  if ($dimension_count == 1 && $position == 0) {
    foreach ($matrix as $val) {
      if ($equal_to != $val['value']) {
        return FALSE;
      }
    }
    return TRUE;
  } else if ($dimension_count == 2) {
    for ($i = 0; $i < $dimensions[0]['value']; $i++) {
      if ($matrix[$i]['value'] != $equal_to) {
        return FALSE;
      }
    }
    return TRUE;
  }


  return false;
}

/**
 * board_games_rules_condition_check_column_equal
 * @param type $running_game
 * @param type $game
 * @param type $position
 * @param type $equal_to
 * @return boolean
 */
function board_games_rules_condition_check_column_equal($running_game = null, $game = null, $position = 0, $equal_to = 0) {

  if (empty($running_game)
          || empty($game)
          || !property_exists($running_game, "field_matrix")
          || !property_exists($game, "field_board_dimension_amount")) {
    return FALSE;
  }
  $dimensions = $game->field_board_dimension_amount[LANGUAGE_NONE];
  $dimension_count = count($dimensions);
  $matrix = $running_game->field_matrix[LANGUAGE_NONE];
  $matrix_count = count($matrix);
  if ($position == 0) {
    if (!isset($matrix[0])) {
      return FALSE;
    }
    if ($matrix[$p]['value'] == $equal_to) {
      return FALSE;
    }
    return TRUE;
  } else if ($position > 0 && $dimension_count == 2) {

    for ($i = 0; $i < $dimensions[1]['value']; $i++) {
      $p = (($position - 1) + $i) * $dimensions[1]['value'];
      if (!isset($matrix[$p])) {
        return FALSE;
      }
      if ($matrix[$p]['value'] != $equal_to) {
        return FALSE;
      }
    }
    return TRUE;
  }
  return FALSE;
}

function get_all_diagonal_types() {
  return array('Top Left', 'Top Right', 'Bottom Left', 'Bottom Right');
}

/**
 * board_games_rules_condition_check_diagonal_equal
 * @param type $running_game
 * @param type $game
 * @param type $position
 * @param type $equal_to
 * @return boolean
 */
function board_games_rules_condition_check_diagonal_equal($running_game = null, $game = null, $position = "", $position_type = 0, $equal_to = 0) {

  if (empty($running_game)
          || empty($game)
          || !property_exists($running_game, "field_matrix")
          || !property_exists($game, "field_board_dimension_amount")) {
    return FALSE;
  }
  $positions = explode("-", $position);



  $dimensions = $game->field_board_dimension_amount[LANGUAGE_NONE];
  $dimension_count = count($dimensions);
  $matrix = $running_game->field_matrix[LANGUAGE_NONE];
  $matrix_count = count($matrix);
  $psd = $position_single_dimension = _convert_to_one_dimension($positions, $dimensions[0]['value']);
  // a general check if the position and the board are at the same dimension
  if ($dimension_count != count($dimensions)) {
    return FALSE;
  }

  if ($dimension_count == 2 && count($positions) == 2) {
    switch ($position_type) {
      case 0:// 'Top Left'
        $count = $positions[0]-1;
        for ($i = 0; $i < $dimensions[0]['value']; $i++) {
          $p = ($psd + $i) + ($dimensions[1]['value'] * $count);
          if (!isset($matrix[$p])) {
            return FALSE;
          }
          if ($matrix[$p]['value'] != $equal_to) {
            return FALSE;
          }
          $count++;
        }
        return TRUE;
        break;
      case 1:// 'Top Right'
        $count = $positions[0]-1;
        for ($i = 0; $i < $dimensions[0]['value']; $i++) {
          $p = ($psd - $i) + ($dimensions[1]['value'] * $count);
          if ($p < 0) {
            break;
          }

          if (!isset($matrix[$p])) {
            return FALSE;
          }
          if ($matrix[$p]['value'] != $equal_to) {
            return FALSE;
          }
          $count++;
        }
        return TRUE;
        break;
      case 2:// 'Bottom Left'
        return TRUE;
        break;
      case 3://'Bottom Right'

        return TRUE;
        break;
    }
  }
  return FALSE;
}

function _convert_to_one_dimension($position, $dimension) {
  return (($position[0] - 1) * $dimension) + ($position[1] - 1);
}

function _convert_to_two_dimension($position, $dimension) {
  if (($position % $dimension) > 0) {
    return array(($position / $dimension), ($position % ($dimension)));
  } else {
    return array(($position / $dimension), 0);
  }
}

/**
 * Hook_rules_action_info
 * @return type
 */
function board_games_rules_action_info() {

  return array(
      'rules_tile_lisiten_to_click' => array(
          'label' => t('Tile listen to click events'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => TRUE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'rules_tile_lisiten_to_click',
          'callbacks' => array(
              'validate' => 'rules_tile_lisiten_to_click_validation',
          ),
      ),
      'rules_tile_lisiten_to_change' => array(
          'label' => t('Tile listen to change events'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => TRUE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'rules_tile_lisiten_to_change',
          'callbacks' => array(
              'validate' => 'rules_tile_lisiten_to_change_validation',
          ),
      ),
      'rules_tile_set_owner' => array(
          'label' => t('Tile Set owner'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => TRUE,
              ),
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => 'tile_position',
                  'optional' => TRUE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'rules_tile_set_owner',
          'callbacks' => array(
              'validate' => 'rules_tile_set_owner_validation',
          ),
      ),
      'rules_game_change_turn' => array(
          'label' => t('Game change turn'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
              ),
          ),
          'group' => t('Game Board'),
          'base' => 'rules_game_change_turn',
          'callbacks' => array(
              'validate' => 'rules_game_change_turn_validation',
          ),
      ),
      'rules_tile_increment' => array(
          'label' => t('Tile Increment'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => TRUE,
              ),
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => 'tile_position',
                  'optional' => TRUE,
              ),
              'modulo' => array(
                  'type' => 'integer',
                  'label' => 'modulo',
                  'optional' => TRUE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'rules_tile_increment',
          'callbacks' => array(
              'validate' => 'rules_tile_increment_validation',
          ),
      ),
      'rules_tile_decrement' => array(
          'label' => t('Tile Decrement'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => TRUE,
              ),
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => 'tile_position',
                  'optional' => TRUE,
              ),
              'modulo' => array(
                  'type' => 'integer',
                  'label' => 'modulo',
                  'optional' => TRUE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'rules_tile_decrement',
          'callbacks' => array(
              'validate' => 'rules_tile_decrement_validation',
          ),
      ),
      'rules_game_set_tile_in_matrix' => array(
          'label' => t('Game set Tile'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'tile_postion' => array(
                  'type' => 'integer',
                  'label' => 'tile position',
                  'optional' => FALSE,
              ),
              'tile_value' => array(
                  'type' => 'integer',
                  'label' => 'tile value',
                  'optional' => FALSE,
              ),
          ),
          'group' => t('Game Board'),
          'base' => 'rules_game_set_tile_in_matrix',
          'callbacks' => array(
              'validate' => 'rules_game_set_tile_in_matrix_validation',
          ),
      ),
  );
}

/**
 * rules_tile_lisiten_to_click
 * Allow for PHP to listen to JS on_click events on Tile elements
 * @param type $running_game
 */
function rules_tile_lisiten_to_click($running_game) {
  $running_game_command = array();
  $running_game_command['running_game_id'] = $running_game->id;
  $running_game_command['command_id'] = 1;
  $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "BoardGame", "fn" => "listen_to_click_event", "params" => array()), "time" => time()));
  $running_game_command_entity = entity_create("running_game_command", $running_game_command);
  $running_game_command_entity->save();
}

function rules_tile_lisiten_to_click_validation($running_game) {
  return false;
}

/**
 * rules_tile_lisiten_to_click
 * Allow for PHP to listen to JS on_change events on Tile elements
 * @param type $running_game
 */
function rules_tile_lisiten_to_change($running_game) {
  $running_game_command = array();
  $running_game_command['running_game_id'] = $running_game->id;
  $running_game_command['command_id'] = 1;
  $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "BoardGame", "fn" => "listen_to_change_event", "params" => array()), "time" => time()));
  $running_game_command_entity = entity_create("running_game_command", $running_game_command);
  $running_game_command_entity->save();
}

function rules_tile_lisiten_to_change_validation($running_game) {
  return false;
}

/**
 * rules_game_set_tile_in_matrix
 * uses filed metrix and change the value of certine position
 * @param type $running_game
 * @param type $tile_postion
 * @return boolean
 */
function rules_game_set_tile_in_matrix_validation($running_game, $tile_postion) {
  return true;
}

function rules_game_set_tile_in_matrix($running_game, $tile_position, $tile_value) {
  for ($j = 0; $j < $tile_position; $j++) {
    if (!isset($running_game->field_matrix['und'][$j])) {
      $running_game->field_matrix['und'][$j]['value'] = "0";
    }
  }
  $running_game->field_matrix['und'][$tile_position]['value'] = $tile_value;

  if ($running_game->save()) {
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "BoardGame", "fn" => "board_game_set_tile_in_matrix", "params" => array("tile_position" => $tile_position, "tile_value" => $tile_value)), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }
}

/**
 * rules_tile_increment
 * uses field_matrix and ++ for current tile
 * @global type $user
 * @param type $running_game_session
 * @param type $tile_position
 * @param type $modulo
 */
function rules_tile_increment($running_game_session, $tile_position = 0, $modulo = 10) {
  global $user;
//  load game instance by session
  if (!empty($running_game_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'running_game')
            ->propertyCondition('session', $running_game_session)
            ->execute();
    $key = key($result['running_game']);
    $running_game = running_game_load($key);
  }

//  reset tiles if not set
  for ($j = 0; $j < $tile_position; $j++) {
    if (!isset($running_game->field_matrix['und'][$j])) {
      $running_game->field_matrix['und'][$j]['value'] = 0;
    }
  }
  if (empty($modulo)) {
    $running_game->field_matrix['und'][$tile_position]['value']++;
  } else {
    $running_game->field_matrix['und'][$tile_position]['value'] = ($running_game->field_matrix['und'][$tile_position]['value'] + 1) % $modulo;
  }
//  save game instance
  if ($running_game->save()) {
//  send js action to all players
    $params = array("tile_id" => $tile_position, "player_turn" => $player->player_turn, "value" => $running_game->field_matrix['und'][$tile_position]['value']);
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 2;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "BoardGame", "fn" => "board_games_tile_increment_action", "params" => $params), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  } else {

    dpm("cant save game instance");
  }
}

function rules_tile_increment_validation($running_game_session, $tile_position = 0, $modulo = 10) {
// dpm("rules_tile_set_owner_validation");
  return true;
}

/**
 * rules_tile_decrement
 * uses field_matrix and ++ for current tile
 * @global type $user
 * @param type $running_game_session
 * @param type $tile_position
 * @param type $modulo
 */
function rules_tile_decrement($running_game_session, $tile_position = 0, $modulo = 0) {
  global $user;
//  load game instance by session
  if (!empty($running_game_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'running_game')
            ->propertyCondition('session', $running_game_session)
            ->execute();
    $key = key($result['running_game']);
    $running_game = running_game_load($key);
  }

//  reset tiles if not set
  for ($j = 0; $j < $tile_position; $j++) {
    if (!isset($running_game->field_matrix['und'][$j])) {
      $running_game->field_matrix['und'][$j]['value'] = 0;
    }
  }
  $running_game->field_matrix['und'][$tile_position]['value']--;
  if (!empty($modulo) && $running_game->field_matrix['und'][$tile_position]['value'] < 0) {
    $running_game->field_matrix['und'][$tile_position]['value'] = $modulo;
  }
//  save game instance
  if ($running_game->save()) {
//  send js action to all players
    $params = array("tile_id" => $tile_position, "player_turn" => $player->player_turn, "value" => $running_game->field_matrix['und'][$tile_position]['value']);
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 2;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "BoardGame", "fn" => "board_games_tile_decrement_action", "params" => $params), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  } else {
    watchdog(WATCHDOG_ALERT, "cant save game instance");
  }
}

function rules_tile_decrement_validation($running_game_session, $tile_position = 0, $modulo = 0) {
  return true;
}

/**
 * 
 * @param type $running_game_session
 */
function rules_game_change_turn($running_game) {

// load all players
  $conditions = array("running_game_id" => $running_game->id);
  $players = entity_load("running_game_player", FALSE, $conditions);

  $keys = array_keys($players);
  $player_count = count($players);

  $current_turn = $running_game->field_current_turn['und'][0]['value'];
  if (empty($current_turn)) {
    $current_turn = 1;
  } else {
    $current_turn = (($current_turn) % $player_count) + 1;
  }
  $running_game->field_current_turn['und'][0]['value'] = $current_turn;

// Search for participent name
  foreach ($players as $player) {
    if ($player->player_turn == $current_turn) {
      $player_name = $player->player_name;
    }
  }
  $message = $player_name . " turn";
  $running_game_command = array();
  $running_game_command['running_game_id'] = $running_game->id;
  $running_game_command['command_id'] = 2;
  $running_game_command['command_data'] = drupal_json_encode(array("message" => $message, "time" => time()));
  $running_game_command_entity = entity_create("running_game_command", $running_game_command);
  $running_game_command_entity->save();


  running_game_save($running_game);
}

function rules_game_change_turn_validation() {
  return true;
}

function rules_tile_set_owner($running_game, $tile_position = 0) {
  global $user;
//  load user credential
  $session = $user->sid;
  if (empty($session)) {
//  user is not a registered user in this site
    $session = session_id();
//dpm("rules_tile_set_owner by session  " . $session);
  }


//  load current user session data
  $conditions = array("running_game_id" => $running_game->id, 'player_session' => $session);
  $entity = entity_load("running_game_player", FALSE, $conditions);
  $player = $entity[key($entity)];

//  reset tiles if not set
  for ($j = 0; $j < $tile_position; $j++) {
    if (!isset($running_game->field_matrix['und'][$j])) {
      $running_game->field_matrix['und'][$j]['value'] = 0;
    }
  }
//  check if i can set owner or tile already owned by another player
  if ($running_game->field_matrix['und'][$tile_position]['value'] == 0 || empty($running_game->field_matrix['und'][$tile_position]['value'])) {
//  changed the tile owner ship to current player
    $running_game->field_matrix['und'][$tile_position]['value'] = $player->player_turn;
//  save game instance
    if ($running_game->save()) {
//  send js action to all players
      $params = array("tile_id" => $tile_position, "player_turn" => $player->player_turn);
      $running_game_command = array();
      $running_game_command['running_game_id'] = $running_game->id;
      $running_game_command['command_id'] = 2;
      $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "BoardGame", "fn" => "board_games_tile_set_owner_action", "params" => $params), "time" => time()));
      $running_game_command_entity = entity_create("running_game_command", $running_game_command);

      $running_game_command_entity->save();
    } else {

      watchdog(WATCHDOG_ALERT, "cant save game instance");
    }
  } else {
// the tile is already owned by player cannot
    return array("callback" => array("module" => "RunningGame", "fn" => "message", "params" => array("The tile is already owned")));
//dpm("the tile is already owned by user cannot");
  }



//;

  return array("callback" => array("module" => "RunningGame", "fn" => "message", "params" => array("The tile is already owned")));
}

function rules_tile_set_owner_validation() {
// dpm("rules_tile_set_owner_validation");
  return true;
}

function rules_tile_set_owner_callback() {
// dpm("rules_tile_set_owner_callback");
//return "";
//return array("callback" => array("module" => "RunningGame", "fn" => "message", "params" => array("The tile is already owned")));
  /*
    if ($context['game_id'] == $running_game->gid) {

    $conditions = array("running_game_id" => $running_game->id, 'player_session' => session_id());

    $entity = entity_load("running_game_player", FALSE, $conditions);
    $player = $entity[key($entity)];

    //dpm($player->player_turn);
    // dpm($running_game->field_matrix['und']);
    if ($running_game->field_matrix['und'][$context['params']]['value'] == 0 || empty($running_game->field_matrix['und'][$context['params']]['value'])) {
    $running_game->field_matrix['und'][$context['params']]['value'] = $player->player_turn;

    if ($running_game->save()) {
    $params = array("tile_id" => $context['params'], "player_turn" => $player->player_turn);
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 2;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "BoardGame", "fn" => $context['callback'], "params" => $params), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
    } else {

    dpm("cant save game instance");
    }
    } else {
    // the tile is already owned by user cannot
    return array("callback" => array("module" => "RunningGame", "fn" => "message", "params" => array("The tile is already owned")));
    //dpm("the tile is already owned by user cannot");
    }


    //  dpm("got to action " . board_games_tile_set_owner_action);
    }
   */
}

/**
 * Hook_rules_event_info
 * @return array
 */
function board_games_rules_event_info() {
  $items = array(
      'tile_click' => array(
          'label' => t('Tile click'),
          'group' => t('Game Rules'),
          'variables' => array(
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => t('Tile position'),
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
      'tile_set' => array(
          'label' => t('Tile set'),
          'group' => t('Game Rules'),
          'variables' => array(
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => t('Tile position'),
              ),
              'tile_value' => array(
                  'type' => 'integer',
                  'label' => t('Tile value'),
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
      'tile_hover' => array(
          'label' => t('Tile hover'),
          'group' => t('Game Rules'),
          'variables' => array(
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => t('Tile position'),
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
  );

  return $items;
}

