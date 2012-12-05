<?php

/**
 * Generates the game type editing form.
 */
function game_type_form($form, &$form_state, $game_type, $op = 'edit') {

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
        '#submit' => array('game_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing game_type.
 */
function game_type_form_submit(&$form, &$form_state) {
  $game_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  game_type_save($game_type);

  // Redirect user back to list of game types.
  $form_state['redirect'] = 'admin/structure/game-types';
}

function game_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/game-types/' . $form_state['game_type']->type . '/delete';
}

/**
 * Game type delete form.
 */
function game_type_form_delete_confirm($form, &$form_state, $game_type) {
  $form_state['game_type'] = $game_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['game_type_id'] = array('#type' => 'value', '#value' => entity_id('game_type', $game_type));
  return confirm_form($form, t('Are you sure you want to delete game type %title?', array('%title' => entity_label('game_type', $game_type))), 'game/' . entity_id('game_type', $game_type), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Game type delete form submit handler.
 */
function game_type_form_delete_confirm_submit($form, &$form_state) {
  $game_type = $form_state['game_type'];
  
  game_type_delete($game_type);

  watchdog('game_type', '@type: deleted %title.', array('@type' => $game_type->type, '%title' => $game_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $game_type->type, '%title' => $game_type->label)));

  $form_state['redirect'] = 'admin/structure/game-types';
}

/**
 * Page to select game Type to add new game.
 */
function game_admin_add_page() {
  $items = array();
  foreach (game_types() as $game_type_key => $game_type) {
    $items[] = l(entity_label('game_type', $game_type), 'game/add/' . $game_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of game to create.')));
}

/**
 * Add new game page callback.
 */
function game_add($type) {
  $game_type = game_types($type);

  $game = entity_create('game', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('game_type', $game_type))));

  $output = drupal_get_form('game_form', $game);

  return $output;
}

/**
 * Game Form.
 */
function game_form($form, &$form_state, $game) {

  $form_state['game'] = $game;

  $form['title'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' => t('Name'),
      '#default_value' => $game->title,
  );

  $form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => $game->description,
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
      '#submit' => $submit + array('game_form_submit'),
  );

  // Show Delete button if we edit game.
  $game_id = entity_id('game', $game);
  if (!empty($game_id) && game_access('edit', $game)) {
    $form['actions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
        '#submit' => array('game_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'game_form_validate';

  return $form;
}

function game_form_validate($form, &$form_state) {
  
}

/**
 * Game submit handler.
 */
function game_form_submit($form, &$form_state) {
  $game = $form_state['game'];


  entity_form_submit_build_entity('game', $game, $form, $form_state);

  game_save($game);

  $game_uri = entity_uri('game', $game);

  $form_state['redirect'] = $game_uri['path'];

  drupal_set_message(t('Game %title saved.', array('%title' => entity_label('game', $game))));
}

function game_form_submit_delete($form, &$form_state) {
  $game = $form_state['game'];
  $game_uri = entity_uri('game', $game);
  $form_state['redirect'] = $game_uri['path'] . '/delete';
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

  $form_state['redirect'] = '<front>';
}

/* function game_instance_admin_add_page() {
  $items = array();
  foreach (game_types() as $game_type_key => $game_type) {
  $items[] = l(entity_label('game_type', $game_type), 'game/add/' . $game_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of game to create.')));
  } */

/**
 * Generates the game instance editing form.
 */
function game_instance_form($form, &$form_state, $game_instance, $op = 'edit') {
  if (empty($game_instance) && isset($form_state['game_instance'])) {

    $game_instance = $form_state['game_instance'];
  } else {

    $form_state['game_instance'] = $game_instance;
    if (isset($game_instance->gid) && !isset($form_state['values']['gid'])) {
      $form_state['values']['gid'] = $game_instance->gid;
    }
  }
  //dpm($game_instance);

  if ($op == 'clone') {
    //  $game_instance->label .= ' (cloned)';
    // $game_instance->type = '';
  }

  if (!isset($game_instance->gid)) {
    $game_instance->gid = '';
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
        '#default_value' => $game_instance->gid,
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
        '#submit' => array('game_instance_bundle_form'),
    );
  } else {
    if (!empty($game)) {
      //dpm($game);
      //$game_instance->type=$game[$form_state['values']['gid']]->type;
      $game_instance->type = $game->type;
      $game_instance->gid = $form_state['values']['gid'];
      //$form_state['game'] = $game[$game_instance->gid];
      $form_state['game'] = $game;
      //field_attach_form('game', $game[$game_instance->gid], $form, $form_state);
      field_attach_form('game', $game, $form, $form_state);
    }
    
    field_attach_form('game_instance', $game_instance, $form, $form_state);
    
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save game instance'),
        '#weight' => 40,
    );

    if (!$game_instance->isLocked() && $op != 'add' && $op != 'clone') {
      $form['actions']['delete'] = array(
          '#type' => 'submit',
          '#value' => t('Delete game instance'),
          '#weight' => 45,
          '#limit_validation_errors' => array(),
          '#submit' => array('game_instance_form_submit_delete')
      );
    }
  }
  return $form;
}

function game_instance_bundle_form(&$form, &$form_state) {
  $current_step = &$form_state['step'];
  //  save information

  $form_state['game_instance'] = $form_state['game_instance'];
  //  go to next step
  $current_step++;
  $form_state['rebuild'] = TRUE;
  return;
}

/**
 * Submit handler for creating/editing game_type.
 */
function game_instance_form_submit(&$form, &$form_state) {
  $game_instance = $form_state['game_instance'];
  //dpm($form_state);
  $game = entity_load('game', array($game_instance->gid));

  entity_form_submit_build_entity('game_instance', $game_instance, $form, $form_state);

  game_instance_save($game_instance);

  $game_instance_uri = entity_uri('game_instance', $game_instance);

  $form_state['redirect'] = $game_instance_uri['path'];

  drupal_set_message(t('Game %title saved.', array('%title' => entity_label('game_instance', $game_instance))));
}

function game_instance_create_instance($game) {
  $game->gid;

  $game_instance = array();
  $game_instance['gid'] = $game->gid;
  $game_instance['type'] = $game->type;
  $game_instance['bundle'] = 'game_instance';

  $game_instance_entity = entity_create("game_instance", $game_instance);
  $game_instance_entity->save();

  $game_instance_uri = entity_uri('game_instance', $game_instance_entity);
  drupal_goto($game_instance_uri['path']);
  return "This page is a redirect";
}

function game_instance_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/game-instances/' . $form_state['game_instance']->id . '/delete';
}

function game_instance_participant_create_participant($game_instance) {
  $game_instance_participant = array();
  $game_instance_participant['instance_id'] = $game_instance->id;
  $game_instance_participant['bundle'] = 'game_instance_participant';
  //dpm($game_instance);

  $game_instance_entity = entity_create("game_instance_participant", $game_instance_participant);
  $game_instance_entity->save();
  return true;
}

/**
 * Game type delete form.
 */
function game_instance_form_delete_confirm($form, &$form_state, $game_instance) {
  //print "11";
  //die();
  $form_state['game_instance'] = $game_instance;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['game_instance_id'] = array('#type' => 'value', '#value' => entity_id('game_instance', $game_instance));
  return confirm_form($form, t('Are you sure you want to delete game instance %session?', array('%session' => entity_label('game_instance', $game_instance))), 'game/' . entity_id('game_instance', $game_instance), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Game type delete form submit handler.
 */
function game_instance_form_delete_confirm_submit($form, &$form_state) {
  $game_instance = $form_state['game_instance'];
  //dpm($game_instance);

  game_instance_delete($game_instance);

  watchdog('game_instance', '@type: deleted %title.', array('@type' => $game_instance->type, '%title' => $game_instance->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $game_instance->type, '%title' => $game_instance->session)));

  $form_state['redirect'] = 'admin/structure/game-instances';
}

function game_create_instance($game) {
  
  // create instance and redirect to that instance to start playing
  return game_instance_create_instance($game);
}

