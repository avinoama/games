(function ($) {
  Drupal.behaviors.GamePieces = {
    attach: function (context, settings) {
      pieces = Drupal.settings.GamePieces.pieces;
      piece_types = Drupal.settings.GamePieces.piece_types;


      pieces_holder = $("<div/>").attr("id","pieces_holder").css("position","relative");

      $(".game-canvas").prepend(pieces_holder);
      
      // draw current game pieces
      // add lisiners
      for (i in pieces) {
        this.create_piece({
          tile_position : pieces[i].position,
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
      piece.text(params.piece.label).addClass("piece").addClass(params.piece.type).addClass(params.piece.id).attr("id","piece_"+params.piece.id).hide();
      piece.bind("click",function(){
        piece_tap(this)
      });
      $("#pieces_holder").append(piece);
      tile = $("#tile_"+params.tile_position);
      
      move_to_tile(tile,piece);
      
      
    // add another piece to game pieces
    },
    move_piece: function(params) {
      tile = $("#tile_"+params.tile_position);
      piece = $("#piece_"+params.piece.id);
      move_to_tile(tile,piece);
    },
    load_piece_type: function(machine_name) {
      
    },
    current: null
  };
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

  }
  function piece_end_tap(e) {
    if(Drupal.behaviors.GamePieces.current!=undefined) {
      elem = document.elementFromPoint(e.clientX, e.clientY);
      position = $(elem).attr("id").replace("tile_","");
      piece_move_to_tile(Drupal.behaviors.GamePieces.current,position);
      Drupal.behaviors.GamePieces.current = undefined;
      $(".piece").removeClass("selected");
    }
  }
  /**
   * change to move to element
   */
  function piece_move_to_tile(piece,position) {
    params = {
      "piece":piece,
      "tile_position":position
    };
    hook = "piece_move_to_tile";
    Drupal.behaviors.RunningGame.trigger_rule(hook, params);
  };
  function move_to_tile(tile,piece) {
    $(piece).animate({
      "left": tile.position().left + (tile.width()/2)-(piece.width()/2),
      "top": tile.position().top + (tile.height()/2)-(piece.height()/2)
      }, "slow");
    $(piece).show();
    
  }
})(jQuery);