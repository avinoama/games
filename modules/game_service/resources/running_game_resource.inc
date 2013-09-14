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
  if(isset($params['tile_position'])) {
    $_POST['action']['params']['tile_position']=$params['tile_position'];
  }
  $_POST['action']['game']['session'] = $running_game->session;
   
  $response = rules_invoke_event_by_args($event, $params);
  if(isset($_SESSION['game_response'])) {
    $game_response = $_SESSION['game_response'];
    unset($_SESSION['game_response']);
  }
  if (empty($game_response)) {
    $response = array();
  }
  if (empty($game_response)) {
    $response;
  }
  
  return (object)$response;
  
  //return (object)array('id'=>$id,'event'=>$event,'params'=>$params);
}
function _running_game_resource_commands($id=0, $time=NULL, $command_id=0) {
  
  if(empty($time)) {
    $time=time();
  }
  
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
          //->condition('c.command_time', $time, '>=')
          ->condition('c.id', $command_id, '>')
          ->orderBy('c.command_time', 'ASC');

  $commands = $query->execute();

  $i = 0;
  $return = array();
  foreach ($commands as $command) {
    $return[$i]=array();
    $return[$i]['command_id'] = $command->command_id;
    $return[$i]['command_time'] = $command->command_time;
    $return[$i]['command_data'] = $command->command_data;
    $return[$i]['id'] = $command->id;
    $i++;
  }
  return (object)array('return'=>$return);
  
  //return (object)array("ok"=>'22','id'=>$id);
}