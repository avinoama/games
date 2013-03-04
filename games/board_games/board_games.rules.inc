<?php

//hook_rules_data_info();
//hook_rules_data_info
function board_games_rules_data_info() {
  $data = array();
  $data['game_instance'] = array(
      'label' => t('Game Instance'),
      'ui class' => 'GameInstanceController',
  );
  return $data;
}

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
  );
}

function board_games_rules_condition_check_pattren($board, $game_instance) {
  //dpm(print_r($game_instance,1));
  //dpm("board_games_rules_condition_check_pattren " . print_r($board,1));
  return true;
}

function board_games_rules_action_info() {

  return array(
      'rules_tile_set_owner' => array(
          'label' => t('Tile Set owner'),
          'parameter' => array(
              'game_instance' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'game_instance',
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
              'game_instance' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'game_instance',
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
              'game_instance' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'game_instance',
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
              'game_instance' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'game_instance',
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
  );
}

function rules_tile_increment($game_instance_session, $tile_position = 0, $modulo = 0) {
  global $user;
  //  load game instance by session
  if (!empty($game_instance_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'game_instance')
            ->propertyCondition('session', $game_instance_session)
            ->execute();
    $key = key($result['game_instance']);
    $game_instance = game_instance_load($key);
  }

  //  reset tiles if not set
  for ($j = 0; $j < $tile_position; $j++) {
    if (!isset($game_instance->field_matrix['und'][$j])) {
      $game_instance->field_matrix['und'][$j]['value'] = 0;
    }
  }
  if (empty($modulo)) {
    $game_instance->field_matrix['und'][$tile_position]['value']++;
  } else {
    $game_instance->field_matrix['und'][$tile_position]['value'] = ($game_instance->field_matrix['und'][$tile_position]['value'] + 1) % $modulo;
  }
  //  save game instance
  if ($game_instance->save()) {
    //  send js action to all players
    $params = array("tile_id" => $tile_position, "participant_turn" => $player->participant_turn, "value" => $game_instance->field_matrix['und'][$tile_position]['value']);
    $game_instance_command = array();
    $game_instance_command['instance_id'] = $game_instance->id;
    $game_instance_command['command_id'] = 2;
    $game_instance_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => "board_games_tile_increment_action", "params" => $params), "time" => time()));
    $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
    $game_instance_command_entity->save();
  } else {

    dpm("cant save game instance");
  }
}

function rules_tile_increment_validation() {
  // dpm("rules_tile_set_owner_validation");
  return true;
}

function rules_tile_decrement($game_instance_session, $tile_position = 0, $modulo = 0) {
  global $user;
  //  load game instance by session
  if (!empty($game_instance_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'game_instance')
            ->propertyCondition('session', $game_instance_session)
            ->execute();
    $key = key($result['game_instance']);
    $game_instance = game_instance_load($key);
  }

  //  reset tiles if not set
  for ($j = 0; $j < $tile_position; $j++) {
    if (!isset($game_instance->field_matrix['und'][$j])) {
      $game_instance->field_matrix['und'][$j]['value'] = 0;
    }
  }
  $game_instance->field_matrix['und'][$tile_position]['value']--;
  if (!empty($modulo) && $game_instance->field_matrix['und'][$tile_position]['value'] < 0) {
    $game_instance->field_matrix['und'][$tile_position]['value'] = $modulo;
  }
  //  save game instance
  if ($game_instance->save()) {
    //  send js action to all players
    $params = array("tile_id" => $tile_position, "participant_turn" => $player->participant_turn, "value" => $game_instance->field_matrix['und'][$tile_position]['value']);
    $game_instance_command = array();
    $game_instance_command['instance_id'] = $game_instance->id;
    $game_instance_command['command_id'] = 2;
    $game_instance_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => "board_games_tile_decrement_action", "params" => $params), "time" => time()));
    $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
    $game_instance_command_entity->save();
  } else {

    dpm("cant save game instance");
  }
}

function rules_tile_decrement_validation() {
  // dpm("rules_tile_set_owner_validation");
  return true;
}

function rules_game_change_turn($game_instance_session) {
  if (!empty($game_instance_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'game_instance')
            ->propertyCondition('session', $game_instance_session)
            ->execute();
    $key = key($result['game_instance']);
    $game_instance = game_instance_load($key);

    // load all players
    $conditions = array("instance_id" => $game_instance->id);
    $entity = entity_load("game_instance_participant", FALSE, $conditions);

    $keys = array_keys($entity);
    $player_count = count($entity);

    $current_turn = $game_instance->field_current_turn['und'][0]['value'];
    if (empty($current_turn)) {
      $current_turn = 1;
    } else {
      $current_turn = ($current_turn % $player_count) + 1;
    }
    $game_instance->field_current_turn['und'][0]['value'] = $current_turn;
    dpm($keys);
    dpm($current_turn);
    $message=$entity[$keys[$current_turn-1]]->participant_name." turn";
    $game_instance_command = array();
    $game_instance_command['instance_id'] = $game_instance->id;
    $game_instance_command['command_id'] = 2;
    $game_instance_command['command_data'] = drupal_json_encode(array("message" => $message, "time" => time()));
    $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
    $game_instance_command_entity->save();


    game_instance_save($game_instance);
  }
}

function rules_game_change_turn_validation() {
  return true;
}

function rules_tile_set_owner($game_instance_session, $tile_position = 0) {
  global $user;
  //  load game instance by session
  if (!empty($game_instance_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'game_instance')
            ->propertyCondition('session', $game_instance_session)
            ->execute();
    $key = key($result['game_instance']);
    $game_instance = game_instance_load($key);
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
  $conditions = array("instance_id" => $game_instance->id, 'participant_session' => $session);
  $entity = entity_load("game_instance_participant", FALSE, $conditions);
  $player = $entity[key($entity)];

  //  reset tiles if not set
  for ($j = 0; $j < $tile_position; $j++) {
    if (!isset($game_instance->field_matrix['und'][$j])) {
      $game_instance->field_matrix['und'][$j]['value'] = 0;
    }
  }
  //  check if i can set owner or tile already owned by another player
  if ($game_instance->field_matrix['und'][$tile_position]['value'] == 0 || empty($game_instance->field_matrix['und'][$tile_position]['value'])) {
    //  changed the tile owner ship to current player
    $game_instance->field_matrix['und'][$tile_position]['value'] = $player->participant_turn;
    //  save game instance
    if ($game_instance->save()) {
      //  send js action to all players
      $params = array("tile_id" => $tile_position, "participant_turn" => $player->participant_turn);
      $game_instance_command = array();
      $game_instance_command['instance_id'] = $game_instance->id;
      $game_instance_command['command_id'] = 2;
      $game_instance_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => "board_games_tile_set_owner_action", "params" => $params), "time" => time()));
      $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
      $game_instance_command_entity->save();
    } else {

      dpm("cant save game instance");
    }
  } else {
    // the tile is already owned by player cannot
    return array("callback" => array("module" => "gameInstance", "fn" => "message", "params" => array("The tile is already owned")));
    //dpm("the tile is already owned by user cannot");
  }



  //array("callback" => array("module" => "gameInstance", "fn" => "message", "params" => array("The tile is already owned")));

  return;
}

function rules_tile_set_owner_validation() {
  // dpm("rules_tile_set_owner_validation");
  return true;
}

function rules_tile_set_owner_callback() {
  dpm("rules_tile_set_owner_callback");
  //return "";
  //return array("callback" => array("module" => "gameInstance", "fn" => "message", "params" => array("The tile is already owned")));
  /*
    if ($context['game_id'] == $game_instance->gid) {

    $conditions = array("instance_id" => $game_instance->id, 'participant_session' => session_id());

    $entity = entity_load("game_instance_participant", FALSE, $conditions);
    $player = $entity[key($entity)];

    //dpm($player->participant_turn);
    // dpm($game_instance->field_matrix['und']);
    if ($game_instance->field_matrix['und'][$context['params']]['value'] == 0 || empty($game_instance->field_matrix['und'][$context['params']]['value'])) {
    $game_instance->field_matrix['und'][$context['params']]['value'] = $player->participant_turn;

    if ($game_instance->save()) {
    $params = array("tile_id" => $context['params'], "participant_turn" => $player->participant_turn);
    $game_instance_command = array();
    $game_instance_command['instance_id'] = $game_instance->id;
    $game_instance_command['command_id'] = 2;
    $game_instance_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => $context['callback'], "params" => $params), "time" => time()));
    $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
    $game_instance_command_entity->save();
    } else {

    dpm("cant save game instance");
    }
    } else {
    // the tile is already owned by user cannot
    return array("callback" => array("module" => "gameInstance", "fn" => "message", "params" => array("The tile is already owned")));
    //dpm("the tile is already owned by user cannot");
    }


    //  dpm("got to action " . board_games_tile_set_owner_action);
    }
   */
}

function board_games_rules_event_info() {
  $items = array(
      'tile_click' => array(
          'label' => t('After tile was clicked'),
          'group' => t('Game Rules'),
          // If the event provides any parameters to Rules, these are described with
          // the 'variables' property.
          // 'variables' => entity_rules_events_variables('board_games', t('tile_position', array(), array('context' => 'current tile position'))),
          'variables' => array(
              // Each provided variable is keyed by a given machine name, and work
              // very similar to how parameters and provided variables are desribed in
              // conditions and actions.

              'tile_position' => array(
                  'type' => 'int',
                  'label' => t('Tile num'),
              ),
          /*
            'game_instance' => array(
            'type' => 'entity',
            'label' => t('Game Instance'),
            ),
           * 
           */
          ),
      ),
      'tile_hover' => array(
          'label' => t('After tile was hoverd'),
          'group' => t('Game Rules'),
          // If the event provides any parameters to Rules, these are described with
          // the 'variables' property.
          'variables' => array(
              // Each provided variable is keyed by a given machine name, and work
              // very similar to how parameters and provided variables are desribed in
              // conditions and actions.
              'tile_num' => array(
                  'type' => 'int',
                  'label' => t('Tile num'),
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