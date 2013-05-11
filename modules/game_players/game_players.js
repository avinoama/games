(function ($) {
  Drupal.behaviors.GamePlayers = {
    attach: function (context, settings) {
      

      player_joined = Drupal.settings.GamePlayers.player_joined_game;
      player_name = Drupal.settings.GamePlayers.player_name;

      build_player_title_header ();
      
      this.set_player_name(player_name);
      this.set_players_count(Drupal.settings.GamePlayers.num_players);
      
      
      //  if game didnot start yet
      if(Drupal.settings.RunningGame.instance.status==1 && !player_joined) {
        if(!Drupal.settings.RunningGame.player_joined_game) {
          m = new Array('trying to join game...');
          Drupal.behaviors.RunningGame.message(m);
          this.joinGame("");
        }
      //  ELSE IF game started
      } else if ( Drupal.settings.RunningGame.instance.status==2 ) {
        
        if(!Drupal.settings.GamePlayers.player_joined_game) {
          m = new Array();
          m[0]= "game already started, and your not in it.";
          Drupal.behaviors.RunningGame.message(m);
        } else {
          this.set_player_name(Drupal.settings.GamePlayers.player_name);
        }
      // ELSE IF game ended
      } else if ( Drupal.settings.RunningGame.instance.status==2 ) {
        m = new Array();
        m[0]= "game already ended";
        Drupal.behaviors.RunningGame.message(m);
      }

    },
    joinGame : function (player_name) {
      hook="game_join";
      params = {
        player_name:player_name
      };
      Drupal.behaviors.RunningGame.trigger_rule(hook, params);

    },
    set_player_name: function ($name) {
      $(".game-player-name").text($name);
    },
    set_players_count: function($count) {
      $("#players-count").text($count);
    }

  }
  function build_player_title_header () {
    header = $('<div class="game-header-row game-header-row-2"><div class="game-header-row-middle game-player-name"></div><div class="game-header-row-right game-players">Players <span id="players-count"></span></div></div>');
    $(".game-header-row-1").after(header);
  }
})(jQuery);