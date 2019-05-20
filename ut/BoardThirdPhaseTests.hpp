#include "../src/game/Board.hpp"

// how to create board in third phase state?

class BoardTestable : public Board{
public:
    using Board::phase;
};

/*
W-----o-----o
|     |     |
| o---o---o |
| |   |   | |
| | o-o-o | |
| | |   | | |
o-o o   o-o-o
| | |   | | |
| | o-o-o | |
| |   |   | |
| o---o---o |
|     |     |
o-----o-----o
*/

std::unique_ptr<Board> create_second_phase_board(){
    auto b = std::make_unique<BoardTestable>();
    b->place_pawn(0);
    b->phase = GamePhase::SECOND_PHASE;
    return b;
}

std::unique_ptr<Board> transform_second_to_third_stage_board(std::unique_ptr<Board> board){

    return board;
}

TEST(BoardPhase2Should, ){
    auto b = create_second_phase_board();
    ASSERT_EQ(GamePhase::SECOND_PHASE, b->get_phase());
}

