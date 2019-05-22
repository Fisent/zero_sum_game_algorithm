#pragma once

/*
    During the game there can be three kind of moves:
        place_pawn(pawn_index, player_color)
        move_pawn(pawn_start_index, pawn_destination_index, player_color)
        take_pawn(pawn_index, player_which_makes_this_move_color)

*/

struct Move{
    Move(int index, bool taking_arg=false): first_index{index}, second_index{-1}, taking{taking_arg}{}
    Move(int first_ind, int second_ind, bool taking_arg=false): first_index{first_ind}, second_index{second_ind}, taking{taking_arg}{}
    int first_index;
    int second_index;
    bool taking;
};
