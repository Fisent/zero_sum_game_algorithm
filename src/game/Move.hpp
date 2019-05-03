
/*
    During the game there can be three kind of moves:
        place_pawn(pawn_index, player_color)
        move_pawn(pawn_start_index, pawn_destination_index, player_color)
        take_pawn(pawn_index, player_which_makes_this_move_color)

        player color is mandatory only in place_pawn move, in two others it only is validated to see if this player can move
*/

struct Move{
    int first_index;
    int second_index;
    Field color;
};