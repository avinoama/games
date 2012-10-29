<?php
/**
 * @file
 * Hooks provided by this module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Acts on game being loaded from the database.
 *
 * This hook is invoked during $game loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $game entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
 /*
function hook_game_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {game} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}
*/
/**
 * Responds when a $game is inserted.
 *
 * This hook is invoked after the $game is inserted into the database.
 *
 * @param ExampleTask $game
 *   The $game that is being inserted.
 *
 * @see hook_entity_insert()
 */
 /*
function hook_game_insert(Game $game) {
  db_insert('game')
    ->fields(array(
      'id' => entity_id('game', $game),
      'extra' => print_r($game, TRUE),
    ))
    ->execute();
}
*/
/**
 * Acts on a $game being inserted or updated.
 *
 * This hook is invoked before the $game is saved to the database.
 *
 * @param Game $game
 *   The $game that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
 /*
function hook_game_presave(Game $game) {
  $game->name = 'foo';
}
*/
/**
 * Responds to a $game being updated.
 *
 * This hook is invoked after the $game has been updated in the database.
 *
 * @param ExampleTask $game
 *   The $game that is being updated.
 *
 * @see hook_entity_update()
 */
 /*
function hook_game_update(Game $game) {
  db_update('game')
    ->fields(array('extra' => print_r($game, TRUE)))
    ->condition('id', entity_id('game', $game))
    ->execute();
}
*/
/**
 * Responds to $game deletion.
 *
 * This hook is invoked after the $game has been removed from the database.
 *
 * @param Game $game
 *   The $game that is being deleted.
 *
 * @see hook_entity_delete()
 */
 /*
function hook_game_delete(Game $game) {
  db_delete('game')
    ->condition('gid', entity_id('game', $game))
    ->execute();
}
*/
/**
 * Act on a game that is being assembled before rendering.
 *
 * @param $game
 *   The game entity.
 * @param $view_mode
 *   The view mode the game is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $game->content prior to rendering. The
 * structure of $game->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
 /*
function hook_game_view($game, $view_mode, $langcode) {
  $game->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}
*/
/**
 * Alter the results of entity_view() for games.
 *
 * @param $build
 *   A renderable array representing the game content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * game content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the game rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_game().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
 /*
function hook_game_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}
*/
/**
 * Acts on game_type being loaded from the database.
 *
 * This hook is invoked during game_type loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of game_type entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
 /*
function hook_game_type_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {game} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}
*/
/**
 * Responds when a game_type is inserted.
 *
 * This hook is invoked after the game_type is inserted into the database.
 *
 * @param ExampleTaskType $game_type
 *   The game_type that is being inserted.
 *
 * @see hook_entity_insert()
 */
 /*
function hook_game_type_insert(GameType $game_type) {
  db_insert('game')
    ->fields(array(
      'id' => entity_id('game_type', $game_type),
      'extra' => print_r($game_type, TRUE),
    ))
    ->execute();
}
*/
/**
 * Acts on a game_type being inserted or updated.
 *
 * This hook is invoked before the game_type is saved to the database.
 *
 * @param ExampleTaskType $game_type
 *   The game_type that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
 /*
function hook_game_type_presave(GameType $game_type) {
  $game_type->name = 'foo';
}
*/
/**
 * Responds to a game_type being updated.
 *
 * This hook is invoked after the game_type has been updated in the database.
 *
 * @param ExampleTaskType $game_type
 *   The game_type that is being updated.
 *
 * @see hook_entity_update()
 */
 /*
function hook_game_type_update(GameType $game_type) {
  db_update('game')
    ->fields(array('extra' => print_r($game_type, TRUE)))
    ->condition('id', entity_id('game_type', $game_type))
    ->execute();
}
*/
/**
 * Responds to game_type deletion.
 *
 * This hook is invoked after the game_type has been removed from the database.
 *
 * @param ExampleTaskType $game_type
 *   The game_type that is being deleted.
 *
 * @see hook_entity_delete()
 */
 /*
function hook_game_type_delete(GameType $game_type) {
  db_delete('game')
    ->condition('pid', entity_id('game_type', $game_type))
    ->execute();
}
*/
/**
 * Define default game_type configurations.
 *
 * @return
 *   An array of default game_type, keyed by machine names.
 *
 * @see hook_default_game_type_alter()
 */
 /*
function hook_default_game_type() {
  $defaults['main'] = entity_create('game_type', array(

  ));
  return $defaults;
}
*/
/**
 * Alter default game_type configurations.
 *
 * @param array $defaults
 *   An array of default game_type, keyed by machine names.
 *
 * @see hook_default_game_type()
 */
 /*
function hook_default_game_type_alter(array &$defaults) {
  $defaults['main']->name = 'custom name';
}*/