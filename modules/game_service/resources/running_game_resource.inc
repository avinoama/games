<?php
function _running_game_resource_trigger($id=0) {
  $running_game = current(entity_load("running_game",FALSE,array('id'=>$id)));
  
  return (object)array("ok"=>'22','id'=>$running_game);
}