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

  $path = drupal_get_path("module", 'game');
  require_once $path . '/game.define.inc';



  $title = t('All Open games');
  $type = 'ul';
// The following attributes apply to the list tag (e.g., <ol> or <ul>)
  $attributes = array(
      'id' => 'my-custom-listing',
      'class' => 'custom-class another-custom-class', // a string or indexed (string) array with the classes for the list tag
  );

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'running_game')
          ->propertyCondition('gid', $game->gid)
          ->propertyCondition('status', GAME_STATUS_NOT_STARTED);
  $running_games = array();
  $result = $query->execute();
  if (isset($result['running_game'])) {
    $ids = array_keys($result['running_game']);
    $running_games = entity_load('running_game', $ids);
  }
  $s = array('Not created', 'Not Started', 'Started', 'Ended');

  $items = array();
  foreach ($running_games as $running_game) {
    $items[] = array(
        'data' => $game->title . " - " . $s[$running_game->status] . " - " . l('Join', 'play/' . $running_game->id),
        'id' => $running_game->id, // be careful not to add another id attribute on the page that might be the same as one of the uids or your page will not validate
            //'class' => array_keys($account->roles), // value for 'class' key MUST be an (indexed) array. Using a string value like '2 3 4' produces an error
    );
  }
  $items[] = array('data' => l("create new", 'game/' . $game->gid . '/create'));

  return theme_item_list(array('items' => $items, 'title' => $title, 'type' => $type, 'attributes' => $attributes));
  ;
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