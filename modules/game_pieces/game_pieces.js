(function ($) {
  Drupal.behaviors.GamePieces = {
    attach: function (context, settings) {
      pieces = Drupal.settings.GamePieces.pieces;
      piece_types = Drupal.settings.GamePieces.piece_types;
      patterns = Drupal.settings.GamePieces.patterns;
      //console.log(Drupal.settings.GamePieces);

      pieces_holder = $("<div/>").attr("id","pieces_holder").css("position","relative");

      $(".game-canvas").prepend(pieces_holder);
      
      // draw current game pieces
      // add lisiners

      for (i in pieces) {
        this.create_piece({
          field_position : pieces[i].field_position,
          piece: pieces[i],
          piece_type: piece_types[pieces[i].type]
        });
      }

      $(".game-canvas").bind("click",function(e) {
        piece_end_tap(e);
      });
    },
    create_piece: function(params){
      piece = $("<div/>");
      $(piece).text(params.piece.label).addClass("piece")
      .addClass(params.piece.type)
      .addClass(params.piece.id)
      .attr("id","piece_"+params.piece.id).hide();
      
      piece.bind("click",function(){
        piece_tap(this)
      });
      $("#pieces_holder").append(piece);

      if(params.element!=null) {
        elem = $("#"+params.element);
        move_to_element(elem,piece);
      } else if (params.position!=null)  {
        move_to_position(params.position.split("-"),piece);
      } else if(params.field_position) {
        positions = new Array();
        for(v in params.field_position['und']) {
          positions.push(params.field_position['und'][v].value);
        }
        move_to_position(positions,piece);
      }
      
      
      
    // add another piece to game pieces
    },
    remove_piece: function(params){
      $("#piece_"+params.piece.id).hide();
    },

    move_piece: function(params) {
      piece = $("#piece_"+params.piece.id);
      console.log();
      tmp=Array(params.position.length);
      for(p in params.position) {
        tmp[p]=Array(1);
        tmp[p]['value']= params.position[p];
      }
      Drupal.settings.GamePieces.pieces[params.piece.id].field_position['und'] = tmp;
      move_to_position(params.position,piece);
    },
    load_piece_type: function(machine_name) {
      
    },
    current: null,
    show_pattern: function (pattern,piece) {
      px = piece['field_position']['und'][0]['value'];
      py = piece['field_position']['und'][1]['value'];
      dimension_amount = Drupal.settings.RunningGame.game.field_board_dimension_amount['und'];
      board_x = dimension_amount[0]['value'];
      board_y = dimension_amount[1]['value'];
      temp = pattern
      .replace(/px/gi,px)
      .replace(/py/gi,py)
      .replace(/left/gi,1)
      .replace(/right/gi,board_x)
      .replace(/top/gi,1)
      .replace(/bottom/gi,board_y);

      pattern = $.parseJSON(temp);
      this.eval_single_pattern(pattern);
    },
    eval_single_pattern: function (pattern) {
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
              //alert(i);
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
  };
  function show_current_piece_pattern(piece) {
    id = piece.id.replace("piece_","");
    pieces = Drupal.settings.GamePieces.pieces;
    piece_types = Drupal.settings.GamePieces.piece_types;
    patterns = Drupal.settings.GamePieces.patterns;
    current_pattern = piece_types[pieces[id].type].move_pattern;
    pattern = patterns[current_pattern];
    for(i in pattern.field_pattern['und']) {
      Drupal.behaviors.GamePieces.show_pattern(pattern.field_pattern['und'][i]['value'],pieces[id]);
    }
  }

  function piece_tap(piece) {
    current = Drupal.behaviors.GamePieces.current;
    if(current != piece.id) {
      mark_piece(piece);
      setTimeout(function(){
        Drupal.behaviors.GamePieces.current = piece.id.replace("piece_","");
      },100);
    }
  }
  function mark_piece(piece) {
    $(".piece").removeClass("selected");
    $(piece).addClass("selected");
    show_current_piece_pattern(piece);
  }
  function piece_end_tap(e) {
    elem = document.elementFromPoint(e.clientX, e.clientY);
    if(Drupal.behaviors.GamePieces.current != undefined) {  
      if(($(elem).attr("id")).indexOf("tile")>=0) {
        position = piece_get_position(elem);
        trigger_piece_move_to_position(Drupal.behaviors.GamePieces.current, position);
      } else if (($(elem).attr("id")).indexOf("piece")>=0) {
        id = $(elem).attr("id").replace("piece_","");
        trigger_piece_interact(Drupal.behaviors.GamePieces.current, id);
      }
      Drupal.behaviors.GamePieces.current = undefined;
      $(".piece").removeClass("selected");
      $(".tile.selected").removeClass("selected");
    }
    
  }

  /**
   * change to move to element
   */
  function trigger_piece_move_to_position(piece,position) {
    params = {
      "piece":piece,
      "position":position
    };
    hook = "piece_move_to_position";
    Drupal.behaviors.RunningGame.trigger_rule(hook, params);
  };
  function trigger_piece_interact(initiator, initiated) {
    setTimeout(function(){
      Drupal.behaviors.GamePieces.current = undefined;
    },100);
    Drupal.behaviors.GamePieces.current = undefined;
    params = {
      "initiator":initiator,
      "initiated":initiated
    };
    hook = "piece_initiate";
    Drupal.behaviors.RunningGame.trigger_rule(hook, params);
  }
  function move_to_position(position, piece) {
    pos = "position";
    for(p in position) {
      pos = pos +"_"+ position[p];
    }
    element = $("."+pos);
    if(element.length>0) {
      move_to_element(element, piece);
    }
  }
  function move_to_element(element, piece) {
    $(piece).animate({
      "left": element.position().left + (element.width()/2)-(piece.width()/2),
      "top": element.position().top + (element.height()/2)-(piece.height()/2)
    }, "slow");
    $(piece).show();
  }
  function element_is_tile(that) {
    //console.log($(that).id);
    return false
  }
  function piece_get_position(elem) {
    pos = "position_";
    for(c in elem.classList) {
      if(elem.classList[c].indexOf(pos)>=0) {
        s = elem.classList[c].replace(pos,"");
        return s.split("_");
      }
    }
    return null;
  }
})(jQuery);