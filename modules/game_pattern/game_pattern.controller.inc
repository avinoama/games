<?php
/**
* Task class.
*/
class GamePattern extends Entity {
  protected function defaultLabel() {
    return $this->label;
  }
  protected function defaultUri() {
    return array('path' => 'game/pattern/' . $this->identifier());
  }
}

class GamePatternController extends EntityAPIController {
  public function create(array $values = array()) {
    global $user;
    $values += array(
      'label' => '',
      'machine_name' => '',
    );
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('game_pattern', $entity);
    //$content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->id->name->value(array('sanitize' => TRUE)))));
    /*
    // Make Description and Status themed like default fields.
    $content['description'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' =>t('Description'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_description',
      '#field_type' => 'text',
      '#entity_type' => 'game_pattern',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->description)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->description))
    );
  */
    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}





/**
* Task Type class.
*/
class GamePatternType extends Entity {
  public $type;
  public $label;
  public $weight = 0;
  public function __construct($values = array()) {
    parent::__construct($values, 'game_pattern_type');
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}

class GamePatternTypeController extends EntityAPIControllerExportable {
   public function create(array $values = array()) {
    $values += array(
      'label' => '',
      'description' => '',
    );
    return parent::create($values);
  }

  /**
   * Save Task Type.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
    // Rebuild menu registry. We do not call menu_rebuild directly, but set
    // variable that indicates rebuild in the end.
    // @see _http://drupal.org/node/1399618
    variable_set('menu_rebuild_needed', TRUE);
  }
}
//    GamePatternTypeUIController
class GamePatternTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Game types.';
    return $items;
  }

}