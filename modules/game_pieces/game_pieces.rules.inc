<?php

function game_pieces_rules_action_info() {

  return array(
      'piece_move' => array(
          'label' => t('piece move'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'piece' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => 'tile_position',
                  'optional' => FALSE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'piece_move',
          'callbacks' => array(
              'validate' => 'piece_move_validation',
          ),
      ),
      'piece_create' => array(
          'label' => t('piece Create'),
          'parameter' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => 'running_game',
                  'optional' => FALSE,
              ),
              'piece_type' => array(
                  'type' => 'text',
                  'label' => 'piece_type',
                  'optional' => FALSE,
                  'descritpion' => "Machine name of piece type",
                  'options list' => "get_all_piece_tyes",
              ),
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => 'tile_position',
                  'optional' => FALSE,
              )
          ),
          'group' => t('Game Board'),
          'base' => 'piece_create',
          'callbacks' => array(
              'validate' => 'piece_create_validation',
          ),
      ),
  );
}

function get_all_piece_tyes() {
  $r = array();
  $e = entity_load("piece_type");
  foreach ($e as $val) {
    $r[$val->type] = $val->label;
  }
  return $r;
}

/**
 * function piece_create_validation() {
 * @return boolean
 */
function piece_create_validation($running_game = null, $piece_type = null, $tile_position = -1) {
  if (property_exists($running_game, "field_pieces")) {
    return false;
  }
  if ($tile_position < 0) {
    return false;
  }
  return true;
}

function piece_create($running_game = null, $piece_type = null, $tile_position = -1) {

  // create piece
  $entity_type = "piece";
  $piece = entity_create($entity_type, array());

  $piece_type_entity = reset(entity_load("piece_type", FALSE, array("type" => $piece_type)));

  $piece->label = $piece_type_entity->symbol;
  $piece->type = $piece_type;
  $piece->position = $tile_position;
  $piece->uid = -1;

  piece_save($piece);

  // put it in running game
  $running_game->field_pieces["und"][]["target_id"] = $piece->id;


  // notify exsting users
  if ($running_game->save()) {
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "GamePieces", "fn" => "create_piece", "params" => array("tile_position" => $tile_position, "piece" => $piece, "piece_type" => $piece_type)), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }
}

function piece_move_validation($running_game = null, $piece = null, $tile_position = -1) {
  return true;
}

function piece_move($running_game = null, $piece = null, $tile_position = -1) {
  $piece->position = $tile_position;
  if ($piece->save()) {
    $running_game_command = array();
    $running_game_command['running_game_id'] = $running_game->id;
    $running_game_command['command_id'] = 1;
    $running_game_command['command_data'] = drupal_json_encode(array("callback" => array("module" => "GamePieces", "fn" => "move_piece", "params" => array("tile_position" => $tile_position, "piece" => $piece)), "time" => time()));
    $running_game_command_entity = entity_create("running_game_command", $running_game_command);
    $running_game_command_entity->save();
  }
}

/**
 * Hook_rules_event_info
 * @return array
 */
function game_pieces_rules_event_info() {
  $items = array(
      'piece_move_to_tile' => array(
          'label' => t('Piece Move'),
          'group' => t('Game Rules'),
          'variables' => array(
              'piece' => array(
                  'type' => 'piece',
                  'label' => 'piece',
                  'optional' => FALSE,
              ),
              'tile_position' => array(
                  'type' => 'integer',
                  'label' => t('Tile position'),
              ),
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => t('Running Game'),
              ),
              'game' => array(
                  'type' => 'game',
                  'label' => t('Game'),
              ),
          ),
      ),
  );

  return $items;
}

