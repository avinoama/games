(function ($) {
  Drupal.behaviors.GamePattern = {
    attach: function (context, settings) {
      board_sizes=[3,5,7];
      Drupal.behaviors.GamePattern.init(5);
    },
    init : function (current_board_size) {
      Drupal.settings.current_board_size = current_board_size;
      Drupal.settings.current_board_mid = current_board_mid = Math.ceil(current_board_size/2);

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
        pattern.start.x = eval(pattern.start.x);
        pattern.start.y = eval(pattern.start.y);
        if(pattern.start.repeat!=null) {
          for (i=0;i<=pattern.start.repeat;i++) {
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
    $('.board_pattern').remove();
    $('.pattern_controller').remove();
    board_sizes=[3,5,7,9];
    
    controller = $("<ul/>").addClass("pattern_controller");
    for(size in board_sizes) {
      li=$("<li/>");
      li.text(board_sizes[size]+ "x" + board_sizes[size]).attr("id",board_sizes[size]);
      if(current_board_size==board_sizes[size]) {
        li.addClass("selected");
      }
      li.bind("click",function(e){
        Drupal.behaviors.GamePattern.init($(e.currentTarget).attr("id"));
      });
      controller.append(li);
    }
    
    tile_size=40;
    board = $("<div/>").addClass("board_pattern");

    count=0;
    var top_buttons = $("<div/>").addClass("top_buttons buttons");
    var bottom_buttons = $("<div/>").addClass("bottom_buttons buttons");
    var right_buttons = $("<div/>").addClass("right_buttons buttons");
    var left_buttons = $("<div/>").addClass("left_buttons buttons");

    b = $("<button/>").html('↙').addClass("diagnal_button");
    right_buttons.append(b);
    b = $("<button/>").html('↘').addClass("diagnal_button");
    left_buttons.append(b);

    for(y=1;y<= current_board_size;y++) {

      b = $("<button/>").html('←').addClass("nerrow_button");
      right_buttons.append(b);
      b = $("<button/>").html('→').addClass("nerrow_button");
      left_buttons.append(b);
      for(x=1;x<= current_board_size;x++) {
        if(y==1) {
          b = $("<button/>").html('↑').addClass("wide_button");
          bottom_buttons.append(b);
          b = $("<button/>").html('↓').addClass("wide_button");
          console.log(b);
          top_buttons.append(b);
        }
        tile = $("<div/>")
        .addClass("tile")
        .addClass("position_" + x  + "_" + y)
        .attr("id","tile_"+count)
        .html("&nbsp;");
        
        if(x==y && y== current_board_mid) {
          tile.addClass("middle");
        }
        if(x==current_board_size) {
          tile.addClass("right");
        }
        if(y==current_board_size) {          
          
          tile.addClass("bottom");
        }
        if(x==1) {
          tile.addClass("left");
        }
        if(y==1) {
          tile.addClass("top");
        }
        tile.bind("click",handle_tile_click);
        //
        //tile.bind("mouseout",handle_mouse_move_on_tile);
        board.append(tile);
        count++;
      }
      
    }
    b = $("<button/>").html('↖').addClass("diagnal_button");
    right_buttons.append(b);
    b = $("<button/>").html('↗').addClass("diagnal_button");
    left_buttons.append(b);

    board.width((tile_size*(current_board_size))+20);
    board.height((tile_size*(current_board_size))+20);
    board.append(top_buttons).append(bottom_buttons).append(right_buttons).append(left_buttons);
    $("#edit-field-pattern").prepend(board).prepend(controller);
  }
  function handle_tile_click(e) {
    //check_if_pattern_selected
    tile =$(e.currentTarget);
    if(tile.hasClass("selected")) {
      _tile_unselect(tile);
    } else {
      _tile_select(tile);
    }    
  }
  function _tile_unselect(tile) {
    console.log("tile_unselect");
    tile.removeClass("selected");
  }
  function _tile_select(tile) {
    tile_id = $(tile).attr("id").replace("tile_");
    tile_position = get_position($(tile).attr("class"));
    console.log(tile_position);
    middle = $(".tile.middle");
    middle_id = middle.attr("id").replace("tile_");
    middle_position = get_position($(middle).attr("class"));
    console.log(middle_position);
    pattern = '{"start":{"x": "px","offsetx":"@offsetx","y": "py","offsety":"@offsety","repeat":1}}';
    
    pattern = pattern.replace("@offsetx", tile_position[0] - middle_position[0] );
    pattern = pattern.replace("@offsety", tile_position[1] - middle_position[1] );
    
    Drupal.settings.pattern.field_pattern['und'].push({
      "value":pattern
    });
    console.log(Drupal.settings.pattern.field_pattern['und']);
    tile.addClass("selected");
  }
  function get_position(tile_class) {
    console.log("get_position" + " "+ tile_class);
    start=tile_class.indexOf("position_");
    console.log(start);
    if(start>-1) {
      end = tile_class.indexOf(" ",start);
      if(end==-1) {
        end = tile_class.length;
      }
      tmp = tile_class.slice(start+9,end);
      return tmp.split("_");

    }
    return null;
  }
  function handle_mouse_move_on_tile(e) {
    
    mouseX = e.layerX - this.offsetLeft;
    mouseY = e.layerY - this.offsetTop;
    divPos = {
      left: e.pageX - $(this).offset().left,
      top: e.pageY - $(this).offset().top
    };
    if(divPos.left>10 && divPos.top<10 && divPos.left<30) {
      //console.log(divPos);
      $(this).addClass("top-arrow");
    } else if (divPos.left>30 && divPos.top>10 && divPos.top<30) {
      $(this).addClass("right-arrow");
      
    }else {
      $(this).removeClass("top-arrow");
      $(this).removeClass("right-arrow");
    }
  //var mousePos = {'x': e.layerX, 'y': e.layerY};
  //console.log(divPos);
  //console.log(mouseX + " " + mouseY);
  //console.log(mousePos);
  }
})(jQuery);