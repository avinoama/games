<?php

function game_participants_event_info() {

  $items = array(
      'game_join' => array(
          'label' => t('Game Join'),
          'group' => t('Game Rules'),
          'variables' => array(
              'running_game' => array(
                  'type' => 'running_game',
                  'label' => t('Running Game'),
              ),
          ),
      ),
  );

  return $items;
}