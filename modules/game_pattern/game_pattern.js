(function ($) {
  Drupal.behaviors.GamePattern = {
    attach: function (context, settings) {
      board_sizes=[3,5,7,9,11];
      Drupal.behaviors.GamePattern.init(9);
    },
    init : function (current_board_size) {
      
      current_board_mid=Math.ceil(current_board_size/2);

      if($(".board_pattern").empty()) {
        create_board(current_board_size,current_board_mid);
      }

      var p  = Drupal.settings.pattern.field_pattern;
      for(i in p['und']) {
        temp = p['und'][i]['value']
        .replace(/px/gi,current_board_mid)
        .replace(/py/gi,current_board_mid)
        .replace(/left/gi,1)
        .replace(/right/gi,current_board_size)
        .replace(/top/gi,1)
        .replace(/bottom/gi,current_board_size);

        pattern = $.parseJSON(temp);
        eval_single_pattern(pattern);

      }
      
    }
  }
  function eval_single_pattern(pattern) {
    if(pattern!=null) {
      if(pattern.start!= null && pattern.end!= null) {
        pattern.start.x = eval(pattern.start.x);
        pattern.start.y = eval(pattern.start.y);
        pattern.end.x = eval(pattern.end.x);
        pattern.end.y = eval(pattern.end.y);
        for(i=pattern.start.x;i<=pattern.end.x;i++) {
          for(j=pattern.start.y;j<=pattern.end.y;j++) {
            $(".position_" + i  + "_" + j).addClass("selected");
          }
        }
      }
      else if(pattern.start!= null) {
        console.log(pattern);
        pattern.start.x = eval(pattern.start.x);
        pattern.start.y = eval(pattern.start.y);
        if(pattern.start.repeat!=null) {
          for (i=0;i<=pattern.start.repeat;i++) {
            //$(".position_" + ( pattern.start.x + i) + "_" + (pattern.start.y + i)).addClass("selected");
            //console.log(pattern.start.x+ " " + pattern.start.y);
            //console.log(pattern.start.offsetx+ " " + pattern.start.offsety);
            //console.log(pattern.start.offsetx* i+ " " + pattern.start.offsety* i);
            //console.log( (Number(pattern.start.x)  + Number( pattern.start.offsetx * i ) )+ " " + (Number(pattern.start.y)  + Number(pattern.start.offsety * i)));
            //console.log("------");
            $(".position_" + (pattern.start.x + (pattern.start.offsetx* i)) + "_" + (pattern.start.y + (pattern.start.offsety* i))).addClass("selected");
          }
        } else {
          $(".position_" + pattern.start.x  + "_" + pattern.start.y).addClass("selected");
        }
      }
      else if(pattern.end!= null) {
            
        pattern.end.x = eval(pattern.end.x);
        pattern.end.y = eval(pattern.end.y);
        $(".position_" + pattern.end.x  + "_" + pattern.end.y).addClass("selected");
      }
    }
  }
  function create_board(current_board_size,current_board_mid) {

    tile_size=40;
    
    board = $("<div/>").addClass("board_pattern");
    count=0;
    for(y=1;y<= current_board_size;y++) {
      for(x=1;x<= current_board_size;x++) {
        tile = $("<div/>")
        .addClass("tile")
        .addClass("position_" + x  + "_" + y)
        .attr("id","tile_"+count)
        .html("&nbsp;");
              
        if(x==y && y== current_board_mid) {
          //console.log(i  + "_" + j);
          tile.addClass("middle");
                
        }
        board.append(tile);
        count++;
      }
      
    }
    board.width((tile_size*current_board_size)+20);
    board.height((tile_size*current_board_size)+20);
    $("#edit-field-pattern").prepend(board);
  }
})(jQuery);