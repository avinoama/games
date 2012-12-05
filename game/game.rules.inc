<?php

function game_rules_event_info() {
  
  $items = array(
      'game_create_instance' => array(
          'label' => t('After Instance is created'),
          'group' => t('Game Rules'),
          'variables' => rules_events_node_variables(t('created content')),
      ),
      'game_start' => array(
          'label' => t('After game start'),
          'group' => t('Game Rules'),
          'variables' => rules_events_node_variables(t('updated content'), TRUE),
      ),
      'game_end' => array(
          'label' => t('After game ends'),
          'group' => t('Game Rules'),
          'variables' => rules_events_node_variables(t('saved content'), TRUE),
      ),
  );

  return $items;
}


function _rules_game_select_info() {
  
  
  return array(
      'type' => array(
          'type' => 'text',
          'label' => t('The category to which this message belongs'),
      ),
  );
}