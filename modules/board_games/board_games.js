(function ($) {
  Drupal.behaviors.BoardGame = {
    attach: function (context, settings) {
      field_matrix = Drupal.settings.RunningGame.instance.field_matrix;

      if(Drupal.settings.RunningGame.instance.field_board_status['und'] !=undefined) {
        status = Drupal.settings.RunningGame.instance.field_board_status['und'][0]['value'];
      }
      dimension_amount = Drupal.settings.RunningGame.game.field_board_dimension_amount['und'];
      dimensions = Drupal.settings.RunningGame.game.field_board_dimension_amount['und'].length;

      tile_type = Drupal.settings.RunningGame.game.field_tile_type['und'][0].value;

      
      
      var board,row,column;
      
      board = $("<div/>").addClass("boardInstance").attr("id","game"+Drupal.settings.RunningGame.game.gid);
      
      if($.isArray(field_matrix['und'])) {
        field_matrix = field_matrix['und'];
      }
      if (!$.isArray(field_matrix) ) {
        field_matrix=new Array();
      }
      
      var count=0;



      for(d = 1; d <= dimensions-1; d++) {
        if(dimension_amount[d] != undefined) {
          for(y = 1; y <= dimension_amount[d].value; y++) {
            for(x = 1; x <= dimension_amount[0].value; x++) {
              
              if (!$.isArray(field_matrix[count]) && !$.isPlainObject(field_matrix[count])) {
                field_matrix[count]=new Array();
              }
              a = Array("","<div/>","<input/>");
              tile = $(a[tile_type]).addClass("tile")
              .addClass("tile_"+dimensions+"d")
              .addClass("position_" + x  + "_" + y)
              .attr("id","tile_"+count);
              
              if(tile_type==1) {
                if(field_matrix[count]!=undefined && field_matrix[count].value>0) {
                  tile.addClass("owned_"+field_matrix[count].value).addClass("owned");
                  tile.text(field_matrix[count].value);
                } else {
                  tile.html("&nbsp;");
                }
                if(status=='lisiten_to_click') {
                  $(tile).bind("click",function(){
                    board_games_tile_on_click(this)
                  });
                }

              } else if (tile_type==2) {
                  
                if(field_matrix[count]!=undefined && field_matrix[count].value>0) {
                  tile.val(field_matrix[count].value);
                }
                if(status=='lisiten_to_change') {
                  $(tile).bind("keyup",function(event){
                    board_games_tile_on_key_up(this,event);
                  });
                }

              }
            
              count++;
              board.append(tile);
            }
          }
        }
      }

      //
      // console.log("count " + count);

      $("#game-canvas").html('');
      $("#game-canvas").append(board);
      _resize_canvas();
    },
    listen_to_click_event: function(params){
      $(".tile").bind("click",function(){
        board_games_tile_on_click(this)
      });
    },
    listen_to_change_event: function(params){
      $(".tile").bind("keyup",function(event){
        board_games_tile_on_key_up(this,event);
      });
    },
    board_games_tile_set_owner_action: function(params){
      $("#tile_"+params.tile_id).addClass("owned_"+params.player_turn).addClass("owned");
      $("#tile_"+params.tile_id).text(params.player_turn);
    },
    board_games_tile_increment_action: function(params){
      $("#tile_"+params.tile_id).text(params.value);
    },
    board_games_tile_decrement_action: function(params){
      $("#tile_"+params.tile_id).text(params.value);
    },
    board_game_set_matrix:function(params) {
      for(i in params.matrix) {
        for(position in params.matrix[i]) {
          _board_game_set_tile(position,params.matrix[i][position]);
        }
      }
    },
    board_game_set_tile_in_matrix:function(params) {
      _board_game_set_tile(params.tile_position, params.tile_value);
    }
  }
  function _resize_canvas() {
     dimension_amount = Drupal.settings.RunningGame.game.field_board_dimension_amount['und'];
      $('.boardInstance').width(($(".tile").width()+4)* dimension_amount[0].value);
    
  }
  function _board_game_set_tile(position,value) {
    if($("#tile_"+position).is("input")) {
      $("#tile_"+position).val(value).removeAttr('disabled');
    } else {
      $("#tile_"+position).text(value);
    }
  };
  /**
   * Listens to keyup action and sent it to server
   * 
   *
   ***/
  function board_games_tile_on_key_up(tile, event) {
    if(isNumber($(tile).val())) {
      id=$(tile).attr("id").replace("tile_","");
      val = $(tile).val();
      $(tile).attr("disabled","disabled");

      params = {
        tile_position: id,
        tile_value: val
      };

      _board_games_action_send("tile_set",params);
    } else {
      $(tile).val("");
    }
  };
  function isNumber(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
  };
  function board_games_tile_on_click(tile) {
    $(tile).addClass("clicked");
    id=$(tile).attr("id").replace("tile_","");
    setTimeout(function () {
      $(tile).removeClass("clicked");
    },1000);
    params = {
      tile_position: id
    };
    _board_games_action_send("tile_click",params);
  };
  function _board_games_action_send(hook,params) {
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
        console.log(data);
      /*for(r in data) {
          for(i in data[r])
            if(data[r][i]!=null){
              if(data[r][i].callback) {
                c= data[r][i].callback;
                Drupal.behaviors[c.module][c.fn](c.params);
              }
            }
        }*/
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });
  };

})(jQuery);