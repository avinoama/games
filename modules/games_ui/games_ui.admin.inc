<?php

/**
 * Generates the game type editing form.
 */
function game_ui_type_form($form, &$form_state, $game_type, $op = 'edit') {

  if ($op == 'clone') {
    $game_type->label .= ' (cloned)';
    $game_type->type = '';
  }

  $form['label'] = array(
      '#title' => t('Label'),
      '#type' => 'textfield',
      '#default_value' => $game_type->label,
      '#description' => t('The human-readable name of this game type.'),
      '#required' => TRUE,
      '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
      '#type' => 'machine_name',
      '#default_value' => isset($game_type->type) ? $game_type->type : '',
      '#maxlength' => 32,
      '#disabled' => $game_type->isLocked() && $op != 'clone',
      '#machine_name' => array(
          'exists' => 'game_types',
          'source' => array('label'),
      ),
      '#description' => t('A unique machine-readable name for this game type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
      '#type' => 'textarea',
      '#default_value' => isset($game_type->description) ? $game_type->description : '',
      '#description' => t('Description about the game type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save game type'),
      '#weight' => 40,
  );

  if (!$game_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete game type'),
        '#weight' => 45,
        '#limit_validation_errors' => array(),
        '#submit' => array('game_ui_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing game_type.
 */
function game_ui_type_form_submit(&$form, &$form_state) {
  $game_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  game_type_save($game_type);

  // Redirect user back to list of game types.
  $form_state['redirect'] = 'admin/structure/game-types';
}

function game_ui_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/game-types/manage/' . $form_state['game_type']->type . '/delete';
}

/**
 * Game type delete form.
 */
function game_ui_type_form_delete_confirm($form, &$form_state, $game_type) {
  $form_state['game_type'] = $game_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['game_type_id'] = array('#type' => 'value', '#value' => entity_id('game_type', $game_type));
  return confirm_form($form, t('Are you sure you want to delete game type %title?', array('%title' => entity_label('game_type', $game_type))), 'game/' . entity_id('game_type', $game_type), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Game type delete form submit handler.
 */
function game_ui_type_form_delete_confirm_submit($form, &$form_state) {
  $game_type = $form_state['game_type'];

  game_type_delete($game_type);

  watchdog('game_type', '@type: deleted %title.', array('@type' => $game_type->type, '%title' => $game_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $game_type->type, '%title' => $game_type->label)));

  $form_state['redirect'] = 'admin/structure/game-types';
}

/**
 * Page to select game Type to add new game.
 */
function game_ui_admin_add_page() {
  drupal_set_title(t("Game Add"));
  $items = array();
  foreach (game_types() as $game_type_key => $game_type) {
    $items[] = l(entity_label('game_type', $game_type), 'game/add/' . $game_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of game to create.')));
}

/**
 * Add new game page callback.
 */
function game_ui_add($type) {
  $game_type = game_types($type);

  $game = entity_create('game', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('game_type', $game_type))));

  return drupal_get_form('game_ui_form', $game);
}

/**
 * Game Form.
 */
function game_ui_form($form, &$form_state, $game) {

  $form_state['game'] = $game;

  $form['title'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' => t('Name'),
      '#default_value' => $game->title,
      '#weight' => -15,
  );

  $form['machine_name'] = array(
      '#type' => 'machine_name',
      '#required' => TRUE,
      '#title' => t('Machine Name'),
      '#default_value' => $game->machine_name,
      '#machine_name' => array(
          'exists' => 'game_ui_machine_name_exists',
          'source' => array('title'),
          'replace_pattern' => '[^a-z0-9-]+',
          'replace' => '-',
      ),
      '#weight' => -10,
  );

  $form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => $game->description,
      '#weight' => 20,
  );

  $form['uid'] = array(
      '#type' => 'value',
      '#value' => $game->uid,
  );

  field_attach_form('game', $game, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
      '#weight' => 100,
  );

  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save game'),
      '#submit' => $submit + array('game_ui_form_submit'),
  );

  // Show Delete button if we edit game.
  $game_id = entity_id('game', $game);
  if (!empty($game_id) && game_access('edit', $game)) {
    $form['actions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
        '#submit' => array('game_ui_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'game_ui_form_validate';

  return $form;
}

function game_ui_machine_name_exists() {
  return false;
}

function game_ui_form_validate($form, &$form_state) {
  
}

/**
 * Game submit handler.
 */
function game_ui_form_submit($form, &$form_state) {
  $game = $form_state['game'];

  entity_form_submit_build_entity('game', $game, $form, $form_state);

  if (!isset($game->entity_id)) {
    $game->entity_id = 1;
  }
  game_save($game);

  drupal_set_message(t('Game %title saved.', array('%title' => entity_label('game', $game))));
  $form_state['redirect'] = 'games';
}

function game_ui_form_submit_delete($form, &$form_state) {
  $game = $form_state['game'];
  $game_uri = entity_uri('game', $game);
  $form_state['redirect'] = $game_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function game_ui_delete_form($form, &$form_state, $game) {
  $form_state['game'] = $game;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['game_type_id'] = array('#type' => 'value', '#value' => entity_id('game', $game));
  $game_uri = entity_uri('game', $game);
  return confirm_form($form, t('Are you sure you want to delete game %title?', array('%title' => entity_label('game', $game))), $game_uri['path'], t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function game_ui_delete_form_submit($form, &$form_state) {
  $game = $form_state['game'];
  game_delete($game);

  drupal_set_message(t('Game %title deleted.', array('%title' => entity_label('game', $game))));

  $form_state['redirect'] = '<front>';
}

/* function running_game_admin_add_page() {
  $items = array();
  foreach (game_types() as $game_type_key => $game_type) {
  $items[] = l(entity_label('game_type', $game_type), 'game/add/' . $game_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of game to create.')));
  } */

/**
 * Generates the game instance editing form.
 */
function game_ui_instance_form($form, &$form_state, $running_game, $op = 'edit') {
  if (empty($running_game) && isset($form_state['running_game'])) {

    $running_game = $form_state['running_game'];
  } else {

    $form_state['running_game'] = $running_game;
    if (isset($running_game->gid) && !isset($form_state['values']['gid'])) {
      $form_state['values']['gid'] = $running_game->gid;
    }
  }

  if ($op == 'clone') {
    //  $running_game->label .= ' (cloned)';
    // $running_game->type = '';
  }

  if (!isset($running_game->gid)) {
    $running_game->gid = '';
  } else {
    $game_entities = entity_load('game', array($form_state['values']['gid']));
    $key = key($game_entities);
    $game = $game_entities[$key];
  }

  if (empty($form_state['step'])) {
    $form_state['step'] = 1;
  }
  $step = &$form_state['step'];
  if ($step == 1) {
    $games = entity_load('game');

    $string = array();

    foreach ($games as $key => $game) {
      $string[$key] = $game->label();
    }

    $form['gid'] = array(
        '#title' => t('Game'),
        '#type' => 'select',
        '#default_value' => $running_game->gid,
        '#description' => t('The human-readable name of this game.'),
        '#required' => TRUE,
        '#options' => $string,
    );
  }

  if ($step == 1 && $op == 'add') {
    $form['next'] = array(
        '#type' => 'submit',
        '#value' => t('Next'),
        '#name' => 'next',
        '#submit' => array('running_game_bundle_form'),
    );
  } else {
    if (!empty($game)) {
      $running_game->type = $game->type;
      $running_game->gid = $form_state['values']['gid'];
      $form_state['game'] = $game;
      field_attach_form('game', $game, $form, $form_state);
    }

    field_attach_form('running_game', $running_game, $form, $form_state);

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save game instance'),
        '#weight' => 40,
    );

    if (!$running_game->isLocked() && $op != 'add' && $op != 'clone') {
      $form['actions']['delete'] = array(
          '#type' => 'submit',
          '#value' => t('Delete game instance'),
          '#weight' => 45,
          '#limit_validation_errors' => array(),
          '#submit' => array('running_game_form_submit_delete')
      );
    }
  }
  return $form;
}

function game_ui_instance_bundle_form(&$form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['running_game'] = $form_state['running_game'];
  $current_step++;
  $form_state['rebuild'] = TRUE;
  return;
}

/**
 * Submit handler for creating/editing game_type.
 */
function game_ui_instance_form_submit(&$form, &$form_state) {
  $running_game = $form_state['running_game'];

  $game = entity_load('game', array($running_game->gid));

  entity_form_submit_build_entity('running_game', $running_game, $form, $form_state);

  running_game_save($running_game);

  $running_game_uri = entity_uri('running_game', $running_game);

  $form_state['redirect'] = $running_game_uri['path'];

  drupal_set_message(t('Game %title saved.', array('%title' => entity_label('running_game', $running_game))));
}

function game_ui_instance_create_instance($game) {
  $game->gid;

  $running_game = array();
  $running_game['gid'] = $game->gid;
  $running_game['type'] = $game->type;
  $running_game['bundle'] = 'running_game';

  $running_game_entity = entity_create("running_game", $running_game);
  $running_game_entity->save();

  $running_game_uri = entity_uri('running_game', $running_game_entity);
  drupal_goto($running_game_uri['path']);
  return "This page is a redirect";
}

function game_ui_instance_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/running-game/' . $form_state['running_game']->id . '/delete';
}

/**
 * Game type delete form.
 */
function game_ui_instance_form_delete_confirm($form, &$form_state, $running_game) {

  $form_state['running_game'] = $running_game;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['running_game_id'] = array('#type' => 'value', '#value' => entity_id('running_game', $running_game));
  return confirm_form($form, t('Are you sure you want to delete game instance %session?', array('%session' => entity_label('running_game', $running_game))), 'game/' . entity_id('running_game', $running_game), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Game type delete form submit handler.
 */
function game_ui_instance_form_delete_confirm_submit($form, &$form_state) {
  $running_game = $form_state['running_game'];

  running_game_delete($running_game);

  watchdog('running_game', '@type: deleted %title.', array('@type' => $running_game->type, '%title' => $running_game->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $running_game->type, '%title' => $running_game->session)));

  $form_state['redirect'] = 'admin/structure/game-instances';
}

/**
 * 
 * @param type $game
 */
function game_ui_create_instance($game) {
  // create instance and redirect to that instance to start playing
  game_ui_instance_create_instance($game);
}

/**
 * Delete confirmation form.
 */
function game_delete_form($form, &$form_state, $game) {
  $form_state['game'] = $game;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['game_type_id'] = array('#type' => 'value', '#value' => entity_id('game', $game));
  $game_uri = entity_uri('game', $game);
  return confirm_form($form, t('Are you sure you want to delete game %title?', array('%title' => entity_label('game', $game))), $game_uri['path'], t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function game_delete_form_submit($form, &$form_state) {
  $game = $form_state['game'];
  game_delete($game);

  drupal_set_message(t('Game %title deleted.', array('%title' => entity_label('game', $game))));

  $form_state['redirect'] = 'games';
}

/**
 *
 * @param type $form
 * @param type $form_state
 * @param type $op
 */
function game_ui_setting_form($form, &$form_state, $op = 'edit') {
  // long polling interval
  $form['label'] = array(
      '#title' => t('Long polling interval'),
      '#type' => 'textfield',
      '#default_value' => variable_get('game_poll', '4000'),
      '#description' => t('in millisecound'),
      '#required' => TRUE,
      '#size' => 30,
  );

  // players time out interval

  $form['player_idle_interval'] = array(
      '#title' => t('Player idle interval'),
      '#type' => 'textfield',
      '#default_value' => variable_get('player_idle', '10000'),
      '#description' => t('in millisecound'),
      '#required' => TRUE,
      '#size' => 30,
  );

  
  return $form;
}