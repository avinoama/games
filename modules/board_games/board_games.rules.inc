<?php

//hook_rules_data_info();
//hook_rules_data_info



function board_games_rules_condition_info() {
  return array(
      'board_games_rules_condition_check_pattren' => array(
          'group' => 'game',
          'label' => t('Board Check Pattren'),
          'arguments' => array(
              'board' => array(
                  'type' => 'list',
                  'label' => 'Board',
                  'optional' => TRUE,
              ),
              'game-instance' => array(
                  'type' => 'entity',
                  'label' => 'Instance',
                  'optional' => TRUE,
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

function board_games_rules_condition_check_pattren($board, $running_game) {
  //dpm(print_r($running_game,1));
  //dpm("board_games_rules_condition_check_pattren " . print_r($board,1));
  return true;
}

function board_games_rules_action_info() {

  return array(
      'rules_tile_set_owner' => array(
          'label' => t('Tile Set owner'),
          'parameter' => array(
              'running_game' => array(
                  //'type' => 'entity',
                  'type' => 'text',
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
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'running_game',
                  'optional' => TRUE,
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
                  //'type' => 'entity',
                  'type' => 'text',
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
                  //'type' => 'entity',
                  'type' => 'text',
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
//      'rules_game_set_matrix' => array(
//          'label' => t('Game set Metrix'),
//          'parameter' => array(
//              'running_game' => array(
//                  'type' => 'running_game',
//                  'label' => 'running_game',
//                  'optional' => FALSE,
//              ),
//              'matrix_text' => array(
//                  'type' => 'text',
//                  'label' => 'valid jason array',
//                  'description' => "example : [{\"20\": 8},{\"25\": 6}] in position 20 put value 8 and in position 25 put value 6.",
//                  "optional" => FALSE,
//              ),
//          ),
//          'group' => t('Game Board'),
//          'base' => 'rules_game_set_matrix',
//          'callbacks' => array(
//              'validate' => 'rules_game_set_matrix_validation',
//          ),
//      ),
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

// Not a good way to do design for none programmers game
// 
//function rules_game_set_matrix_validation($running_game, $matrix) {
////  $j = drupal_json_decode($matrix_jason);
////  if ($j == null) {
////    return false;
////  }
//  return true;
//}
//
//function rules_game_set_matrix($running_game, $matrix_text) {
//  $matrix = drupal_json_decode($matrix_text);
//  $max_position = 0;
//  foreach ($matrix as $key => $value) {
//    $k = key($value);
//    $running_game->field_matrix['und'][$k]['value'] = $value[$k];
//    if ($k > $max_position) {
//      $max_position = $k;
//    }
//  }
//  for ($i = 0; $i < $max_position; $i++) {
//    if (!isset($running_game->field_matrix['und'][$i])) {
//      $running_game->field_matrix['und'][$i]['value'] = "0";
//    }
//  }
//  if ($running_game->save()) {
//    $running_game_command = array();
//    $running_game_command['running_game_id'] = $running_game->id;
//    $running_game_command['command_id'] = 1;
//    $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "boardGame", "fn" => "board_game_set_matrix", "params" => array("matrix" => $matrix)), "time" => time()));
//    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
//    $running_game_command_entity->save();
//  }
//}

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
    $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "boardGame", "fn" => "board_game_set_tile_in_matrix", "params" => array("tile_position" => $tile_position, "tile_value" => $tile_value)), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }
}

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
    $params = array("tile_id" => $tile_position, "participant_turn" => $player->participant_turn, "value" => $running_game->field_matrix['und'][$tile_position]['value']);
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 2;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => "board_games_tile_increment_action", "params" => $params), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  } else {

    dpm("cant save game instance");
  }
}

function rules_tile_increment_validation() {
  // dpm("rules_tile_set_owner_validation");
  return true;
}

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
    $params = array("tile_id" => $tile_position, "participant_turn" => $player->participant_turn, "value" => $running_game->field_matrix['und'][$tile_position]['value']);
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 2;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => "board_games_tile_decrement_action", "params" => $params), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  } else {
    watchdog(WATCHDOG_ALERT, "cant save game instance");
  }
}

function rules_tile_decrement_validation() {
  // dpm("rules_tile_set_owner_validation");
  return true;
}

function rules_game_change_turn($running_game_session) {
  if (!empty($running_game_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'running_game')
            ->propertyCondition('session', $running_game_session)
            ->execute();
    $key = key($result['running_game']);
    $running_game = running_game_load($key);

    // load all players
    $conditions = array("running_game_id" => $running_game->id);
    $participants = entity_load("running_game_participant", FALSE, $conditions);

    $keys = array_keys($participants);
    $player_count = count($participants);

    $current_turn = $running_game->field_current_turn['und'][0]['value'];
    if (empty($current_turn)) {
      $current_turn = 1;
    } else {
      $current_turn = (($current_turn) % $player_count) + 1;
    }
    $running_game->field_current_turn['und'][0]['value'] = $current_turn;

    // Search for participent name
    foreach ($participants as $participant) {
      if ($participant->participant_turn == $current_turn) {
        $participant_name = $participant->participant_name;
      }
    }
    $message = $participant_name . " turn";
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 2;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $message, "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();


    running_game_save($running_game);
  }
}

function rules_game_change_turn_validation() {
  return true;
}

function rules_tile_set_owner($running_game_session, $tile_position = 0) {
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
  //  load user credential
  $session = $user->sid;
  if (empty($session)) {
    //  user is not a registered user in this site
    $session = session_id();
    //dpm("rules_tile_set_owner by session  " . $session);
  } else {
    //  user is registered user in this site
    //dpm("rules_tile_set_owner by account " . $session);
  }



  //  load current user session data
  $conditions = array("running_game_id" => $running_game->id, 'participant_session' => $session);
  $entity = entity_load("running_game_participant", FALSE, $conditions);
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
    $running_game->field_matrix['und'][$tile_position]['value'] = $player->participant_turn;
    //  save game instance
    if ($running_game->save()) {
      //  send js action to all players
      $params = array("tile_id" => $tile_position, "participant_turn" => $player->participant_turn);
      $running_game_command = array();
      $running_game_command['running_game_id'] = $running_game->id;
      $running_game_command['command_id'] = 2;
      $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => "board_games_tile_set_owner_action", "params" => $params), "time" => time()));
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



  //array("callback" => array("module" => "RunningGame", "fn" => "message", "params" => array("The tile is already owned")));

  return;
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

    $conditions = array("running_game_id" => $running_game->id, 'participant_session' => session_id());

    $entity = entity_load("running_game_participant", FALSE, $conditions);
    $player = $entity[key($entity)];

    //dpm($player->participant_turn);
    // dpm($running_game->field_matrix['und']);
    if ($running_game->field_matrix['und'][$context['params']]['value'] == 0 || empty($running_game->field_matrix['und'][$context['params']]['value'])) {
    $running_game->field_matrix['und'][$context['params']]['value'] = $player->participant_turn;

    if ($running_game->save()) {
    $params = array("tile_id" => $context['params'], "participant_turn" => $player->participant_turn);
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 2;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => $context['callback'], "params" => $params), "time" => time()));
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

/**
 * Implements hook_default_rules_configuration().
 */
/*
function board_games_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = 'example default rule';
  $rule->active = FALSE;
  $rule->event('tile_click')
          ->condition(rules_condition('data_is', array('data:select' => 'entity:type', 'value' => "board_games")))
          ->action('drupal_message', array('message' => 'Test_11.'));

  $configs['rules_test_default_1'] = $rule;
  return $configs;
}
*/