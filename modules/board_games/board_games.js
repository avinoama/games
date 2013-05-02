(function ($) {
  Drupal.behaviors.boardGame = {
    attach: function (context, settings) {
      field_matrix = Drupal.settings.RunningGame.instance.field_matrix;
      height = Drupal.settings.RunningGame.game.field_board_height['und'][0].value;
      width = Drupal.settings.RunningGame.game.field_board_width['und'][0].value;
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
      for(i=0;i<height;i++) {
        //row = $("<div/>").addClass("row");
        
        if (!$.isArray(field_matrix[i]) && !$.isPlainObject(field_matrix[i])) {
          field_matrix[i]=new Array();
        }
        for(j=0;j<width;j++) {
          a = Array("","<div/>","<input/>");
          tile = $(a[tile_type]).addClass("tile").attr("id","tile_"+count);
          if(tile_type==1) {
            
            if(field_matrix[count]!=undefined && field_matrix[count].value>0) {
              tile.addClass("owned_"+field_matrix[count].value).addClass("owned");
              tile.text(field_matrix[count].value);
            } else {
              tile.html("&nbsp;");
            }
          }else if(tile_type==2) {
            
            if(field_matrix[count]!=undefined && field_matrix[count].value>0) {
              tile.val(field_matrix[count].value);
            }

          }
          count++;
          board.append(tile);
        }
      }
      $("#game-canvas").html('');
      $("#game-canvas").append(board);
    },
    board_games_listen_to_click_event: function(params){
      $(".tile").bind("click",function(){
        board_games_tile_on_click(this)
      });
    },
    board_games_listen_to_input_changed_event: function(params){
      $(".tile").bind("keyup",function(event){
        board_games_tile_on_key_up(this,event);
      });
    },
    board_games_tile_set_owner_action: function(params){
      $("#tile_"+params.tile_id).addClass("owned_"+params.participant_turn).addClass("owned");
      $("#tile_"+params.tile_id).text(params.participant_turn);
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
      _board_game_set_tile(params.tile_position,params.tile_value);
    }
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
      //  console.log(data);
      /*
        for(r in data) {
          //console.log(data[r])
          for(i in data[r])
            if(data[r][i]!=null){
              if(data[r][i].callback) {
                c= data[r][i].callback;
                Drupal.behaviors[c.module][c.fn](c.params);
              }
            }
        }
        */
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });
  };

})(jQuery);