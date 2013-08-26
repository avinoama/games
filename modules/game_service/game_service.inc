<?php
function _game_service_retrieve($gid) {
  return game_load($gid);
}
function _game_service_index($page=null, $parameters=null) {
  $list = _list_games();
  return (object)array('games'=>$list);

}

function _game_service_create($data) {


}

function _game_service_update($id=0,$data=null) {
  return (object)array(
        'id' => $id,
  );
}
function _game_service_delete($gid) {
  //noteresource_delete_note($id);
  return (object)array(
      'id' => $id,
  );
}
function _running_game_service_index($gid=null,$page=0,$parameters=null) {
  $list = _list_running_games($gid);
  return (object)array('running_games'=>$list );
}
function _running_game_service_retrieve($id) {
  $running_game = entity_load('running_game', array($id));
  return (object)array('id'=>$id,'running_game'=>$running_game);
}
function _list_games() {
  return entity_load('game',FALSE);
}

function _list_running_games($gid) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'running_game')
          ->propertyCondition('gid', $gid)
          ->propertyOrderBy('id', 'DESC');
          //->propertyCondition('status', GAME_STATUS_NOT_STARTED);
  $running_games = array();
  $result = $query->execute();
  if (isset($result['running_game'])) {
    $ids = array_keys($result['running_game']);
    $running_games = entity_load('running_game', $ids);
  }
  
  return $running_games;
}

