<?php

/**
 * Pieces type view callback.
 */
function piece_type_view($piece) {

  drupal_set_title(entity_label('piece', $piece));
  $id = entity_id('piece', $piece);
  $output = entity_view('piece', array(entity_id('piece', $piece) => $piece), 'full');
  return $output;
}