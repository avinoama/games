(function ($) {
 
  Drupal.behaviors.boardGame = {
    attach: function (context, settings) {
    
      //console.log(Drupal.settings.gameInstance);
      field_matrix = Drupal.settings.gameInstance.instance.field_matrix;
      
      height = Drupal.settings.gameInstance.game.field_board_height['und'][0].value;
      width = Drupal.settings.gameInstance.game.field_board_width['und'][0].value;
      /*
      height = Drupal.settings.gameInstance.game.field_board_height['und'][0].value;
      width = Drupal.settings.gameInstance.game.field_board_width['und'][0].value;
      */
      var board,row,column;
      
      board = $("<div/>").addClass("boardInstance").attr("id","game"+Drupal.settings.gameInstance.game.gid);
      if($.isArray(field_matrix['und'])) {
        field_matrix = field_matrix['und'];
      }
      //console.log(field_matrix);  
      if (!$.isArray(field_matrix) ) {
        field_matrix=new Array();
      }
      var count=0;
      for(i=0;i<height;i++) {
        row = $("<div/>").addClass("row");
        
        if (!$.isArray(field_matrix[i]) && !$.isPlainObject(field_matrix[i])) {
          field_matrix[i]=new Array();
        }
        for(j=0;j<width;j++) {
          
          column = $("<div/>").addClass("column").attr("id","tile_"+count);
          if(field_matrix[count]!=undefined) {
            if(field_matrix[count].safe_value>0) {
              column.addClass("owned_"+field_matrix[count].safe_value).addClass("owned");
              column.text(field_matrix[count].safe_value);
            }
          }
          
          count++;
          column.bind("click",function(){
            board_games_tile_on_click(this)
          });
          //column.html("&nbsp;");
          row.append(column);
        }
        board.append(row);
      }
      $("#content").html('');
      $("#content").append(board);			
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
    }	
  }
  
  function init(game) {
    alert("init board game");  
  }	
  
  function board_games_tile_on_click(tile) {
    $(tile).addClass("clicked");
    id=$(tile).attr("id").replace("tile_","");
    setTimeout(function () {
      $(tile).removeClass("clicked");
    },1000);
    $.ajax({
      url: location.pathname+"/ajax",
      data: {
        action: {
          command: 'trigger',
          hook:"tile_click",
          params: {
            tile_position: id,
            session: Drupal.settings.gameInstance.instance.session
          }
        }
      }, 
      dataType :"json",
      type:"post",
      success: function(data) {
        //console.log(data);
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

  }

})(jQuery);