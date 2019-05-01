#include <gtest/gtest.h>

#include <memory>

#include "../src/game/Board.hpp"

namespace e{

/* SECOND BOARD
o-----o-----o
|     |     |
| o---o---o |
| |   |   | |
| | o-o-o | |
| | |   | | |
o-o-o   o-o-o
| | |   | | |
| | o-o-o | |
| |   |   | |
| o---o---o |
|     |     |
o-----o-----o*/
std::unique_ptr<Board> create_first_board(){
    auto b = std::make_unique<Board>();
    b->place_pawn(0, Field::WHITE);
    b->place_pawn(2, Field::BLACK);
    b->place_pawn(23, Field::WHITE);
    return std::move(b);
}
const int EXPECTED_WHITE_POINTS_FIRST_BOARD{cost_map.at(Advantage::PAWN) * 2};
const int EXPECTED_BLACK_POINTS_FIRST_BOARD{cost_map.at(Advantage::PAWN) * 1};


/* SECOND BOARD
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
W-----B-----W*/
const std::vector<int> white_indexes_second{4, 8, 9, 12, 13, 15, 19, 21, 23};
const std::vector<int> black_indexes_second{0, 2, 6, 7, 10, 14, 16, 17, 22};
std::unique_ptr<Board> create_second_board(){
    auto b = std::make_unique<Board>();
    for(int i = 0; i < white_indexes_second.size(); i++){
        b->place_pawn(white_indexes_second.at(i), Field::WHITE);
        b->place_pawn(black_indexes_second.at(i), Field::BLACK);
    }
    return std::move(b);
}
const int EXPECTED_WHITE_POINTS_SECOND_BOARD{90};
const int EXPECTED_BLACK_POINTS_SECOND_BOARD{90};

} // namespace

TEST(BoardShouldEvaluate, FirstBoard){
    auto b = e::create_first_board();
    ASSERT_EQ(e::EXPECTED_WHITE_POINTS_FIRST_BOARD, b->evaluate_points(Field::WHITE));
    ASSERT_EQ(e::EXPECTED_BLACK_POINTS_FIRST_BOARD, b->evaluate_points(Field::BLACK));
}