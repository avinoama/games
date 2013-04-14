<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//dpm($game);
//dpm($game_instance);
//dpm(get_defined_vars());
?>
<div class="game">

  <div class="game-header-row game-header-row-1">
    <div class="game-header-row-middle game-title">
      <span><?php echo $game->title; ?></span>
    </div>
    <div class="game-header-row-right game-status"> <?php echo $status; ?></div>
  </div>
  <div class="game-header-row game-header-row-2">
    <div class="game-header-row-middle game-player-name"><?php echo $player_name;?></div>
    <div class="game-header-row-right game-players">Players <span id="players-count"><?php echo $num_players;?></span></div>
  </div>
  <div class="game-header-row game-header-row-3">
    <div id="game-last-notice" class="game-header-row-middle game-last-notice">&nbsp;</div>
    <div class="game-header-row-right game-notices">Notices</div>
  </div>
  <div id="game-canvas" class="game-canvas">
  </div>
  <div id="game-notice-board" class="game-notice-board"></div>
</div>