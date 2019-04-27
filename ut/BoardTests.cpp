#include "gtest/gtest.h"
#include "../src/game/Board.hpp"

TEST(BoardShould, beCreated){
    Board b;
}

TEST(BoardShould, hasFirstPhaseOnCreation){
    Board b;
    ASSERT_EQ(b.get_phase(), GamePhase::FIRST_PHASE);
}

TEST(BoardShould, have21EmptyFieldsOnCreation){
    Board b;
    ASSERT_EQ(b.get_field(0), Field::EMPTY);
    ASSERT_EQ(b.get_field(20), Field::EMPTY);
}

TEST(BoardShould, makeProperMove){
    Board b;
    std::cout << getFieldName(b.get_field(0)) << '\n';
    ASSERT_EQ(b.get_field(0), Field::BLACK);
}

//TODO
//TEST(BoardShould, advancePhase){}
