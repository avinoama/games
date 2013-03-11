<?php

/**
 * Game view callback.
 */
function game_view($game) {
  drupal_set_title(entity_label('game', $game));
  return entity_view('game', array(entity_id('game', $game) => $game), 'full');
}

function game_ui_play($game_instance) {

  drupal_session_start();
  drupal_set_title("");
  global $user;
  $game = game_load($game_instance->gid);

  $player_joined_game = false;
  $query = new EntityFieldQuery;
  $result = $query
          ->entityCondition('entity_type', 'game_instance_participant')
          ->propertyCondition('instance_id', $game_instance->id)
          //->propertyCondition('participant_session', session_id(), "=")
          ->execute();
  $players = array();
  $keys = array();
  if(!empty($result['game_instance_participant'])) {
  $keys = array_keys($result['game_instance_participant']);
  $players = entity_load("game_instance_participant", $keys);
  }
  //dpm($players);
  //  if user is currently register to this game
  
  foreach ($players as $player) {
    if ($player->participant_session == session_id()) {
      $player_joined_game = true;
    }
  }

  drupal_add_js(array('gameInstance' => array('session' => session_id(), "instance" => $game_instance, 'player_joined_game' => $player_joined_game, "num_players" => count($players), "game" => $game, 'serverTime' => time())), 'setting');

  // hook_game_load
  // module_invoke_all("game_load");
  foreach (module_implements('game_init_load') as $module) {
    $function = $module . '_game_init_load';
    $function($game);
  }
  drupal_set_message("&nbsp;");
  
  
  //$output = theme('games_ui_play_template');
  //echo $output;
  //return null;
  
  return "Loading game...";
}