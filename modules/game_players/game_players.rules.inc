<?php

/**
 * Hook rules_event_info
 * @return array
 */
function game_players_rules_event_info() {

  $items = array(
      'game_join' => array(
          'label' => t('Game Join'),
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

/**
 * Hook rules_action_info
 * @return type
 */
function game_players_rules_action_info() {
  return array(
      'rules_game_set_winners' => array(
          'label' => t('Game set winner'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
              ),
              'player_id' => array(
                  'type' => 'text',
                  'label' => 'player_id',
              ),
          ),
          'group' => t('Game'),
          'base' => 'rules_game_set_winners',
          'callbacks' => array(
              'validate' => 'rules_game_set_winners_validation',
          ),
      ),
      'rules_player_join_game' => array(
          'label' => t('Game Join Game'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
              ),
              'game' => array(
                  'type' => 'game',
                  'label' => 'game',
              ),
          ),
          'group' => t('Game'),
          'base' => 'rules_player_join_game',
          'callbacks' => array(
              'validate' => 'rules_player_join_game_validation',
          ),
      ),
  );
}

/**
 * rules_player_join_game
 * allow user to join a game.
 * @param type $running_game
 * @param type $game
 * @return type
 */
function rules_player_join_game($running_game, $game) {
  $callbacks;
  //  check if user is playing current game

  $query = new EntityFieldQuery;
  $result = $query
          ->entityCondition('entity_type', 'running_game_player')
          ->propertyCondition('running_game_id', $running_game->id)
          ->propertyCondition('player_session', session_id())
          ->execute();
  $query = new EntityFieldQuery;
  $players = $query
          ->entityCondition('entity_type', 'running_game_player')
          ->propertyCondition('running_game_id', $running_game->id)
          ->execute();
  //  if user is currently register to this game
  if (isset($result['running_game_player'])) {
    return drupal_json_encode(array("message" => "Already joind game, please be patiant or ask a friend to join.", "players_count" => count($result['running_game_player']), "time" => time()));
    //return null;
  }
  // check if user can join current game
  $game->field_max_num_players;
  $game->field_min_num_players;
  $num_of_players = count($players['running_game_player']);

  if ($num_of_players >= $game->field_max_num_players['und'][0]['value'] && $game->field_max_num_players['und'][0]['value'] != -1) {
    dpm("Game is already full");
    return drupal_json_encode(array("message" => "Game is already full", "time" => time()));
    return null;
  }

  $can_start_game = false;

  if (( $num_of_players + 1) >= $game->field_min_num_players['und'][0]['value'] || $game->field_min_num_players['und'][0]['value'] == -1) {
    $can_start_game = true;
  }
  //$can_start_game = true;

  $player_name = trim($action['player_name']);
  if (empty($player_name)) {
    $player_name = "Player" . ($num_of_players + 1);
  }

  //  Create an instance of current user to play this game
  $running_game_player = array();
  $running_game_player['running_game_id'] = $running_game->id;
  $running_game_player['bundle'] = 'running_game_player';
  $running_game_player['player_name'] = $player_name;

  $running_game_player_entity = entity_create("running_game_player", $running_game_player);

  if ($running_game_player_entity->save()) {
    $callbacks = array("callbacks" => array(
            array("fn" => "message", "module" => "RunningGame", "params" => array("user " . $player_name . " has joined the game")),
            array("fn" => "set_players_count", "module" => "GamePlayers", "params" => ($num_of_players + 1))));




    //  check if command can occure
      //  allow game to start
      if ($can_start_game) {
        $callbacks['callbacks'][] = array("fn" => "show_start_game_button", "module" => "RunningGame", "params" => "1");
      }

      //echo drupal_json_encode(array("message" => "user " . $player_name . " has joined the game", "time" => time()));
      //  Write to other user that a new user has just joined in

      /* return array(
        array("command_id" => -1, "command_data" => array("callback" => array("fn" => "set_player_name", "module" => "RunningGame", "params" => $player_name))),
        array("command_id" => -1, "command_data" => array("callback" => array("fn" => "set_players_count", "module" => "RunningGame", "params" => ($num_of_players + 1))))
        ); */

    $callbacks["time"] = time();
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode($callbacks);
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }

  //echo drupal_json_encode($game);
  //echo drupal_json_encode(array("Error" => $aid, "time" => time()));
  //break;
}

function rules_player_join_game_validation() {

  return true;
}

function rules_game_set_winners($running_game, $player_id) {
  //dpm("rules_game_set_winners player_id:" . $player_id);
  // the game can only define a winner once whan game is beaing played
  if (!empty($running_game)) {

    // load player
    $conditions = array("running_game_id" => $running_game->id, 'player_turn' => $player_id);
    $entity = entity_load("running_game_player", FALSE, $conditions);
    $player = $entity[key($entity)];
    $player->player_name;

    //  inform all players game winner
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(array("message" => $player->player_name . " won the game", "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }

  // change game mod to ended inform all other player game ended
}

function rules_game_set_winners_validation() {
  return true;
}