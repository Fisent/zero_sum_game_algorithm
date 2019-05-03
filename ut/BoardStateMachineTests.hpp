#include "gtest/gtest.h"

#include <memory>
#include <vector>

#include "../src/game/Board.hpp"

namespace state_machine_test{

/* BOARD
o-----o-----B
|     |     |
| o---W---B |
| |   |   | |
| | B-B-W | |
| | |   | | |
W-B o   W-W-B
| | |   | | |
| | W-B-B | |
| |   |   | |
| o---W---o |
|     |     |
W-----o-----W*/
const std::vector<int> white_indexes{8, 9, 12, 13, 15, 19, 21, 23};
const std::vector<int> black_indexes{2, 6, 7, 10, 14, 16, 17, 5};
std::unique_ptr<Board> create_second_board(){
    auto b = std::make_unique<Board>();
    for(int i = 0; i < white_indexes.size(); i++){
        b->place_pawn(white_indexes.at(i));
        b->place_pawn(black_indexes.at(i));
    }
    return std::move(b);
}

TEST(BoardStateMachineShould, notMakeRegularMoveWhenItsTimeToTake){
    auto b = create_second_board();

    b->place_pawn(22);
    ASSERT_TRUE(b->place_pawn(0));
}

TEST(BoardStateMachineShould, notTakeWhenItsTimeForNormalMove){
    auto b = create_second_board();

    ASSERT_FALSE(b->take_pawn(2));
}

TEST(BoardStateMachineShould, makeTakeMoveAfterThreeInARow){
    auto b = create_second_board();

    b->place_pawn(22);
    ASSERT_TRUE(b->take_pawn(2));
}

TEST(BoardStateMachineShould, notMakeTakeMoveAfterThreeInARowButForWrongPlayer){
    auto b = create_second_board();

    b->place_pawn(22);
    ASSERT_FALSE(b->take_pawn(4));
}

} // namespace state_machine_test