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
    },
    create_piece: function(params){
      
      div = $("<div/>");
      div.text(params.piece.label).addClass("piece").addClass(params.piece.type).addClass(params.piece.id);
      $("#tile_"+params.tile_position).append(div);

    // add another piece to game pieces
    },
    show_piece: function(piece) {
      
    },
    load_piece_type: function(machine_name) {
      
    }
  };
 
})(jQuery);