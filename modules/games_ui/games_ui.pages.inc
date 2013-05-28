<?php

/**
 * Game view callback.
 */
//$id = entity_id('game', $game);
function game_ui_view($game) {
  drupal_set_title(entity_label('game', $game));
  return entity_view('game', array(entity_id('game', $game) => $game), 'full');;
}

function game_ui_play($running_game) {

  drupal_session_start();
  drupal_set_title("");
  global $user;
  $path = drupal_get_path('module', 'games_ui');
  drupal_add_js($path . "/jgrowl/jquery.jgrowl.js", 'file');
  drupal_add_css($path . "/jgrowl/jquery.jgrowl.css", 'file');


  $game = game_load($running_game->gid);

  // hook_game_load
  // module_invoke_all("game_init_load");
  foreach (module_implements('game_init_load') as $module) {
    $function = $module . '_game_init_load';
    $function($game, $running_game);
  }

  drupal_add_js(array('RunningGame' => array('session' => session_id(), "instance" => $running_game, "game" => $game, 'serverTime' => time())), 'setting');

  $s = array('Not created', 'Not Started', 'Started', 'Ended');
  $status = $s[$running_game->status];
  $output = theme('games_ui_play_template', array(
      'game' => $game,
      'running_game' => $running_game,
      'status' => $status
          )
  );


  return $output;
}