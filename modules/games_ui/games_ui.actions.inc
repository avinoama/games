<?php

/**
 * running_game_ajax_callback( RunningGame )
 * 
 * @param type $running_game
 * @return json object
 * 
 */
function game_ui_instance_ajax_callback($running_game) {
  drupal_session_start();
  global $user;
  //ajax_get_form() function will be the drupal way of doing it
  $_SESSION["anonymous-tracker"] = time();

  //  load game instance
  $game = game_load($running_game->gid);

  $tabs = array();

  //  get action to preform
  $action = $_POST['action'];

  //  switch between commands needed to be done
  switch ($action['command']) {
    case "trigger":
      $action['params'];
      // Ask the trigger module for all actions enqueued for the 'hook' trigger.
      // 
      // prepare a basic context, indicating group and "hook", and call all the
      // actions with this context as arguments.
      $context = array(
          'group' => 'game',
          'hook' => $action['hook'],
          'params' => $action['params'],
      );
      // Always add game instance to rules_invoke_event
      $action['params']['running_game'] = $running_game;
      $action['params']['game'] = $game;


      // Events are invoked by the event name, followed by the event variables in
      // the same order as they are listed in the event declaration. You can also
      // use rules_invoke_event_by_args() to call the event with all the variables
      // collected in an associative array – which is particularly useful if there
      // are a shifting number of variables

      $response = rules_invoke_event_by_args($action['hook'], $action['params']);
      
      if (empty($response)) {
        $response = array();
      }
      echo drupal_json_encode($response);
      return;

      //echo drupal_json_encode(array("Error" => $_POST, "time" => time()));
      break;

    case "command":

      // invoke other modules for this event
      foreach (module_implements('_game_command') as $module) {
        $function = $module . '_game_command';
        $function($running_game, $game);
      }

      // check for stored commands
      $query = db_select('running_game_command', 'c');
      $query->fields('c', array('id', 'command_id', 'command_data', 'command_time'))
              ->condition('c.running_game_id', $running_game->id, '=')
              ->condition('c.command_time', $action['time'], '>=')
              ->condition('c.id', $action['id'], '>')
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


      echo drupal_json_encode($array);
      return null;
      break;
    default:
      echo drupal_json_encode(array("Error" => "command not known " . $action['command'], "time" => time()));
      break;
  }
  return null;
}

function check_if_user_left($running_game) {
  $query = new EntityFieldQuery;
  $result = $query
          ->entityCondition('entity_type', 'running_game_player')
          ->propertyCondition('running_game_id', $running_game->id)
          ->execute();
}

