#include "gtest/gtest.h"
#include <utility>

/*
test board
W - white pawn
B - black pawn
o - empty field

B-----o-----B
|     |     |
| o---W---o |
| |   |   | |
| | B-B-W | |
| | |   | | |
W-B o   W-W-B
| | |   | | |
| | W-B-B | |
| |   |   | |
| o---W---o |
|     |     |
W-----B-----W

*/

std::vector<int> white_indexes{4, 8, 9, 12, 13, 15, 19, 21, 23};
std::vector<int> black_indexes{0, 2, 6, 7, 10, 14, 16, 17, 22};

std::vector<std::pair<int, int>> possible_moves{{0, 1}, {4, 5}, {10, 3}, {13, 20}};

std::unique_ptr<Board> createSecondPhaseBoard(){
    auto b = std::make_unique<Board>();
    for(int i = 0; i < 9; i++){
        b->place_pawn(white_indexes.at(i), Field::WHITE);
        b->place_pawn(black_indexes.at(i), Field::BLACK);
    }
    return std::move(b);
}

/*

o-----B-----B
|     |     |
| B---o---W |
| |   |   | |
| | B-B-W | |
| | |   | | |
W-o o   W-o-B
| | |   | | |
| | W-B-B | |
| |   |   | |
| o---W---W |
|     |     |
W-----B-----W

*/

std::vector<int> white_indexes_after_possible_moves{5, 8, 9, 12, 15, 19, 20, 21, 23};
std::vector<int> black_indexes_after_possible_moves{1, 2, 3, 6, 7, 14, 16, 17, 22};

std::unique_ptr<Board> expectedBoardAfterPossibleMoves(){
    auto b = std::make_unique<Board>();
    for(int i = 0; i < 9; i++){
        b->place_pawn(white_indexes_after_possible_moves.at(i), Field::WHITE);
        b->place_pawn(black_indexes_after_possible_moves.at(i), Field::BLACK);
    }
    return std::move(b);
}

TEST(BoardShould, advancePhase){
    auto b = createSecondPhaseBoard();
    ASSERT_EQ(b->get_phase(), GamePhase::SECOND_PHASE);
}

TEST(BoardShould, notMakeMoveFromEmptyField){
    auto b = createSecondPhaseBoard();
    ASSERT_FALSE(b->make_move(1, 2));
}

TEST(BoardShould, notMakeMoveToOccupiedField){
    auto b = createSecondPhaseBoard();
    ASSERT_FALSE(b->make_move(0, 9));
}

TEST(BoardShould, make_possible_moves){
    auto b = createSecondPhaseBoard();
    for(auto move : possible_moves){
        ASSERT_TRUE(b->make_move(move.first, move.second));
    }
    ASSERT_EQ(*b, *expectedBoardAfterPossibleMoves());
}
