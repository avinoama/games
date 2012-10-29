(function ($) {
  Drupal.behaviors.gameInstance = {
    //serverTime:'',
    attach: function (context, settings) {
      //console.log(Drupal.settings);
      //console.log(Drupal.settings.gameInstance);
      //console.log(location.pathname);
      if(Drupal.settings.gameInstance.instance.status==1) {
        //Drupal.settings.gameInstance.
        //$(".messages.status").text("Loading...");
        
        // please check if user can join game befor shwing him the join game
        // + check if user already logged in
        if(!Drupal.settings.gameInstance.player_joined_game) {
          //$(".messages.status").text("Game didont started yet. you can join game if you like to ? ");
          div = $("<div>");
          input = $("<input>").attr("id","instance_player_name");
          input2 = $("<input>").attr("type","submit").val(Drupal.t("Join"));
          input2.bind("click",function(){
            player_name = $("#instance_player_name").val();
            if(player_name.length>2) {
              //  send join game
              joinGame(player_name);
              //  wait for replay
              setTimeout(getCommands,1000);
            } else {
              alert("name need to ne longer then 2 chars"); 
            }
          });
          div.append(input);
          div.append(input2);
          
          m = new Array();
          m[0]= div;
          Drupal.behaviors.gameInstance.message(m);          
         
        //$(".messages.status").append(div);
        } else {
          if(Drupal.settings.gameInstance.num_players  >= Drupal.settings.gameInstance.game.field_min_num_players['und'][0].value) {
            div = $("<div>");
            input2 = $("<input>").attr("type","submit").val(Drupal.t("Start Game"));
            input2.bind("click",function(){
              start_game();
            });
            div.append(input2);
            $(".messages.status").append(div);
            setTimeout(getCommands,1000);
          }
        
          
        }
      } else if(Drupal.settings.gameInstance.instance.status==2) {
        //alert("game already started");
        //console.log(Drupal.settings.gameInstance);
        // $(".messages.status").text("game already started").fadeIn(5000).fadeOut(5000);
        //        setTimeout(getCommands,1000);
        getCommands();
      }
    
      

    /**
     * Init game instance
     */
    
    /**
     * show number of players in game
     */
    
    /**
     * show game status
     */
    
    
    }, // end attach
    message: function(params){
      div= $("<div/>");
      div.addClass("messages").addClass("status");
      div.append(params[0]);
      if(params[0]!=undefined && params[0]!="") {
        $("#messages .section").append(div);
      }
    },
    start_game: function() {
      alert("start_game");
      Drupal.behaviors.gameInstance.instance.status=2;
    },
    show_start_game_button: function() {
            div = $("<div>");
            input2 = $("<input>").attr("type","submit").val(Drupal.t("Start Game"));
            input2.bind("click",function(){
              start_game();
            });
            div.append(input2);
            $("#messages .section").append(div);
            setTimeout(getCommands,1000);
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
          time:Drupal.settings.gameInstance.serverTime
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
            
            Drupal.settings.gameInstance.serverTime = data[command].command_time;
            json_data = jQuery.parseJSON( data[command].command_data );
            //console.log(json_data);
            if(json_data.callback) {
              c= json_data.callback;
              Drupal.behaviors[c.module][c.fn](c.params);
            }
            m = new Array();
            m[0]= json_data.message;
            Drupal.behaviors.gameInstance.message(m);          


          }
        }
        //data.players_count;
        //data.message;
        //alert(data.message);
        
        
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
          //alert(data.message);

          m = new Array();
          m[0]= data.message;
          Drupal.behaviors.gameInstance.message(m);          

          Drupal.behaviors.gameInstance.serverTime = data.time;
        }
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });    
    
    
  }
  function start_game() {
    $.ajax({
      url: location.pathname+"/ajax",
      data: {
        action: {
          command: 'trigger',
          hook:"game_start"
        }
      }, 
      dataType :"json",
      type:"post",
      success: function(data) {
        console.log(data);
        
      //  no data sholud be returned maybe just an ok for validational resons
      /*data.message;
        $(".messages.status").text(data.message);
        Drupal.behaviors.gameInstance.serverTime = data.time;        */
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });        
    
    
  }
  
})(jQuery);
