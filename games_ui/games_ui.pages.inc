<?php

/**
 * Game view callback.
 */
function game_ui_view($game) {

  drupal_set_title(entity_label('game', $game));
  $id = entity_id('game', $game);
  $output = entity_view('game', array(entity_id('game', $game) => $game), 'full');
  return $output;//
}

function game_ui_play($running_game) {

  drupal_session_start();
  drupal_set_title("");
  global $user;
  $game = game_load($running_game->gid);

  $player_joined_game = false;
  $query = new EntityFieldQuery;
  $result = $query
          ->entityCondition('entity_type', 'running_game_participant')
          ->propertyCondition('running_game_id', $running_game->id)
          //->propertyCondition('participant_session', session_id(), "=")
          ->execute();
  $players = array();
  $keys = array();
  if (!empty($result['running_game_participant'])) {
    $keys = array_keys($result['running_game_participant']);
    $players = entity_load("running_game_participant", $keys);
  }

  //  if user is currently register to this game
  $player_name="";
  foreach ($players as $player) {
    if ($player->participant_session == session_id()) {
      $player_joined_game = true;
      $player_name=$player->participant_name;
    }
  }
  
  $num_players = count($players);
  //dpm($num_players);
  if(empty($num_players)) {
    $num_players='0';
  }
  drupal_add_js(array('RunningGame' => array('session' => session_id(), "instance" => $running_game, 'player_joined_game' => $player_joined_game, "num_players" => $num_players, "game" => $game, 'serverTime' => time())), 'setting');

  // hook_game_load
  // module_invoke_all("game_load");
  foreach (module_implements('game_init_load') as $module) {
    $function = $module . '_game_init_load';
    $function($game);
  }
  $s = array('Not created','Not Started','Started','Ended');
  $status = $s[$running_game->status];
  $output = theme('games_ui_play_template', array(
      'game' => $game,
      'running_game' => $running_game,
      'status' => $status,
      'num_players' => $num_players,
      'player_name' => $player_name
      )
  );

  return $output;
}