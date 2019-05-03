#include <memory>
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
    ASSERT_TRUE(b.place_pawn(0));
    ASSERT_EQ(b.get_field(0), Field::WHITE);
}

TEST(BoardShould, notMakeMoveOutOfRange){
    Board b;
    ASSERT_FALSE(b.place_pawn(-1));
    ASSERT_FALSE(b.place_pawn(999));

    for(int i = 0; i < 24; i++){
        ASSERT_EQ(b.get_field(i), Field::EMPTY);
    }
}

TEST(BoardPhase1Should, notMakeMoveOnOccupiedField){
    Board b;
    b.place_pawn(0);
    b.place_pawn(1);
    ASSERT_FALSE(b.place_pawn(1));
    b.place_pawn(3);
    ASSERT_FALSE(b.place_pawn(0));
}

TEST(BoardPhase1Should, notGoToNextPhasePrematurely){
    Board b;
    for(int i = 0; i < 16; i+=2){
        b.place_pawn(i);
        b.place_pawn(i + 1);
    }
    ASSERT_EQ(b.get_phase(), GamePhase::FIRST_PHASE);
}
