<?php
/**
 *
 * @return type
 */
function game_rules_data_info() {
  $data = array();
  $data['running_game'] = array(
      'label' => t('Game Instance'),
      'ui class' => 'RunningGameController',
  );
  $data['game'] = array(
      'label' => t('Game'),
      'ui class' => 'GameController',
  );
  return $data;
}

function game_rules_event_info() {

  $items = array(
      'game_create_running_instance' => array(
          'label' => t('After Instance is created'),
          'group' => t('Game Rules'),
          'variables' => rules_events_node_variables(t('created content')),
      ),
      'game_start' => array(
          'label' => t('Game starts'),
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
          ),
      ),
      'game_end' => array(
          'label' => t('Game ends'),
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
          ),
      ),
  );

  return $items;
}

function _rules_game_select_info() {


  return array(
      'type' => array(
          'type' => 'text',
          'label' => t('The category to which this message belongs'),
      ),
  );
}

/**
 *  Fix this most importent 
 */
/*
function game_rules_data_info() {
  return array(
      'running_game' => array(
          'label' => t('running_game'),
          'ui class' => 'RunningGameController',
          'wrap' => TRUE,
          'property info' => array(
              'running_game' => array(
                  'type' => 'text',
                  'label' => 'running_game',
              ),
              'args' => array(
                  'type' => 'list<text>',
                  'label' => t('Arguments'),
                  'setter callback' => 'entity_property_verbatim_set'
              ),
          ),
      ),
      'running_game_entity' => array(
          'label' => t('running game entity'),
          'parent' => 'entity',
          'group' => t('entity'),
      ),
  );
}
*/
function game_rules_action_info() {

  return array(
      'rules_game_over' => array(
          'label' => t('Game Over'),
          'parameter' => array(
              'running_game_session' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'running_game_session',
                  'optional' => TRUE,
              // If we were to make changes to the parameter object, whe should set
              // the 'save' property to TRUE. This makes Rules handle the saving in
              // a more optimized way than if each action saved the objects.
              // 'save' => TRUE,
              ),
          ),
          'group' => t('Game'),
          'base' => 'rules_game_over',
          'callbacks' => array(
              'validate' => 'rules_game_over_validation',
          ),
      ),
      'rules_game_set_winners' => array(
          'label' => t('Game set winner'),
          'parameter' => array(
              'running_game_session' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'running_game_session',
                  'optional' => TRUE,
              // If we were to make changes to the parameter object, whe should set
              // the 'save' property to TRUE. This makes Rules handle the saving in
              // a more optimized way than if each action saved the objects.
              // 'save' => TRUE,
              ),
              'player_id' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'player_id',
              //'optional' => TRUE,
              // If we were to make changes to the parameter object, whe should set
              // the 'save' property to TRUE. This makes Rules handle the saving in
              // a more optimized way than if each action saved the objects.
              // 'save' => TRUE,
              ),
          ),
          'group' => t('Game'),
          'base' => 'rules_game_set_winners',
          'callbacks' => array(
              'validate' => 'rules_game_set_winners_validation',
          ),
      ),
      'rules_game_send_message' => array(
          'label' => t('Game send message'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'message_text' => array(
                  'type' => 'text',
                  'label' => 'message_text',
                  'optional' => TRUE,
              ),
          ),
          'group' => t('Game'),
          'base' => 'rules_game_send_message',
          'callbacks' => array(
              'validate' => 'rules_game_send_message_validation',
          ),
      ),
  );
}

function rules_game_send_message_validation($running_game, $message) {
  return true;
}

function rules_game_send_message($running_game, $message) {

  $running_game_command = array();
  $running_game_command['running_game_id'] = $running_game->id;
  $running_game_command['command_id'] = 1;
  $running_game_command['command_data'] = drupal_json_encode(array("message" => $message, "callback" => array("module" => "RunningGame", "fn" => "message", "params" => array($message)), "time" => time()));
  $running_game_command_entity = entity_create("running_game_command", $running_game_command);
  $running_game_command_entity->save();
}

function rules_game_over_validation($running_game) {
  return true;
}

function rules_game_over($running_game_session) {
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
  } else {
    //  user is registered user in this site
  }

  //  load current player session data
  $conditions = array("running_game_id" => $running_game->id, 'participant_session' => $session);
  $entity = entity_load("running_game_participant", FALSE, $conditions);
  $player = $entity[key($entity)];

  // set game status to game over
  $running_game->status = GAME_STATUS_ENDED;

  if ($running_game->save()) {
    //  inform all players game is over
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => "Game Ended", "callback" => array("module" => "RunningGame", "fn" => "game_ended", "params" => '1'), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
    //  game saved
    // dpm("game saved");
  } else {
    //  problom saving game
  }
}

function rules_game_set_winners($running_game_session, $player_id) {
  //dpm("rules_game_set_winners player_id:" . $player_id);
  // the game can only define a winner once whan game is beaing played
  if (!empty($running_game_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'running_game')
            ->propertyCondition('session', $running_game_session)
            ->execute();
    $key = key($result['running_game']);
    $running_game = running_game_load($key);
    //dpm($running_game);
    // load player
    $conditions = array("running_game_id" => $running_game->id, 'participant_turn' => $player_id);
    $entity = entity_load("running_game_participant", FALSE, $conditions);
    $player = $entity[key($entity)];
    //dpm($player);
    $player->participant_name;

    //  inform all players game winner
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $player->participant_name . " won the game", "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }

  // change game mod to ended inform all other player game ended
}

function rules_game_set_winners_validation() {
  return true;
}