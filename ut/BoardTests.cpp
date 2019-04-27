#include "gtest/gtest.h"
#include "../src/game/Board.hpp"

TEST(BoardShould, beCreated){
    Board b;
}

TEST(BoardShould, hasFirstPhaseOnCreation){
    Board b;
    ASSERT_EQ(b.getPhase(), GamePhase::FIRST_PHASE);
}

TEST(BoardShould, have21EmptyFieldsOnCreation){
    Board b;
    ASSERT_EQ(b.getField(0), Field::EMPTY);
    ASSERT_EQ(b.getField(20), Field::EMPTY);
}

//TODO
//TEST(BoardShould, advancePhase){}
