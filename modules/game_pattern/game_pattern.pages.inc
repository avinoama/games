<?php

/**
 * Game view callback.
 */
function game_pattern_view($game_pattern) {
  drupal_set_title(entity_label('game_pattern', $game_pattern));
  $id = entity_id('game_pattern', $game_pattern);
  $output = entity_view('patterns', array(entity_id('game_pattern', $game_pattern) => $game_pattern), 'full');
  return $output;
}
