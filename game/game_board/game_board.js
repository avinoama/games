(function ($) {
 
  Drupal.behaviors.boardGame = {
    attach: function (context, settings) {
      
    
      field_matrix = Drupal.settings.gameInstance.instance.field_matrix;
      height = Drupal.settings.gameInstance.game.field_board_height['und'][0].value;
      width = Drupal.settings.gameInstance.game.field_board_width['und'][0].value;
    
      var board,row,column;
    
      board = $("<div/>").addClass("boardInstance");
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
          //console.log(field_matrix[i]);
          //alert(field_matrix[count].safe_value);
          //alert(count);
          //field_matrix[i+j]=;
          
          column = $("<div/>").addClass("column").attr("id","tile_"+count);
          if(field_matrix[count]!=undefined) {
            if(field_matrix[count].safe_value>0) {
              column.addClass("owned_"+field_matrix[count].safe_value);
            }
          }
          
          count++;
          column.bind("click",function(){
            game_board_tile_on_click(this)
          });
          column.html("&nbsp;");
          row.append(column);
        }
        board.append(row);
      }
      $("#content").html('');
      $("#content").append(board);			
    },
    game_board_tile_set_owner_action: function(params){
      $("#tile_"+params.tile_id).addClass("owned_"+params.participant_turn);
    }
	
  }
  
  function init(game) {
    alert("init board game");  
  }	
  
  function game_board_tile_on_click(tile) {
    
    id=$(tile).attr("id").replace("tile_","");
    
    $.ajax({
      url: location.pathname+"/ajax",
      data: {
        action: {
          command: 'trigger',
          hook:"tile_click",
          params: id
        }
      }, 
      dataType :"json",
      type:"post",
      success: function(data) {
        console.log(data);
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
      },
      error: function(jqXHR, textStatus, errorThrow) {
        console.log(jqXHR+ " " + textStatus + " " +errorThrow );
      }
    });

  }

})(jQuery);