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