<?php
/**
 * @file
 * the resurces running game adds
 */

/**
 * 
 * Enter description here ...
 * @param unknown_type $id
 */
function _running_game_resource_trigger($id=0, $event='', $params = array()) {
  $running_game = current(entity_load("running_game",FALSE,array('id'=>$id)));
  if(empty($running_game) ) {
    return services_error('running game id dosenot exsit', 406);
  } 
    //  load game instance
  $game = game_load($running_game->gid);
  
  //game_start
  
  //tile_set
  // params : tile_position
  // params : tile_value
  
  $params['running_game'] = $running_game;
  $params['game'] = $game;
  
  $response = rules_invoke_event_by_args($event, $params);
  $game_response = $_SESSION['game_response'];
  unset($_SESSION['game_response']);
  if (empty($game_response)) {
    $response = array();
  }
  if (empty($game_response)) {
    $response;
  }
  
  return (object)$response;
  
  //return (object)array('id'=>$id,'event'=>$event,'params'=>$params);
}
function _running_game_resource_command($id=0, $time=NULL, $command_id=0) {
  
  if(empty($time)) {
    $time=time();
  }
  /*
  $running_game = current(entity_load("running_game",FALSE,array('id'=>$id)));
  if(empty($running_game) ) {
    return services_error('running game id dosenot exsit', 406);
  }
  //  load game instance
  $game = game_load($running_game->gid);  
  
  // invoke other modules for this event
  foreach (module_implements('game_command') as $module) {
    $function = $module . '_game_command';
    $function($running_game, $game);
  }

  // check for stored commands
  $query = db_select('running_game_command', 'c');
  $query->fields('c', array('id', 'command_id', 'command_data', 'command_time'))
          ->condition('c.running_game_id', $running_game->id, '=')
          ->condition('c.command_time', $time, '>=')
          ->condition('c.id', $command_id, '>')
          ->orderBy('c.command_time', 'ASC');

  $commands = $query->execute();

  $i = 0;
  $array = Array();
  foreach ($commands as $command) {
    $array[$i]['command_id'] = $command->command_id;
    $array[$i]['command_time'] = $command->command_time;
    $array[$i]['command_data'] = $command->command_data;
    $array[$i]['id'] = $command->id;
    $i++;
  }
  */
  return (object)array("ok"=>'22','id'=>$id);
}