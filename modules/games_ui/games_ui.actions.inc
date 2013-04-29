<?php

define("GAME_STATUS_NOT_STARTED", 1); // Wating for players to join
define("GAME_STATUS_STARTED", 2); // Game is in progress
define("GAME_STATUS_ENDED", 3); // Game Ended

define("PLAYER_STATUS_JOINED", 1);
define("PLAYER_STATUS_PLAYING", 2);
define("PLAYER_STATUS_IDLE", 3);
define("PLAYER_STATUS_LEFT", 3);
define("PLAYER_STATUS_WON", 4);
define("PLAYER_MAX_IDLE_TIME", 120); // in seconds

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
    /**
     * Joining a game instance 
     */
    case "join":
      //  check if user is playing current game
      $query = new EntityFieldQuery;
      $result = $query
              ->entityCondition('entity_type', 'running_game_participant')
              ->propertyCondition('running_game_id', $running_game->id)
              ->execute();
      //  if user is currently register to this game
      if (isset($result['running_game_participant'][session_id()])) {
        echo drupal_json_encode(array("message" => "Already joind game, please be patiant or ask a friend to join.", "players_count" => count($result['running_game_participant']), "time" => time()));
        return null;
      }
      // check if user can join current game
      $game->field_max_num_players;
      $game->field_min_num_players;

      if (count($result['running_game_participant']) >= $game->field_max_num_players['und'][0]['value'] && $game->field_max_num_players['und'][0]['value']!=-1 ) {
        echo drupal_json_encode(array("message" => "Game is already full", "time" => time()));
        return null;
      }

      $can_start_game = false;
      $num_of_players = count($result['running_game_participant']);
      if (( $num_of_players + 1) >= $game->field_min_num_players['und'][0]['value'] ||  $game->field_min_num_players['und'][0]['value']==-1) {
        $can_start_game = true;
      }
      //$can_start_game = true;

      $player_name = trim($action['player_name']);
      if (empty($player_name)) {
        $player_name = "Player" . ($num_of_players + 1);
      }

      //  Create an instance of current user to play this game
      $running_game_participant = array();
      $running_game_participant['running_game_id'] = $running_game->id;
      $running_game_participant['bundle'] = 'running_game_participant';
      $running_game_participant['participant_name'] = $player_name;

      $running_game_participant_entity = entity_create("running_game_participant", $running_game_participant);

      if ($running_game_participant_entity->save()) {

        //  Write to other user that a new user has just joined in
        $running_game_command = array();
        $running_game_command['running_game_id'] = $running_game->id;
        $running_game_command['command_id'] = 1;
        $running_game_command['command_data'] = drupal_json_encode(array("message" => "user " . $player_name . " has joined the game","callback" => array("fn" => "set_players_count", "module" => "RunningGame", "params" => ($num_of_players+1)), "time" => time()));
        $running_game_command_entity = entity_create("running_game_command", $running_game_command);


        //  check if command can occure
        if ($running_game_command_entity->save()) {
          if (count($result['running_game_participant']) >= $game->field_max_min_players['und'][0]['value']) {
            //  allow game to start
            if ($can_start_game) {
              $running_game_command2 = array();
              $running_game_command2['running_game_id'] = $running_game->id;
              $running_game_command2['command_id'] = 1;
              $running_game_command2['command_data'] = drupal_json_encode(array("callback" => array("fn" => "show_start_game_button", "module" => "RunningGame", "params" => "1"), "time" => time()));
              $running_game_command_entity2 = entity_create("running_game_command", $running_game_command2);
              $running_game_command_entity2->save();
            }
          }
          //echo drupal_json_encode(array("message" => "user " . $player_name . " has joined the game", "time" => time()));
          echo drupal_json_encode(array(
              array("command_id" => -1, "command_data" => array("callback" => array("fn" => "set_player_name", "module" => "RunningGame", "params" => $player_name))),
              array("command_id" => -1, "command_data" => array("callback" => array("fn" => "set_players_count", "module" => "RunningGame", "params" => ($num_of_players+1))))
          ));
          return null;
        } else {
          drupal_json_encode(array("message" => "opps somthing went wrong could not save game", "time" => time()));
          return null;
        }
      }

      //echo drupal_json_encode($game);
      echo drupal_json_encode(array("Error" => $aid, "time" => time()));
      break;
    /**
     * will trigger a logic command in the apropriate module
     */
    case "trigger":
      //dpm($action);
      $action['params'];
      // Ask the trigger module for all actions enqueued for the 'hook' trigger.
      /**/ /* $aids = game_ui_trigger_get_assigned_actions($action['hook']); */
      //$aids = trigger_get_assigned_actions('game_board_tile_on_click');
      //
      // prepare a basic context, indicating group and "hook", and call all the
      // actions with this context as arguments.
      $context = array(
          'group' => 'game',
          'hook' => $action['hook'],
          'params' => $action['params'],
      );
      // Always add game instance to rules_invoke_event
      $action['params']['running_game']=$running_game;
      $action['params']['game']=$game;

      
      // Events are invoked by the event name, followed by the event variables in
      // the same order as they are listed in the event declaration. You can also
      // use rules_invoke_event_by_args() to call the event with all the variables
      // collected in an associative array – which is particularly useful if there
      // are a shifting number of variables
      //dpm($action['hook']);
      //dpm($running_game);
      //dpm($action['params']);
      //dpm($action['params']);
      //$response = rules_invoke_event($action['hook'], $action['params'], $running_game);
      
      $response = rules_invoke_event_by_args($action['hook'], $action['params']);
      
      //rules_invoke_event($action['hook'], $action['params']);
      //echo drupal_json_encode(array("Return" => $action_return, "time" => time(), "action" => $action));
      //  change game status
      if ($action['hook'] == "game_start") {
        // Notice : need to check if game can change the status to start
        // load all players and add there turn in the game the count starts with 1,2,3,4... etc
        // db query
        $query = db_select('running_game_participant', 'p')->fields('p')->condition('running_game_id', $running_game->id, '=');
        $players = $query->execute();

        $i = 1;
        $first_player;
        foreach ($players as $player) {
          if ($i == 1) {
            $first_player = $player->participant_name;
          }
          $player->status = PLAYER_STATUS_PLAYING;
          $player->participant_turn = $i;
          entity_save("running_game_participant", $player);
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
        if ($running_game->save()) {
          //  game saved
        } else {
          //  problom saving game
        }
      }

      echo drupal_json_encode(array(""));
      return;

      //echo drupal_json_encode(array("Error" => $_POST, "time" => time()));
      break;

    case "command":


      /* check id a user is idle for over a minute */
      $now = time();
      $query2 = db_select('running_game_participant', 'p');
      $query2->fields('p', array('running_game_id', 'participant_session', 'participant_name', 'status'))
              ->condition('p.running_game_id', $running_game->id, '=')
              ->condition('p.alive', ($now - (PLAYER_MAX_IDLE_TIME)), '<')
              ->condition("p.status", PLAYER_STATUS_PLAYING, "=")
              ->orderBy('p.alive', 'ASC');

      $players = $query2->execute();




      $i = 0;
      foreach ($players as $player) {
        $query = db_update('running_game_participant');
        $query->fields(array('status' => PLAYER_STATUS_IDLE))
                ->condition('running_game_id', $running_game->id, '=')
                ->condition('participant_session', $player->participant_session, '=')
                ->execute();
        //  Add command user is idle
        /*        $running_game_command = array();
          $running_game_command['running_game_id'] = $running_game->id;
          $running_game_command['command_id'] = 1;
          $running_game_command['command_data'] = drupal_json_encode(array("message" => "user " .$player->participant_name . " is IDLE", "time" => time()));
          $running_game_command_entity = entity_create("running_game_command", $running_game_command);

          //  check if command can occure
          $running_game_command_entity->save();
         * 
         */
      }

      //  $action['time'];
      //   change user time stamp to now
      //  find new command that had been done by other players

      $query = db_update('running_game_participant');
      $query->fields(array('alive' => time()))
              ->condition('running_game_id', $running_game->id, '=')
              ->condition('participant_session', session_id(), '=')
              ->execute();


      $query = db_select('running_game_command', 'c');
      $query->fields('c', array('id', 'command_id', 'command_data', 'command_time'))
              ->condition('c.running_game_id', $running_game->id, '=')
              ->condition('c.command_time', $action['time'], '>=')
              ->condition('c.id', $action['id'], '>')
              ->orderBy('c.command_time', 'ASC');

      $commands = $query->execute();



      //  a better way of doing this


      /*
       * $query = new EntityFieldQuery;
       * $results = $query
        ->entityCondition('entity_type', 'running_game_command')
        ->propertyCondition('running_game_id', $running_game->id)
        //->fieldCondition("command_id")
        //->propertyCondition('command_time', $action['time'], ">")
        ->execute();
       */

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
  //$tabs = module_invoke_all('uiu_mgn_tabs', $tabs);
  //$running_game
  //arg()
  //$_POST
  //echo  drupal_json_encode($_POST['action']);
  return null;
}

function check_if_user_left($running_game) {
  $query = new EntityFieldQuery;
  $result = $query
          ->entityCondition('entity_type', 'running_game_participant')
          ->propertyCondition('running_game_id', $running_game->id)
          ->execute();
}

/**
 * Gets the action IDs of actions to be executed for a hook.
 *
 * @param $hook
 *   The name of the hook being fired.
 *
 * @return
 *   An array whose keys are action IDs that the user has associated with
 *   this trigger, and whose values are arrays containing the action type and
 *   label.
 */
/*
function game_ui_trigger_get_assigned_actions($hook) {
  $actions = &drupal_static(__FUNCTION__, array());
  if (!isset($actions[$hook])) {
    $actions[$hook] = db_query("SELECT ta.aid, a.type, a.label FROM {trigger_assignments} ta LEFT JOIN {actions} a ON ta.aid = a.aid WHERE ta.hook = :hook ORDER BY ta.weight", array(
      ':hook' => $hook,
    ))->fetchAllAssoc('aid', PDO::FETCH_ASSOC);
  }
  return $actions[$hook];
}

*/