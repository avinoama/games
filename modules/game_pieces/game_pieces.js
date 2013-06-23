(function ($) {
  Drupal.behaviors.GamePieces = {
    attach: function (context, settings) {
      pieces = Drupal.settings.GamePieces.pieces;
      piece_types = Drupal.settings.GamePieces.piece_types;
      patterns = Drupal.settings.GamePieces.patterns;
      
      var dimension_amount = Drupal.settings.RunningGame.game.field_board_dimension_amount['und'];
      
      var positions = Drupal.settings.GamePieces.positions;
      if(!positions) {positions=Array();}
      pieces_holder = $("<div/>").attr("id","pieces_holder").css("position","relative");

      $(".game-canvas").prepend(pieces_holder);
      console.log(pieces);
      // draw current game pieces
      // add lisiners
      
      items = Array();
      for (i in pieces) {
        
        position = pieces[i].field_position['und'];
        pointer= positions;
        for(j=0;j<dimension_amount.length;j++) {
          if(!pointer[position[j]['value']]) {
            pointer[position[j]['value']]=Array()
          }
          pointer = pointer[position[j]['value']] ;
          if(j== (dimension_amount.length-1)) {
            if(!pointer) {
              pointer= Array();
            }
            pointer.push(pieces[i].id);
          }
        }
        
        this.create_piece({
          field_position : pieces[i].field_position,
          piece: pieces[i],
          piece_type: piece_types[pieces[i].type]
        });
      }
      
      Drupal.settings.GamePieces.positions = positions;
      console.log(positions);
      $(".game-canvas").bind("click",function(e) {
        piece_end_tap(e);
      });
    },
    create_piece: function(params){
      piece = $("<div/>");
      $(piece).text(params.piece.label).addClass("piece")
      .addClass(params.piece.type)
      .addClass(params.piece.id)
      //.addClass("owned_"+params.piece.uid)
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
      var positions = Drupal.settings.GamePieces.positions;

      piece = $("#piece_"+params.piece.id);
      // remove piece

      tmp=Array(params.position.length);
      for(p in params.position) {
        tmp[p]=Array(1);
        tmp[p]['value']= params.position[p];
      }
      
      if(positions[params.position[0]]==undefined) {
        positions[params.position[0]] = Array();
      }
      if(positions[params.position[0]][params.position[1]]==undefined) {
        positions[params.position[0]][params.position[1]] = Array();
      }
      positions[params.position[0]][params.position[1]].push(params.piece.id);
      old_position = Drupal.settings.GamePieces.pieces[params.piece.id].field_position['und'];
      if(positions[old_position[0]['value']] != undefined) {
        if(positions[old_position[0]['value']][old_position[1]['value']] != undefined) {
          positions[old_position[0]['value']][old_position[1]['value']] = undefined;
        }
      }
      Drupal.settings.GamePieces.pieces[params.piece.id] = params.piece;
      move_to_position(params.position,piece);
    },
    load_piece_type: function(machine_name) {
      
    },
    current: null,
    show_pattern: function (pattern,piece,over_piece) {
      if(!over_piece) {
        over_piece=0;
      }
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

      this.eval_single_pattern(pattern,over_piece);
    },
    eval_single_pattern: function (pattern, over_piece) {
      var positions = Drupal.settings.GamePieces.positions;
      
      
      if(pattern!=null) {
        if(pattern.start!= null && pattern.end!= null) {
          pattern.start.x = eval(pattern.start.x);
          pattern.start.y = eval(pattern.start.y);
          pattern.end.x = eval(pattern.end.x);
          pattern.end.y = eval(pattern.end.y);
          
          
          if(pattern.end.x < pattern.start.x  ||  pattern.end.y<pattern.start.y) {
            for(i=pattern.start.x; i >= pattern.end.x; i--) {
              for(j=pattern.start.y; j >= pattern.end.y; j--) {
                if(over_piece==0 && positions[i]!=undefined) {if(positions[i][j]!=undefined) {console.log("re");return;}}
                $(".position_" + i  + "_" + j).addClass("selected");
              }
             // if(over_piece==0 && positions[i]!=undefined) {return;}
            }
          } else {
            for(i=pattern.start.x;i<=pattern.end.x;i++) {
              for(j=pattern.start.y;j<=pattern.end.y;j++) {
                if(over_piece==0 && positions[i]!=undefined) {if(positions[i][j]!=undefined) {return;}}
                $(".position_" + i  + "_" + j).addClass("selected");
              }
               if(over_piece==0 && positions[i]!=undefined) {return;}
            }
          }
        }
        else if(pattern.start!= null) {
          pattern.start.x = eval(pattern.start.x);
          pattern.start.y = eval(pattern.start.y);
          if(pattern.start.repeat!=null) {
            for (i=0;i<=pattern.start.repeat;i++) {
              x = pattern.start.x + (pattern.start.offsetx* i);
              y = pattern.start.y + (pattern.start.offsety* i);
              
              if(over_piece==0 && positions[x]!=undefined) {
                if(positions[x][y]!=undefined) {
                  console.log(x+ " " +y);
                  return;
                }
              }

              $(".position_" + (x) + "_" + (y)).addClass("selected");
            }
          } else {
            if( positions[pattern.start.x]!=undefined) {
              if(positions[pattern.start.x][pattern.start.y]!=undefined) {
              //return;
              }
            }
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
  function show_current_piece_pattern(piece) {
    id = piece.id.replace("piece_","");
    pieces = Drupal.settings.GamePieces.pieces;
    piece_types = Drupal.settings.GamePieces.piece_types;
    patterns = Drupal.settings.GamePieces.patterns;
    current_pattern = piece_types[pieces[id].type].move_pattern;
    pattern = patterns[current_pattern];
    over_piece = pattern.field_over_piece['und'][0]['value'];
    
    for(i in pattern.field_pattern['und']) {
      Drupal.behaviors.GamePieces.show_pattern(pattern.field_pattern['und'][i]['value'],pieces[id],over_piece);
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