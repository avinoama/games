<?php

/**
 * Game view callback.
 */
function game_ui_view($game) {
  drupal_set_title(entity_label('game', $game));
  return entity_view('game', array(entity_id('game', $game) => $game), 'full');
  ;
}

/**
 * 
 * @param type $game
 */
function game_ui_list_instances($game) {
  module_load_include('inc', 'game', 'game.define');

  $header = array(t('id'), t('Status'), t('Actions'));
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'running_game')
          ->propertyCondition('gid', $game->gid)
          ->propertyOrderBy('id', 'DESC');
          //->propertyCondition('status', GAME_STATUS_NOT_STARTED);
  $running_games = array();
  $result = $query->execute();
  if (isset($result['running_game'])) {
    $ids = array_keys($result['running_game']);
    $running_games = entity_load('running_game', $ids);
  }
  $s = array(t('Not created'), t('Not Started'), t('Started'), t('Ended'));

  $rows = array();
  foreach ($running_games as $running_game) {
   $rows[] = array($running_game->id, $s[$running_game->status] ,l('Join', 'play/' . $running_game->id));
  }
  
  $output = l(t('Create new game'), 'game/' . $game->gid . '/create');
  $output .= theme('table', array('header' => $header, 'rows' => $rows));

  return $output;
}

/**
 * show running game
 * @global type $user
 * @param type $running_game
 * @return type
 */
function game_ui_play($running_game) {
  global $user;
  drupal_session_start();
  drupal_set_title("");

  $game = game_load($running_game->gid);

  // hook_game_load
  // module_invoke_all("game_init_load");
  foreach (module_implements('game_init_load') as $module) {
    $function = $module . '_game_init_load';
    $function($game, $running_game);
  }

  drupal_add_js(array('RunningGame' => array(
          'session' => session_id(),
          'instance' => $running_game,
          'game' => $game,
          'player_idle_interval' => variable_get('player_idle_interval', '30000'),
          'game_poll_interval' => variable_get('game_poll_interval', '4000'),
          'time_to_show_each_message' => variable_get('time_to_show_each_message', '4000'),
          'time_to_bold_each_message' => variable_get('time_to_bold_each_message', '2000'),
          'serverTime' => time())), 'setting');

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