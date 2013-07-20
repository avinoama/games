(function ($) {
  Drupal.behaviors.GamePattern = {
    attach: function (context, settings) {
      board_sizes=[3,5,7];
      Drupal.behaviors.GamePattern.init(5);
      refresh_inputs();
    },
    init : function (current_board_size) {
      console.log("init");
      Drupal.settings.current_board_size = current_board_size;
      Drupal.settings.current_board_mid = current_board_mid = Math.ceil(current_board_size/2);

      if($(".board_pattern").empty()) {
        create_board(current_board_size,current_board_mid);
      }
      if(Drupal.settings.pattern.field_pattern==undefined) {
        Drupal.settings.pattern.field_pattern = new Array();
        Drupal.settings.pattern.field_pattern['und']= new Array();
      }
      var p  = Drupal.settings.pattern.field_pattern['und'];
      Drupal.settings.patterns=[];
      for(i in p) {
        temp = p[i]['value']
        .replace(/px/gi,current_board_mid)
        .replace(/py/gi,current_board_mid)
        .replace(/left/gi,1)
        .replace(/right/gi,current_board_size)
        .replace(/top/gi,1)
        .replace(/bottom/gi,current_board_size);

        pattern = $.parseJSON(temp);
        this.eval_single_pattern(pattern);

      }
    },
    eval_single_pattern: function (pattern) {
      if(pattern!=null) {
        Drupal.settings.patterns.push(pattern);
        if(pattern.start!= null && pattern.end!= null) {
          pattern.start.x = eval(pattern.start.x);
          pattern.start.y = eval(pattern.start.y);
          pattern.end.x = eval(pattern.end.x);
          pattern.end.y = eval(pattern.end.y);

          if(pattern.end.x < pattern.start.x  ||  pattern.end.y<pattern.start.y) {
            for(i=pattern.start.x;i>=pattern.end.x;i--) {
              for(j=pattern.start.y;j>=pattern.end.y;j--) {
                $(".position_" + i  + "_" + j).addClass("selected");
              }
            }
          } else {
            for(i=pattern.start.x;i<=pattern.end.x;i++) {
              for(j=pattern.start.y;j<=pattern.end.y;j++) {
                $(".position_" + i  + "_" + j).addClass("selected");
              }
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
  }
  function switch_sides(pattern) {
    start = {
      "x": pattern.end.x ,
      "y" :pattern.end.y
    };
    end = {
      "x": pattern.start.x ,
      "y" :pattern.start.y
    };
    return {
      "start":start,
      "end": end
    };
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
      // add arrows
        
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

    b = $("<button/>").html('↙').addClass("diagnal_button").attr("id",'1').attr("value","urtbl").bind("click",handle_button_click);
    right_buttons.append(b);
    b = $("<button/>").html('↘').addClass("diagnal_button").attr("id",'2').attr("value","ultbr").bind("click",handle_button_click);
    left_buttons.append(b);

    for(y=1;y<= current_board_size;y++) {

      b = $("<button/>").html('←').addClass("nerrow_button").attr("id",y).attr("value","rtl").bind("click",handle_button_click);
      right_buttons.append(b);
      b = $("<button/>").html('→').addClass("nerrow_button").attr("id",y).attr("value","ltr").bind("click",handle_button_click);
      left_buttons.append(b);
      for(x=1;x<= current_board_size;x++) {
        if(y==1) {
          b = $("<button/>").html('↑').addClass("wide_button").attr("id",x).attr("value","btu").bind("click",handle_button_click);
          bottom_buttons.append(b);
          b = $("<button/>").html('↓').addClass("wide_button").attr("id",x).attr("value","utb").bind("click",handle_button_click);
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
    b = $("<button/>").html('↖').addClass("diagnal_button").attr("id",'3').attr("value","brtul").bind("click",handle_button_click);
    right_buttons.append(b);
    b = $("<button/>").html('↗').addClass("diagnal_button").attr("id",'4').attr("value","bltur").bind("click",handle_button_click);
    left_buttons.append(b);

    board.width((tile_size*(current_board_size))+20);
    board.height((tile_size*(current_board_size))+20);
    board.append(top_buttons).append(bottom_buttons).append(right_buttons).append(left_buttons);
    $("#edit-field-pattern").prepend(board).prepend(controller);
  }
  function handle_button_click(e) {
    e.preventDefault();
    console.log(e);
    var b= $(e.currentTarget);
    middle = $(".tile.middle");
    middle_id = middle.attr("id").replace("tile_");
    var middle_position = get_position($(middle).attr("class"));

    switch (b.val()) {
      case 'ltr':
        id = b.attr("id");
        middle_position[1];
        row= middle_position[1]- id;
        pattern = '{"start":{"x": "left","y": "py+@row"},"end":{"x": "right","y": "py+@row"}}';
        pattern = pattern.replace(/@row/gi, row );
        
        Drupal.settings.pattern.field_pattern['und'].push({
          "value":pattern
        });

        refresh_inputs();
        break;
    }
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
    var pattern = create_pattern_from_tile(tile);
    input_pattern = $('#edit-field-pattern .form-item tbody tr td .form-type-textfield input[value="'+pattern+'"]');
    input_pattern.val("");
    for (i in Drupal.settings.pattern.field_pattern['und']) {
      if(Drupal.settings.pattern.field_pattern['und'][i]['value']==pattern) {
        Drupal.settings.pattern.field_pattern['und'].splice(i, 1);
        break;
      }
    }
  }
  function _tile_select(tile) {
    pattern = create_pattern_from_tile(tile);
    Drupal.settings.pattern.field_pattern['und'].push({
      "value":pattern
    });
    input_pattern = $('#edit-field-pattern .form-item tbody tr td .form-type-textfield  input:text');
    for ( i in input_pattern) {
      if($(input_pattern[i]).val()=="") {
        $(input_pattern[i]).val(pattern);
        break;
      }
    }
    setTimeout(function(){
      l=$('#edit-field-pattern .form-item tbody tr td .form-type-textfield  input').length;
      console.log(l+ " == " + Drupal.settings.pattern.field_pattern['und'].length);
      if(l==Drupal.settings.pattern.field_pattern['und'].length) {
        $('[name="field_pattern_add_more"]').mousedown();
      }
    },100);
    tile.addClass("selected");
  }
  function create_pattern_from_tile(tile) {
    tile_id = $(tile).attr("id").replace("tile_");
    tile_position = get_position($(tile).attr("class"));

    middle = $(".tile.middle");
    middle_id = middle.attr("id").replace("tile_");
    middle_position = get_position($(middle).attr("class"));

    //pattern = '{"start":{"x": "px","offsetx":"@offsetx","y": "py","offsety":"@offsety","repeat":1}}';
    pattern = '{"start":{"x": "px+@offsetx","y": "py+@offsety"}}';

    pattern = pattern.replace("@offsetx", tile_position[0] - middle_position[0] );
    pattern = pattern.replace("@offsety", tile_position[1] - middle_position[1] );
    return pattern;
  }
  function refresh_inputs(){
    var inputs = $("#field-pattern-values .draggable input");
    for (i in Drupal.settings.pattern.field_pattern['und']) {
      $(inputs[i]).val(Drupal.settings.pattern.field_pattern['und'][i]['value']);
    }
  }

  function get_position(tile_class) {
    start=tile_class.indexOf("position_");
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
  }
})(jQuery);