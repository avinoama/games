(function ($) {
  Drupal.behaviors.RunningGame = {
    attach: function (context, settings) {
      // set default id to 0
      Drupal.settings.RunningGame.clientId = 0;
      Drupal.settings.RunningGame.messages=Array();
      //  Show Game Status
      setTimeout(getCommands,1000);

    }, // end attach
    message: function(params){
      for(i in params) {
        if(params[i]!=undefined && params[i]!="") {
          Drupal.settings.RunningGame.messages.push(params[i]);
        }
      }
      _recursive_handle_messages(); 
      
    },
    start_game: function() {
      $(".start-game").fadeOut(500);
      Drupal.settings.RunningGame.instance.status=2;
    },
    game_ended: function() {
      
    //console.log(Drupal.behaviors.RunningGame);
    //Drupal.behaviors.RunningGame.instance.status=3;
    //m = new Array();
    //m[0]= "game over";
    //this.message(m);
      
    },
    show_start_game_button: function() {
      div = $("<div>");
      div.addClass("start-game");
      input2 = $("<input>").attr("type","submit").val(Drupal.t("Start Game"));
      input2.bind("click",function(){
        _start_game();
      });
      div.append(input2);
      $("#game-canvas").append(div);
    },
    trigger_rule : function (hook, params) {
      $.ajax({
        url: location.pathname+"/ajax",
        data: {
          action: {
            command: 'trigger',
            hook:hook,
            params: params,
            game : {
              session: Drupal.settings.RunningGame.instance.session
            }

          }
        },
        dataType :"json",
        type:"post",
        success: function(data) {
          Drupal.behaviors.RunningGame.handle_response(data);
        },
        error: function(jqXHR, textStatus, errorThrow) {
          console.log(jqXHR+ " " + textStatus + " " +errorThrow );
        }
      });
    },
    handle_response :  function (data){
      if(data.length<1) {
        // no data
        return;
      }
      for(command in data) {
        // need to process incoming command
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
        if(json_data.callbacks) {
          for(c in json_data.callbacks) {
            if(Drupal.behaviors[json_data.callbacks[c].module]!=null) {
              if(Drupal.behaviors[json_data.callbacks[c].module][json_data.callbacks[c].fn]!=null) {
                Drupal.behaviors[json_data.callbacks[c].module][json_data.callbacks[c].fn](json_data.callbacks[c].params);
              } else {
                console.log("function name undefine "+json_data.callbacks[c].fn );
              }
            } else {
              console.log("module name undefine "+json_data.callbacks[c].module );
            }
          }
        }
      }
    }
  }
  
  function getCommands(){
    $.ajax({
      url: location.pathname+'/ajax',
      data: {
        action: {
          command: 'command',
          time:Drupal.settings.RunningGame.serverTime,
          id:Drupal.settings.RunningGame.clientId
        }
      },
      dataType :'json',
      type:'post',
      success: function(data) {
        Drupal.behaviors.RunningGame.handle_response(data);
        setTimeout(getCommands,4000);
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });
  }
  
  function _start_game() {
    hook = 'game_start';
    params = {};
    Drupal.behaviors.RunningGame.trigger_rule(hook, params);
  }
  function _recursive_handle_messages() {
    if(Drupal.settings.RunningGame.messages.length>0) {
      param = Drupal.settings.RunningGame.messages.pop();
      $("#game-last-notice").text(param);
      setTimeout('_recursive_handle_messages()',4000);
    }
  }
})(jQuery);
