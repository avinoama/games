<?php

define("GAME_STATUS_NOT_STARTED", 1);
define("GAME_STATUS_STARTED", 2);
define("GAME_STATUS_ENDED", 3);

define("PLAYER_STATUS_JOINED", 1);
define("PLAYER_STATUS_PLAYING", 2);
define("PLAYER_STATUS_IDLE", 3);
define("PLAYER_STATUS_LEFT", 3);
define("PLAYER_STATUS_WON", 4);
define("PLAYER_MAX_IDLE_TIME", 120); // in seconds

/**
 * game_instance_ajax_callback( gameInstance )
 * 
 * @param type $game_instance
 * @return json object
 * 
 */
function game_ui_instance_ajax_callback($game_instance) {
  drupal_session_start();
  global $user;
  //ajax_get_form() function will be the drupal way of doing it
  $_SESSION["anonymous-tracker"] = time();

  //  load game instance
  $game = game_load($game_instance->gid);

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
              ->entityCondition('entity_type', 'game_instance_participant')
              ->propertyCondition('instance_id', $game_instance->id)
              ->execute();
      //  if user is currently register to this game
      if (isset($result['game_instance_participant'][session_id()])) {
        echo drupal_json_encode(array("message" => "Already joind game, please be patiant or ask a friend to join.", "players_count" => count($result['game_instance_participant']), "time" => time()));
        return null;
      }

      // check if user can join current game
      $game->field_max_num_players;
      $game->field_min_num_players;

      if (count($result['game_instance_participant']) >= $game->field_max_num_players['und'][0]['value']) {
        echo drupal_json_encode(array("message" => "Game is already full", "time" => time()));
        return null;
      }
      $can_start_game = false;
      $num_of_players =count($result['game_instance_participant']);
      if (( $num_of_players + 1) >= $game->field_min_num_players['und'][0]['value']) {
        $can_start_game = true;
      }
      $player_name = trim($action['player_name']);
      if(empty($player_name)) {
        $player_name="Player".($num_of_players+1);
      }
      //  Create an instance of current user to play this game
      $game_instance_participant = array();
      $game_instance_participant['instance_id'] = $game_instance->id;
      $game_instance_participant['bundle'] = 'game_instance_participant';
      $game_instance_participant['participant_name'] = $player_name;

      $game_instance_participant_entity = entity_create("game_instance_participant", $game_instance_participant);

      if ($game_instance_participant_entity->save()) {
        
        //  Write to other user that a new user has just joined in
        $game_instance_command = array();
        $game_instance_command['instance_id'] = $game_instance->id;
        $game_instance_command['command_id'] = 1;
        $game_instance_command['command_data'] = drupal_json_encode(array("message" => "user " . $player_name . " has joined the game", "time" => time()));
        $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);


        //  check if command can occure
        if ($game_instance_command_entity->save()) {
          if (count($result['game_instance_participant']) >= $game->field_max_nim_players['und'][0]['value']) {
            //  allow game to start
            $game_instance_command = array();
            $game_instance_command['instance_id'] = $game_instance->id;
            $game_instance_command['command_id'] = 1;
            $game_instance_command['command_data'] = drupal_json_encode(array("callback" => array("fn" => "show_start_game_button", "module" => "gameInstance", "params" => "1"), "time" => time()));
            $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
            $game_instance_command_entity->save();

            echo drupal_json_encode(array("message" => "user has joined the game, to start game press here", "time" => time()));
          } else {
            echo drupal_json_encode(array("message" => "user has joined the game", "time" => time()));
          }
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
      
      // Events are invoked by the event name, followed by the event variables in
      // the same order as they are listed in the event declaration. You can also
      // use rules_invoke_event_by_args() to call the event with all the variables
      // collected in an associative array – which is particularly useful if there
      // are a shifting number of variables.
      //dpm($action['params'] . " " . $action['hook']);
      //dpm($game_instance);
      //$game_instance->id
      rules_invoke_event($action['hook'], $game_instance, $action['params']);
      //rules_invoke_event($action['hook'], $action['params'], $game_instance);
      //rules_invoke_event($action['hook'], $game_instance, $action['params']);
      //rules_invoke_event($action['hook'], array("tile_position"=>$action['params'],"game_instance"=> $game_instance));
      //rules_invoke_component("this_tile_set_owner",array("game_instance"=>$game_instance, "tile_position"=>$action['params']));
      
      //$action_return = rules_invoke_event_by_args("ss" , array("game_instance"=>$game_instance,"tile_num"=>$action['params']));
      //$action_return = rules_invoke_event_by_args($action['hook'] , array("game_instance"=>$game_instance,"tile_position"=>$action['params']));
      
      //array("account"=>$user)
      
      //dpm ($action_return);
      //$action_return = actions_do(array_keys($aids), $game_instance, $context);

      echo drupal_json_encode(array("Return" => $action_return, "time" => time(), "action" => $action));

      //  change game status
      if ($action['hook'] == "game_start") {
        // Notice : need to check if game can change the status to start
        // load all players and add there turn in the game the count starts with 1....
        // db query
        $query = db_select('game_instance_participant', 'p')->fields('p')->condition('instance_id', $game_instance->id, '=');
        $players = $query->execute();

        $i = 1;
        $first_player;
        foreach ($players as $player) {
          if ($i == 1) {
            $first_player = $player->participant_name;
          }
          $player->status = PLAYER_STATUS_PLAYING;
          $player->participant_turn = $i;
          entity_save("game_instance_participant", $player);
          $i++;
        }

        // TODO : add command "turn Start for $first_player"
        /*
          $game_instance_command = array('instance_id' => $game_instance->id,
          'command_id' => 3,
          'command_data' => drupal_json_encode(array(
          "message" => "Game Started its ".$first_player. " turn" ,
          //  "callback" => array("fn"=>"start_game","module"=>"gameInstance","params"=>"1"),
          "time" => time()))
          ); */


        $game_instance_command = array();
        $game_instance_command['instance_id'] = 4;
        $game_instance_command['command_id'] = 1;
        $game_instance_command['command_data'] = drupal_json_encode(array("message" => "Game Started its " . $first_player . " turn", "time" => time()));
        $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
        $game_instance_command_entity->save();



        //  Start game
        $game_instance->started = REQUEST_TIME;
        $game_instance->status = GAME_STATUS_STARTED;
        if ($game_instance->save()) {


          //  game saved
          dpm("game saved");
        } else {
          //  problom saving game
        }
      }



      //echo drupal_json_encode(array("Error" => $_POST, "time" => time()));
      break;

    case "command":


      /* check id a user is idle for over a minutel */
      $now = time();
      $query2 = db_select('game_instance_participant', 'p');
      $query2->fields('p', array('instance_id', 'participant_session', 'participant_name', 'status'))
              ->condition('p.instance_id', $game_instance->id, '=')
              ->condition('p.alive', ($now - (PLAYER_MAX_IDLE_TIME)), '<')
              ->condition("p.status", PLAYER_STATUS_PLAYING, "=")
              ->orderBy('p.alive', 'ASC');

      $players = $query2->execute();




      $i = 0;
      foreach ($players as $player) {
        $query = db_update('game_instance_participant');
        $query->fields(array('status' => PLAYER_STATUS_IDLE))
                ->condition('instance_id', $game_instance->id, '=')
                ->condition('participant_session', $player->participant_session, '=')
                ->execute();
        //  Add command user is idle
        /*        $game_instance_command = array();
          $game_instance_command['instance_id'] = $game_instance->id;
          $game_instance_command['command_id'] = 1;
          $game_instance_command['command_data'] = drupal_json_encode(array("message" => "user " .$player->participant_name . " is IDLE", "time" => time()));
          $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);

          //  check if command can occure
          $game_instance_command_entity->save();
         * 
         */
      }

      //  $action['time'];
      //   change user time stamp to know
      //  find new command that had been done by other players

      $query = db_update('game_instance_participant');
      $query->fields(array('alive' => time()))
              ->condition('instance_id', $game_instance->id, '=')
              ->condition('participant_session', session_id(), '=')
              ->execute();


      $query = db_select('game_instance_command', 'c');
      $query->fields('c', array('command_id', 'command_data', 'command_time'))
              ->condition('c.instance_id', $game_instance->id, '=')
              ->condition('c.command_time', $action['time'], '>')
              ->orderBy('c.command_time', 'ASC');

      $commands = $query->execute();



      //  a better way of doing this


      /*
       * $query = new EntityFieldQuery;
       * $results = $query
        ->entityCondition('entity_type', 'game_instance_command')
        ->propertyCondition('instance_id', $game_instance->id)
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
        $i++;
      }


      echo drupal_json_encode($array);
      return null;
      break;
    /*

      case "game_start":



      echo drupal_json_encode(array("message" => "starting game", "time" => time()));
      return null;
      break;
     */
    default:
      echo drupal_json_encode(array("Error" => "command not known", "time" => time()));
      break;
  }
  //$tabs = module_invoke_all('uiu_mgn_tabs', $tabs);
  //$game_instance
  //arg()
  //$_POST
  //echo  drupal_json_encode($_POST['action']);
  return null;
}

function check_if_user_left($game_instance) {
  $query = new EntityFieldQuery;
  $result = $query
          ->entityCondition('entity_type', 'game_instance_participant')
          ->propertyCondition('instance_id', $game_instance->id)
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