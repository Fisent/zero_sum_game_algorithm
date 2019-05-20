#include <gtest/gtest.h>

#include <memory>

#include "../src/game/Board.hpp"

namespace e{

/* FIRST BOARD
w-----o-----B
|     |     |
| o---o---o |
| |   |   | |
| | o-o-o | 
| | |   | | |
o-o-o   o-o-o
| | |   | | |
| | o-o-o | |
| |   |   | |
| o---o---o |
|     |     |
o-----o-----W*/
std::unique_ptr<Board> create_first_board(){
    auto b = std::make_unique<Board>();
    b->place_pawn(0);
    b->place_pawn(2);
    b->place_pawn(23);
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
        b->place_pawn(white_indexes_second.at(i));
        b->place_pawn(black_indexes_second.at(i));
    }
    return std::move(b);
}
const int EXPECTED_WHITE_POINTS_SECOND_BOARD{cost_map.at(Advantage::PAWN) * 9 + 
                                             cost_map.at(Advantage::TWO_IN_A_ROW) * 4};
const int EXPECTED_BLACK_POINTS_SECOND_BOARD{cost_map.at(Advantage::PAWN) * 9 +
                                             cost_map.at(Advantage::TWO_IN_A_ROW) * 5};

// /* THIRD BOARD
// B-----B-----B
// |     |     |
// | o---W---o |
// | |   |   | |
// | | B-B-W | |
// | | |   | | |
// W-B o   W-W-B
// | | |   | | |
// | | W-B-B | |
// | |   |   | |
// | o---W---o |
// |     |     |
// W-----W-----W*/
// const std::vector<int> white_indexes_third{8, 9, 12, 13, 15, 19, 21, 22, 23};
// const std::vector<int> black_indexes_third{0, 1, 2, 6, 7, 14, 16, 17, 20};
// std::unique_ptr<Board> create_third_board(){
//     auto b = std::make_unique<Board>();
//     for(int i = 0; i < white_indexes_third.size(); i++){
//         b->place_pawn(white_indexes_third.at(i));
//         b->place_pawn(black_indexes_third.at(i));
//     }
//     return std::move(b);
// }
// const int EXPECTED_WHITE_POINTS_THIRD_BOARD{cost_map.at(Advantage::PAWN) * 9 + 
//                                             cost_map.at(Advantage::TWO_IN_A_ROW) * 4 + 
//                                             cost_map.at(Advantage::THREE_IN_A_ROW)};
// const int EXPECTED_BLACK_POINTS_THIRD_BOARD{cost_map.at(Advantage::PAWN) * 9 +
//                                             cost_map.at(Advantage::TWO_IN_A_ROW) * 4 +
//                                             cost_map.at(Advantage::THREE_IN_A_ROW)};

TEST(BoardShouldEvaluate, FirstBoard){
    auto b = create_first_board();
    ASSERT_EQ(EXPECTED_WHITE_POINTS_FIRST_BOARD, b->evaluate_points(Field::WHITE));
    ASSERT_EQ(EXPECTED_BLACK_POINTS_FIRST_BOARD, b->evaluate_points(Field::BLACK));
}

TEST(BoardShouldEvaluate, SecondBoard){
    auto b = create_second_board();
    ASSERT_EQ(EXPECTED_WHITE_POINTS_SECOND_BOARD, b->evaluate_points(Field::WHITE));
    ASSERT_EQ(EXPECTED_BLACK_POINTS_SECOND_BOARD, b->evaluate_points(Field::BLACK));
}

// TEST(BoardShouldEvaluate, ThirdBoard){
//     auto b = create_third_board();
//     ASSERT_EQ(EXPECTED_WHITE_POINTS_THIRD_BOARD, b->evaluate_points(Field::WHITE));
//     ASSERT_EQ(EXPECTED_BLACK_POINTS_THIRD_BOARD, b->evaluate_points(Field::BLACK));
// }

} // namespace
