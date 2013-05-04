<?php
class RunningGamePlayerController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    drupal_session_start();

    $values += array(
        'player_session' => session_id(),
        'player_name' => "",
        'joined' => REQUEST_TIME,
        'alive' => REQUEST_TIME,
    );
    return parent::create($values);
  }

}

/**
 * RunningGame class.
 */
class RunningGamePlayer extends Entity {

  protected function defaultLabel() {
    return $this->player_session;
  }

  protected function defaultUri() {
    return ""; //array('path' => 'play/' . $this->identifier());
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }

}