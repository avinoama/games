<?php

function game_rules_event_info() {

  $items = array(
      'game_create_instance' => array(
          'label' => t('After Instance is created'),
          'group' => t('Game Rules'),
          'variables' => rules_events_node_variables(t('created content')),
      ),
      'game_start' => array(
          'label' => t('After game start'),
          'group' => t('Game Rules'),
          'variables' => rules_events_node_variables(t('updated content'), TRUE),
      ),
      'game_end' => array(
          'label' => t('After game ends'),
          'group' => t('Game Rules'),
          'variables' => rules_events_node_variables(t('saved content'), TRUE),
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
function game_rules_data_info() {
  return array(
      'game_instance' => array(
          'label' => t('game instance'),
          'ui class' => 'GameInstanceController',
          'wrap' => TRUE,
          'property info' => array(
              'game_instance' => array(
                  'type' => 'text',
                  'label' => 'game_instance',
              ),
              'args' => array(
                  'type' => 'list<text>',
                  'label' => t('Arguments'),
                  'setter callback' => 'entity_property_verbatim_set'
              ),
          ),
      ),
  );
}

function game_rules_action_info() {

  return array(
      'rules_game_over' => array(
          'label' => t('Game Over'),
          'parameter' => array(
              'game_instance_session' => array(
                  //'type' => 'entity',
                  'type' => 'text',
                  'label' => 'game_instance_session',
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
              'player_id' => array(
                  //'type' => 'entity',
                  'type' => 'integer',
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
  );
}

function rules_game_over_validation($game_instance) {
  return true;
}

function rules_game_over($game_instance_session) {
  global $user;
  //dpm("rules_game_over");
  //  load game instance by session
  //dpm($game_instance_session);
  if (!empty($game_instance_session)) {

    $query = new EntityFieldQuery;
    $result = $query
            ->entityCondition('entity_type', 'game_instance')
            ->propertyCondition('session', $game_instance_session)
            ->execute();
    $key = key($result['game_instance']);
    $game_instance = game_instance_load($key);
    //dpm($game_instance);
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

  //  load current player session data
  $conditions = array("instance_id" => $game_instance->id, 'participant_session' => $session);
  $entity = entity_load("game_instance_participant", FALSE, $conditions);
  $player = $entity[key($entity)];

  // set game status to game over
  $game_instance->status = GAME_STATUS_ENDED;
  if ($game_instance->save()) {
    //  inform all players game is over
    $game_instance_command = array();
    $game_instance_command['instance_id'] = $game_instance->id;
    $game_instance_command['command_id'] = 1;
    $game_instance_command['command_data'] = drupal_json_encode(array("message" => "Game Ended", "time" => time()));
    $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
    $game_instance_command_entity->save();
    //  game saved
    // dpm("game saved");
  } else {
    //  problom saving game
  }
}

function rules_game_set_winners($player_id) {
  dpm("rules_game_set_winners");
}

function rules_game_set_winners_validation() {
  return true;
}