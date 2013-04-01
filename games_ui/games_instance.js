(function ($) {
  
  Drupal.behaviors.RunningGame = {
    attach: function (context, settings) {
      // set default id to 0
      console.log(Drupal.settings.RunningGame);
      Drupal.settings.RunningGame.clientId = 0;
      // $("#messages").css("overflow","auto");
      // $("#messages").css("height","100px");
      
      
      //  Show Game Status
      
      //  IF game didnot start yet
      if(Drupal.settings.RunningGame.instance.status==1) {
        if(!Drupal.settings.RunningGame.player_joined_game) {
          m = new Array('trying to join game...');
          Drupal.behaviors.RunningGame.message(m);
          joinGame("");
        } else {
          if(Drupal.settings.RunningGame.num_players  >= Drupal.settings.RunningGame.game.field_min_num_players['und'][0].value) {
            this.show_start_game_button();
          }
        }
      //  ELSE IF game started
      } else if ( Drupal.settings.RunningGame.instance.status==2 ) {
        //alert(Drupal.settings.RunningGame.player_joined_game);
        //console.log(Drupal.settings.RunningGame);
        if(Drupal.settings.RunningGame.player_joined_game) {
              
        } else {
          m = new Array();
          m[0]= "game already started, and your not in it.";
          Drupal.behaviors.RunningGame.message(m);
        }
      // ELSE IF game ended
      } else if ( Drupal.settings.RunningGame.instance.status==2 ) {
        m = new Array();
        m[0]= "game already ended";
        Drupal.behaviors.RunningGame.message(m);
      }
      
      setTimeout(getCommands,1000);

    /**
     * show number of players in game
     */
    
    /**
     * show game status
     */
    
    /**
     * show current player name
     */
    
    }, // end attach
    message: function(params){
      for(i in params) {
        if(params[i]!=undefined && params[i]!="") {
          $("#game-last-notice").text(params[i]);
        }
      }
      
    },
    start_game: function() {
      //console.log("game started");
       $(".start-game").fadeOut(500);
      //Drupal.settings.RunningGame.instance.status=2;
      
    },
    game_ended: function() {
      //console.log(Drupal.behaviors.RunningGame);
      //Drupal.behaviors.RunningGame.instance.status=3;
      alert("game over");
      
    },
    set_players_count: function($count) {
      $("#players-count").text($count);
      
    },
    show_start_game_button: function() {
      div = $("<div>");
      div.addClass("start-game");
      input2 = $("<input>").attr("type","submit").val(Drupal.t("Start Game"));
      input2.bind("click",function(){
        start_game();
      });
      div.append(input2);
      $("#game-canvas").append(div);
    },
    set_player_name: function ($name) {

      $(".game-player-name").text($name);
      
    }
  }
  
  function getCommands(){
    //console.log("check gor updates");
    //console.log("getCommands "+Drupal.settings.RunningGame.serverTime);
    $.ajax({
      url: location.pathname+"/ajax",
      data: {
        action: {
          command: 'command',
          time:Drupal.settings.RunningGame.serverTime,
          id:Drupal.settings.RunningGame.clientId
        }
      }, 
      dataType :"json",
      type:"post",
      success: function(data) {
        handle_response(data);
        setTimeout(getCommands,4000);
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });    
  }
  
  function joinGame(player_name) {
    
    $.ajax({
      url: location.pathname+"/ajax",
      data: {
        action: {
          command: 'join',
          player_name:player_name
        }
      }, 
      dataType :"json",
      type:"post",
      success: function(data) {
        handle_response(data);
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });    
    
    
  }
  function start_game() {
    data = {
      action: {
        command: 'trigger',
        hook:"game_start"
      }
    };
    $.ajax({
      url: location.pathname+"/ajax",
      data: data, 
      dataType :"json",
      type:"post",
      success: function(data) {
        console.log(data);
        
        handle_response(data);
      //alert("start game has been pressed");
      //  no data sholud be returned maybe just an ok for validational resons
      //  somthing like game will start shortly
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });
  }
  function handle_response(data){
    if(data.length<1) {
      // no data
      return;
    }
    for(command in data) {
      // need to process incoming command
      //console.log(data[command]);
      
      //  Notice only update client time on command Update
      if(data[command].command_time!=undefined) {
        Drupal.settings.RunningGame.serverTime = data[command].command_time;
      }
      if(data[command].id!=undefined) {
        Drupal.settings.RunningGame.clientId = data[command].id;
      }
      // check if this is already an object or needs to be converted to an object
      if(!$.isPlainObject(data[command].command_data)) {
        json_data = jQuery.parseJSON( data[command].command_data );
      } else {
        json_data = data[command].command_data;
      }
      if(json_data==null) {
        return;
      }
      if(json_data.callback) {
        //console.log(json_data.callback);
        c= json_data.callback;
        if(Drupal.behaviors[c.module]!=null) {
          if(Drupal.behaviors[c.module][c.fn]!=null) {
            Drupal.behaviors[c.module][c.fn](c.params);
          } else {
            console.log("function name undefine "+c.fn );
          }
        } else {
          console.log("module name undefine "+c.module );
        }
      }
      // TODO : put this in a callback command on all modules
      m = new Array();
      m[0]= json_data.message;
      Drupal.behaviors.RunningGame.message(m);
    }
  }
})(jQuery);
