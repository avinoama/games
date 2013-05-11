<?php

function piece_type_form($form, &$form_state, $piece_type, $op = 'edit') {

  if ($op == 'clone') {
    $piece_type->label .= ' (cloned)';
    $piece_type->type = '';
  }

  $form['symbol'] = array(
      '#title' => t('Symbol'),
      '#type' => 'textfield',
      '#default_value' => $piece_type->symbol,
      '#description' => t('The uniqu char of this piece type.'),
      '#required' => TRUE,
      '#size' => 30,
  );

  $form['label'] = array(
      '#title' => t('Label'),
      '#type' => 'textfield',
      '#default_value' => $piece_type->label,
      '#description' => t('The human-readable name of this piece type.'),
      '#required' => TRUE,
      '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
      '#type' => 'machine_name',
      '#default_value' => isset($piece_type->type) ? $piece_type->type : '',
      '#maxlength' => 32,
      '#disabled' => $piece_type->isLocked() && $op != 'clone',
      '#machine_name' => array(
          'exists' => 'piece_types',
          'source' => array('label'),
      ),
      '#description' => t('A unique machine-readable name for this piece type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
      '#type' => 'textarea',
      '#default_value' => isset($piece_type->description) ? $piece_type->description : '',
      '#description' => t('Description about the piece type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save piece type'),
      '#weight' => 40,
  );

  if (!$piece_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete piece type'),
        '#weight' => 45,
        '#limit_validation_errors' => array(),
        '#submit' => array('piece_type_form_submit_delete')
    );
  }
  return $form;

  
}


/**
 * Submit handler for creating/editing piece_type.
 */
function piece_type_form_submit(&$form, &$form_state) {
  $piece_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  piece_type_save($piece_type);

  // Redirect user back to list of piece types.
  $form_state['redirect'] = 'admin/structure/piece-types';
}

function piece_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/piece-types/' . $form_state['piece_type']->type . '/delete';
}

/**
 * piece type delete form.
 */
function piece_type_form_delete_confirm($form, &$form_state, $piece_type) {
  $form_state['piece_type'] = $piece_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['piece_type_id'] = array('#type' => 'value', '#value' => entity_id('piece_type', $piece_type));
  return confirm_form($form, t('Are you sure you want to delete piece type %title?', array('%title' => entity_label('piece_type', $piece_type))), 'piece/' . entity_id('piece_type', $piece_type), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * piece type delete form submit handler.
 */
function piece_type_form_delete_confirm_submit($form, &$form_state) {
  $piece_type = $form_state['piece_type'];

  piece_type_delete($piece_type);

  watchdog('piece_type', '@type: deleted %title.', array('@type' => $piece_type->type, '%title' => $piece_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $piece_type->type, '%title' => $piece_type->label)));

  $form_state['redirect'] = 'admin/structure/piece-types';
}


/**
 * Form function for the rules link components.
 */
function piece_type_component_form($form, $form_state, $entity_type, $piece_type) {
  $form = array();
  $form_state['piece_type'] = $piece_type;

  $condition = piece_type_load_condition_set($piece_type);
  $condition->form($form['condition_set'], $form_state);

  $form['condition_set']['elements']['#caption'] = '';
  $form['condition_set']['help']['#title'] = t('Movment conditions');
  $form['condition_set']['help']['#type'] = 'item';
  //$form['condition_set']['help']['#markup'] = t('The access conditions can additionally to <a href="!url">%link</a> specify, when to show the rules links.', array('%link' => t('the permissions'), '!url' => url('admin/people/permissions', array('fragment' => 'module-piece_type'))));


  // Since we never want to negate the result, we can hide the form.
  unset($form['condition_set']['negate']);
  $form['condition_set']['#tree'] = TRUE;

/*
  $rule_set = piece_type_load_rules_set($piece_type);
  $rule_set->form($form['rule_set'], $form_state, array('show settings' => TRUE));

  $form['rule_set']['elements']['#caption'] = '';
  $form['rule_set']['#tree'] = TRUE;

  $form['rule_set']['help']['#title'] = t('Reactions');
  $form['rule_set']['help']['#type'] = 'item';
  $form['rule_set']['help']['#markup'] = t('To output a system message, simply use the "Show a message on the site" action in one of your rules. Javascript links will replace the link with the text from the system message.');


  $form['rule_set']['settings']['vars']['#description'] .= '<br/>' . t('Please also note that Rules Link only checks if there are enough variables available, but not if the entities could be loaded. You will have to check that your self in your components.');
  $form['rule_set']['settings']['label']['#access'] = FALSE;
  $form['rule_set']['settings']['name']['#type'] = 'value';
  $form['rule_set']['settings']['tags']['#access'] = FALSE;
  $form['rule_set']['settings']['vars']['items'][$piece_type->entity_type]['#disabled'] = TRUE;
*/
  $form_state['piece_type_condition_set'] = $condition;
  //$form_state['piece_type_rules_set'] = $rule_set;


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Rules Link'),
    '#weight' => 40,
  );
  return $form;
}

function piece_type_component_form_validate(&$form, &$form_state) {
  $form_state['piece_type_condition_set']->form_validate($form['condition_set'], $form_state);
  $form_state['piece_type_rules_set']->form_validate($form['rule_set'], $form_state);
}

/**
 * Form API submit callback for the type form.
 */
function piece_type_component_form_submit(&$form, &$form_state) {
  $rules_set_vars = $form_state['piece_type_rules_set']->componentVariables();
  $form_state['piece_type_rules_set']->form_submit($form['rule_set'], $form_state);

  $condition_vars = &$form_state['piece_type_condition_set']->componentVariables();
  foreach ($condition_vars as $key => $value) {
    unset($condition_vars[$key]);
  }
  foreach ($rules_set_vars as $key => $value) {
    $condition_vars[$key] = $value;
  }
  $form_state['piece_type_condition_set']->form_submit($form['condition_set'], $form_state);

  // If the rule is renamed, rename also the rules set.
  if ($form_state['piece_type_condition_set']->name != piece_type_get_condition_set_name($form_state['piece_type'])) {
    $form_state['piece_type_condition_set']->label = 'Rules link: ' . $form_state['piece_type']->label . ' condition';
    $form_state['piece_type_condition_set']->save(piece_type_get_condition_set_name($form_state['piece_type']), 'piece_type');
  }

  // If the rule is renamed, rename also the rules set.
  if ($form_state['piece_type_rules_set']->name != piece_type_get_rules_set_name($form_state['piece_type'])) {
    $form_state['piece_type_rules_set']->label = 'Rules link: ' . $form_state['piece_type']->label . ' rules set';
    $form_state['piece_type_rules_set']->save(piece_type_get_rules_set_name($form_state['piece_type']), 'piece_type');
  }

  // If an additional variable was added, then disable 'show link in entity'.
  if (count($rules_set_vars) > 1) {
    $form_state['piece_type']->settings['entity_link'] = FALSE;
    $form_state['piece_type']->save();
  }

  drupal_set_message(t('Your Rules Link components has been saved.'));
}