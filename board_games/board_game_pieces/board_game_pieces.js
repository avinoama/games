(function ($) {
  Drupal.behaviors.boardGamePieces = {
    attach: function (context, settings) {
      pieces = Drupal.settings.boardGamePieces.pieces;
      piece_types = Drupal.settings.boardGamePieces.piece_types;
      
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
        piece_end_tap(e)
        });
    },
    create_piece: function(params){
      
      piece = $("<div/>");
      piece.text(params.piece.label).addClass("piece").addClass(params.piece.type).addClass(params.piece.id).attr("id",params.piece.id);
      piece.bind("click",function(){
        piece_tap(this)
        });
      $("#tile_"+params.tile_position).append(piece);
      
    // add another piece to game pieces
    },
    show_piece: function(piece) {
      
    },
    load_piece_type: function(machine_name) {
      
    },
    current: null
  };
  function piece_tap(piece) {
    current = Drupal.behaviors.boardGamePieces.current;
    if(current != piece.id) {
      mark_piece(piece);
      setTimeout(function(){Drupal.behaviors.boardGamePieces.current = piece.id;},1000);
    }
  }
  function mark_piece(piece) {
    $(".piece").removeClass("selected");
    $(piece).addClass("selected");

  }
  function piece_end_tap(e) {
    if(Drupal.behaviors.boardGamePieces.current!=undefined) {
      console.log("piece_end_tap");
      console.log(e);
      Drupal.behaviors.boardGamePieces.current = undefined;
      $(".piece").removeClass("selected");
    }
  }
  function request_move() {
    
    
  }
})(jQuery);