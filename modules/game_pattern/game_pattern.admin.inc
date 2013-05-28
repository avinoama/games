<?php

/**
 *
 * @param type $form
 * @param type $form_state
 * @param type $pattern_type
 * @param type $op
 * @return array
 */
function game_pattern_type_form($form, &$form_state, $pattern_type, $op = 'edit') {

  if ($op == 'clone') {
    $pattern_type->label .= ' (cloned)';
    $pattern_type->type = '';
  }
  if (property_exists($pattern_type, "symbol")) {
    $s = $$pattern_type->symbol;
  } else {
    $s = "";
  }

  $form['label'] = array(
      '#title' => t('Label'),
      '#type' => 'textfield',
      '#default_value' => $pattern_type->label,
      '#description' => t('The human-readable name of this piece type.'),
      '#required' => TRUE,
      '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
      '#type' => 'machine_name',
      '#default_value' => isset($pattern_type->type) ? $pattern_type->type : '',
      '#maxlength' => 32,
      '#disabled' => $pattern_type->isLocked() && $op != 'clone',
      '#machine_name' => array(
          'exists' => 'pattern_type_exists',
          'source' => array('label'),
      ),
      '#description' => t('A unique machine-readable name for this piece type. It must only contain lowercase letters, numbers, and underscores.'),
  );
  /*
    $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($pattern_type->description) ? $pattern_type->description : '',
    '#description' => t('Description about the piece type.'),
    );
   */


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save piece type'),
      '#weight' => 40,
  );


  if (!$pattern_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete piece type'),
        '#weight' => 45,
        '#limit_validation_errors' => array(),
        '#submit' => array('game_pattern_type_form_submit_delete')
    );
  }
  return $form;
}

function pattern_type_exists() {
  return FALSE;
}

/**
 * Submit handler for creating/editing game_pattern.
 */
function game_pattern_type_form_submit(&$form, &$form_state) {
  $game_pattern = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  game_pattern_save($game_pattern);

  // Redirect user back to list of piece types.
  $form_state['redirect'] = 'admin/structure/game-patterns';
}

function game_pattern_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/game-patterns/manage/' . $form_state['game_pattern_type']->type . '/delete';
}

/**
 * piece type delete form.
 */
function game_pattern_form_delete_confirm($form, &$form_state, $game_pattern) {
  $form_state['game_pattern'] = $game_pattern;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['game_pattern_id'] = array('#type' => 'value', '#value' => entity_id('game_pattern', $game_pattern));
  return confirm_form($form, t('Are you sure you want to delete piece type %title?', array('%title' => entity_label('game_pattern', $game_pattern))), 'pattren/' . entity_id('game_pattern', $game_pattern), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * piece type delete form submit handler.
 */
function game_pattern_form_delete_confirm_submit($form, &$form_state) {
  $game_pattern = $form_state['game_pattern'];

  game_pattern_delete($game_pattern);

  watchdog('game_pattern', '@type: deleted %title.', array('@type' => $game_pattern->type, '%title' => $game_pattern->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $game_pattern->type, '%title' => $game_pattern->label)));

  $form_state['redirect'] = 'admin/structure/game-patterns';
}

function game_pattern_admin_add_page() {
  drupal_set_title(t("Game Pattern Add"));
  $items = array();
  foreach (game_pattern_type_load() as $game_type_key => $game_type) {
    $items[] = l(entity_label('game_pattern', $game_type), 'pattern/add/' . $game_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of game to create.')));
}

/**
 *
 * @param type $type
 * @return type
 */
function game_pattern_add($type) {



  $game_pattern_type = game_types($type);

  $game_pattern = entity_create('game_pattern', array('type' => $type));

  drupal_set_title(t('Create @name', array('@name' => entity_label('game_pattern_type', $game_pattern_type))));

  return drupal_get_form('pattern_ui_form', $game_pattern);
}

/**
 *
 * @param type $form
 * @param array $form_state
 * @param type $pattern
 * @return string
 */
function pattern_ui_form($form, &$form_state, $pattern) {
  $path = drupal_get_path('module', 'game_pattern');
  drupal_add_js($path . "/game_pattern.js", 'file');
  drupal_add_css($path . "/game_pattern.css");
  drupal_add_js(array('pattern' => $pattern), 'setting');
  
  $form_state['pattern'] = $pattern;

  $form['label'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' => t('label'),
      '#default_value' => $pattern->label,
      '#weight' => -15,
  );

  $form['machine_name'] = array(
      '#type' => 'machine_name',
      '#required' => TRUE,
      '#title' => t('Machine Name'),
      '#default_value' => $pattern->machine_name,
      '#machine_name' => array(
          'exists' => 'pattern_ui_machine_name_exists',
          'source' => array('label'),
          'replace_pattern' => '[^a-z0-9-]+',
          'replace' => '-',
      ),
      '#weight' => -10,
  );

  field_attach_form('game_pattern', $pattern, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
      '#weight' => 100,
  );

  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save Pattern'),
      '#submit' => $submit + array('pattern_ui_form_submit'),
  );

  // Show Delete button if we edit game.
  $pattern_id = entity_id('game_pattern', $pattern);
  if (!empty($pattern_id) && game_access('edit', $pattern)) {
    $form['actions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
        '#submit' => array('pattern_ui_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'pattern_ui_form_validate';

  return $form;
}

/**
 *
 * @return boolean
 */
function pattern_ui_machine_name_exists() {

  return false;
}

/**
 *
 * @param type $form
 * @param type $form_state
 */
function pattern_ui_form_validate($form, &$form_state) {
  return true;
}

/**
 *
 * @param type $form
 * @param array $form_state
 */
function pattern_ui_form_submit($form, &$form_state) {
  $pattern = $form_state['pattern'];

  entity_form_submit_build_entity('pattern', $pattern, $form, $form_state);

  if (!isset($pattern->entity_id)) {
    // $pattern->entity_id = 1;
  }
  if (property_exists($pattern, "field_pattern")) {
    if (isset($pattern->field_pattern[LANGUAGE_NONE]['add_more'])) {
      unset($pattern->field_pattern[LANGUAGE_NONE]['add_more']);
    }
    foreach ($pattern->field_pattern[LANGUAGE_NONE] as $key => $value) {
      if (empty($value['value'])) {
        unset($pattern->field_pattern[LANGUAGE_NONE][$key]);
      }
    }
  }

  game_pattern_save($pattern);

  drupal_set_message(t('Game Pattern %title saved.', array('%title' => entity_label('game_pattern', $pattern))));
  $form_state['redirect'] = 'patterns';
}

/**
 *
 * @param type $form
 * @param array $form_state
 */
function pattern_ui_form_submit_delete($form, &$form_state) {
  $pattern = $form_state['pattern'];
  $game_pattern_uri = entity_uri('game_pattern', $pattern);
  $form_state['redirect'] = $game_pattern_uri['path'] . '/delete';
}

