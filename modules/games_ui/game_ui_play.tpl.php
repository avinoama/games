<?php
/**
 * @file
 * template for a basic game
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 * vars
 * $game
 * $game_instance
 * 
 */

?>
<div id="<?php echo $game->machine_name?>" class="game">

  <div class="game-header-row game-header-row-1">
    <div class="game-header-row-middle game-title">
      <span><?php echo $game->title; ?></span>
    </div>
    <div class="game-header-row-right game-status"> <?php echo $status; ?></div>
  </div>
   
  <div class="game-header-row game-header-row-3">
    <div id="game-last-notice" class="game-header-row-middle game-last-notice">&nbsp;</div>
    <div class="game-header-row-right game-notices">Notices</div>
  </div>
  <div id="game-canvas" class="game-canvas">
  </div>
  <div id="game-notice-board" class="game-notice-board"></div>
</div>