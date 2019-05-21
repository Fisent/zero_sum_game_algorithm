#pragma once

/*
    During the game there can be three kind of moves:
        place_pawn(pawn_index, player_color)
        move_pawn(pawn_start_index, pawn_destination_index, player_color)
        take_pawn(pawn_index, player_which_makes_this_move_color)

*/

struct Move{
    Move(int index): first_index{index}, second_index{-1}{}
    Move(int first_ind, int second_ind): first_index{first_ind}, second_index{second_ind}{}
    int first_index;
    int second_index;
};
