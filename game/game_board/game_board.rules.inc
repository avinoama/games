<?php

function game_board_rules_action_info() {

  return array(
      'rules_tile_set_owner' => array(
          'label' => t('Tile Set owner'),
          'parameter' => array(
              'account' => array(
                  'type' => 'user',
                  'label' => t('User to say hello to'),
              // If we were to make changes to the parameter object, whe should set
              // the 'save' property to TRUE. This makes Rules handle the saving in
              // a more optimized way than if each action saved the objects.
              // 'save' => TRUE,
              ),
              'game_instance' => array(
                'type' => 'entity',
                'label'=> 'game instance to react',
              ),
          ),
          'group' => t('Game Board'),
          'base' => 'rules_tile_set_owner',
          'callbacks' => array(
              'validate' => 'rules_tile_set_owner_validation',
          ),
      ),
  );
}

function rules_tile_set_owner($action, $game_instance) {
  global $user;
  dpm("rules_tile_set_owner " . session_id());
  dpm(print_r($action, 1) . print_r($game_instance, 1));
  $conditions = array("instance_id" => $game_instance->id, 'participant_session' => session_id());
  $entity = entity_load("game_instance_participant", FALSE, $conditions);

  //array("callback" => array("module" => "gameInstance", "fn" => "message", "params" => array("The tile is already owned")));

  return;
}

function rules_tile_set_owner_validation() {
  // dpm("rules_tile_set_owner_validation");
  return true;
}

function rules_tile_set_owner_callback() {
  dpm("rules_tile_set_owner_callback");
  //return "";
  //return array("callback" => array("module" => "gameInstance", "fn" => "message", "params" => array("The tile is already owned")));
  /*
    if ($context['game_id'] == $game_instance->gid) {

    $conditions = array("instance_id" => $game_instance->id, 'participant_session' => session_id());

    $entity = entity_load("game_instance_participant", FALSE, $conditions);
    $player = $entity[key($entity)];

    //dpm($player->participant_turn);
    // dpm($game_instance->field_matrix['und']);
    if ($game_instance->field_matrix['und'][$context['params']]['value'] == 0 || empty($game_instance->field_matrix['und'][$context['params']]['value'])) {
    $game_instance->field_matrix['und'][$context['params']]['value'] = $player->participant_turn;

    if ($game_instance->save()) {
    $params = array("tile_id" => $context['params'], "participant_turn" => $player->participant_turn);
    $game_instance_command = array();
    $game_instance_command['instance_id'] = $game_instance->id;
    $game_instance_command['command_id'] = 2;
    $game_instance_command['command_data'] = drupal_json_encode(array("message" => $context['message'], "callback" => array("module" => "boardGame", "fn" => $context['callback'], "params" => $params), "time" => time()));
    $game_instance_command_entity = entity_create("game_instance_command", $game_instance_command);
    $game_instance_command_entity->save();
    } else {

    dpm("cant save game instance");
    }
    } else {
    // the tile is already owned by user cannot
    return array("callback" => array("module" => "gameInstance", "fn" => "message", "params" => array("The tile is already owned")));
    //dpm("the tile is already owned by user cannot");
    }


    //  dpm("got to action " . game_board_tile_set_owner_action);
    }
   */
}

function game_board_rules_event_info() {
  $items = array(
      'tile_click' => array(
          'label' => t('After tile was clicked'),
          'group' => t('Game Rules'),
      // If the event provides any parameters to Rules, these are described with
      // the 'variables' property.
      /*
        'variables' => array(
        // Each provided variable is keyed by a given machine name, and work
        // very similar to how parameters and provided variables are desribed in
        // conditions and actions.
        'tile_num' => array(
        'type' => 'int',
        'label' => t('Tile num'),
        ),
        ),
       * 
       */
      ),
      'tile_hover' => array(
          'label' => t('After tile was hoverd'),
          'group' => t('Game Rules'),
          // If the event provides any parameters to Rules, these are described with
          // the 'variables' property.
          'variables' => array(
              // Each provided variable is keyed by a given machine name, and work
              // very similar to how parameters and provided variables are desribed in
              // conditions and actions.
              'tile_num' => array(
                  'type' => 'int',
                  'label' => t('Tile num'),
              ),
          ),
      ),
  );

  return $items;
}

/**
 * Implements hook_default_rules_configuration().
 */
function game_board_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = 'example default rule';
  $rule->active = FALSE;
  $rule->event('tile_click')
          ->condition(rules_condition('data_is', array('data:select' => 'entity:type', 'value' => "game_board")))
          ->action('drupal_message', array('message' => 'Test_11.'));

  $configs['rules_test_default_1'] = $rule;
  return $configs;
}

//rules_invoke_event('tile_hover', $game_instance);
//rules_invoke_event('tile_click', $game_instance);
