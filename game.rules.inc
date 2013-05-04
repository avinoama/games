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
          'label' => t('Game created'),
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

function game_rules_action_info() {

  return array(
      'rules_start_game' => array(
          'label' => t('Start Game'),
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
          ),
          'group' => t('Game'),
          'base' => 'rules_start_game',
          'callbacks' => array(
              'validate' => 'rules_start_game_validation',
          ),
      ),
      'rules_game_over' => array(
          'label' => t('Game Over'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
          ),
          'group' => t('Game'),
          'base' => 'rules_game_over',
          'callbacks' => array(
              'validate' => 'rules_game_over_validation',
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

function rules_start_game($running_game, $game) {
  //  change game status
  
  $query = db_select('running_game_player', 'p')->fields('p')->condition('running_game_id', $running_game->id, '=');
  $players = $query->execute();

  $i = 1;
  $first_player;
  foreach ($players as $player) {
    if ($i == 1) {
      $first_player = $player->player_name;
    }
    $player->status = PLAYER_STATUS_PLAYING;
    $player->player_turn = $i;
    entity_save("running_game_player", $player);
    $i++;
  }

  $running_game_command = array();
  $running_game_command['running_game_id'] = $running_game->id;
  $running_game_command['command_id'] = 1;
  $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("fn" => "start_game", "module" => "RunningGame", "params" => "1")));
  $running_game_command_entity = entity_create("running_game_command", $running_game_command);
  $running_game_command_entity->save();
  //  Start game
  $running_game->started = REQUEST_TIME;
  $running_game->status = GAME_STATUS_STARTED;
  $running_game->save();
}

function rules_start_game_validation($running_game, $game) {
  return true;
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

function rules_game_over($running_game) {
  global $user;

  //  load user credential
  $session = $user->sid;
  if (empty($session)) {
    //  user is not a registered user in this site
    $session = session_id();
  } else {
    //  user is registered user in this site
  }

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
  } else {
    //  problom saving game
  }
}

