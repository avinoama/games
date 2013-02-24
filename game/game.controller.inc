<?php

class GameController extends EntityAPIController {

  public function create(array $values = array()) {
    //print_r(date("Y-m-d H:i:s",REQUEST_TIME));
    global $user;
    $values += array(
      'title' => '',
      'description' => '',
      //'created' => date("Y-m-d H:i:s",REQUEST_TIME),
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
      'uid' => $user->uid,
    );
    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('game', $entity);
    $content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));

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
      '#entity_type' => 'game',
      '#bundle' => $entity->type,
      '#items' => array(array('value' => $entity->description)),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->description))
    );

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}

class GameInstanceController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    
    $values += array(
      'session'=>md5(time()+""+$user->uid+session_id()),
      'created' => REQUEST_TIME,
      'participant_turn' =>1,
      'started'=>REQUEST_TIME,
      'uid' => $user->uid,
    );
    return parent::create($values);
  }
}
class GameInstanceParticipantController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    drupal_session_start();
    
    $values += array(
      'participant_session' => session_id(),
      'participant_name' => "",
      'joined' => REQUEST_TIME,
      'alive' =>  REQUEST_TIME,
    );
    return parent::create($values);
  }
}
class GameInstanceCommandController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    drupal_session_start();
    
    $values += array(
      'participant_session' => session_id(),
      'command_time' => REQUEST_TIME,
    );
    return parent::create($values);
  }
}
 class GameTypeController extends EntityAPIControllerExportable {
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
    variable_set('menu_rebuild_needed', TRUE);
  }
}









/**
 * UI controller for Game Instance.
 */
class GameInstanceUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Game Instances.';
    return $items;
  }
}

/**
 * UI controller for Game Type.
 */
class GameTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage Game types.';
    return $items;
  }
}


/**
 * Game class.
 */
class Game extends Entity {
  protected function defaultLabel() {
    return $this->title;
  }

  protected function defaultUri() {
    return array('path' => 'game/' . $this->identifier());
  }
}

/**
 * GameInstance class.
 */
class GameInstance extends Entity {
  protected function defaultLabel() {
    return $this->session;
  }

  protected function defaultUri() {
    return array('path' => 'play/' . $this->identifier());
  }
  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}

/**
 * GameInstance class.
 */
class GameInstanceParticipant extends Entity {
  protected function defaultLabel() {
    return $this->participant_session;
  }

  protected function defaultUri() {
    return "";//array('path' => 'play/' . $this->identifier());
  }
  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}
/**
 * GameInstance class.
 */
class GameInstanceCommand extends Entity {
  
  protected function defaultLabel() {
    return $this->participant_session;
  }

  protected function defaultUri() {
    return "";//array('path' => 'play/' . $this->identifier());
  }
  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}

/**
 * Game Type class.
 */
class GameType extends Entity {
  public $type;
  public $label;
  public $weight = 0;

  public function __construct($values = array()) {
    parent::__construct($values, 'game_type');
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }
}










