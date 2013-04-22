<?php
/**
 * Controllers
 */
class PieceController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    $values += array(
      'label' => '',
      'uid' => null,//$user->uid
    );
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('piece', $entity);

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}
class PieceTypeController extends EntityAPIControllerExportable {
   public function create(array $values = array()) {
    $values += array(
      'label' => '',
      'description' => '',
    );
    return parent::create($values);
  }

  /**
   * Save Game Type.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
    // Rebuild menu registry. We do not call menu_rebuild directly, but set
    // variable that indicates rebuild in the end.
    // @see http://drupal.org/node/1399618
    // variable_set('menu_rebuild_needed', TRUE);
  }
}
/**
 * UI Controllers
 */
/**
 * UI controller for Game Type.
 */
class PieceTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage piece types.';
    return $items;
  }
}

/**
 * Classes
 */
/**
 * piece class.
 */
class Piece extends Entity {
  protected function defaultLabel() {
    return $this->label;
  }
  protected function defaultUri() {
    return array('path' => 'piece/' . $this->identifier());
  }
}
/**
 * piece Type class.
 */
class PieceType extends Entity {
  public $type;
  public $label;
  public $weight = 0;

  public function __construct($values = array()) {
    parent::__construct($values, 'piece_type');
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}