(function ($) {
  
  Drupal.behaviors.gameInstance = {
    attach: function (context, settings) {
      // set default id to 0 
      Drupal.settings.gameInstance.clientId = 0;
      $("#messages").css("overflow","auto");
      $("#messages").css("height","100px");
      //  game didnot start yet
      if(Drupal.settings.gameInstance.instance.status==1) {        
        if(!Drupal.settings.gameInstance.player_joined_game) {
          m = new Array('trying to join game...');
          Drupal.behaviors.gameInstance.message(m);    
          joinGame("");
        } else {
          if(Drupal.settings.gameInstance.num_players  >= Drupal.settings.gameInstance.game.field_min_num_players['und'][0].value) {
            this.show_start_game_button();
          }
        }
      //  game started
      } else if ( Drupal.settings.gameInstance.instance.status==2 ) {
            
        if(Drupal.settings.gameInstance.player_joined_game) {
              
        } else {
          m = new Array();
          m[0]= "game already started, and your not in it.";
          Drupal.behaviors.gameInstance.message(m);
        }
      // game ended
      } else if ( Drupal.settings.gameInstance.instance.status==2 ) {
        m = new Array();
        m[0]= "game already ended";
        Drupal.behaviors.gameInstance.message(m);
      }
      //alert();
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
      div= $("<div/>");
      div.addClass("messages").addClass("status");
      div.append(params[0]);
      if(params[0]!=undefined && params[0]!="") {
        $("#messages .section").append(div);
        $("#messages").animate({
          scrollTop: div.offset().top
        });
      }
      
    },
    start_game: function() {
      //alert("start_game");
      Drupal.behaviors.gameInstance.instance.status=2;
    },
    show_start_game_button: function() {
      div = $("<div>");
      div.addClass("messages").addClass("status");
      input2 = $("<input>").attr("type","submit").val(Drupal.t("Start Game"));
      input2.bind("click",function(){
        start_game();
      });
      div.append(input2);
      $("#messages .section").append(div);
    }
  }
  
  function getCommands(){
    //console.log("check gor updates");
    //console.log("getCommands "+Drupal.settings.gameInstance.serverTime);
    $.ajax({
      url: location.pathname+"/ajax",
      data: {
        action: {
          command: 'command',
          time:Drupal.settings.gameInstance.serverTime,
          id:Drupal.settings.gameInstance.clientId
        }
      }, 
      dataType :"json",
      type:"post",
      success: function(data) {
        //console.log(data);
        if(data.length<1) {
        // no data 
          
        } else {
          for(command in data) {
            // need to process incoming command
            
            //  Notice only update client time on command Update
            Drupal.settings.gameInstance.serverTime = data[command].command_time;
            Drupal.settings.gameInstance.clientId = data[command].id;
            console.log("command id " + data[command].id)
            json_data = jQuery.parseJSON( data[command].command_data );
            //console.log(json_data);
            if(json_data.callback) {
              console.log(json_data.callback);
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
            m = new Array();
            m[0]= json_data.message;
            Drupal.behaviors.gameInstance.message(m);
          }
        }
        
        
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
        
        console.log(data);
        if(data!=null) {
          data.message;
          m = new Array();
          m[0]= data.message;
          Drupal.behaviors.gameInstance.message(m);
        }
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
      //alert("start gae has been pressed");
      //  no data sholud be returned maybe just an ok for validational resons
      //  somthing like game will start shortly
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });
  }
  
})(jQuery);
