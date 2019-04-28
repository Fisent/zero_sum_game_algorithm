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
    ASSERT_TRUE(b.place_pawn(0, Field::WHITE));
    ASSERT_EQ(b.get_field(0), Field::WHITE);
}

TEST(BoardShould, notMakeMoveOutOfRange){
    Board b;
    ASSERT_FALSE(b.place_pawn(-1, Field::WHITE));
    ASSERT_FALSE(b.place_pawn(999, Field::WHITE));

    for(int i = 0; i < 24; i++){
        ASSERT_EQ(b.get_field(i), Field::EMPTY);
    }
}

TEST(BoardShould, notMakeMoveWithFieldAsEmpty){
    Board b;
    ASSERT_FALSE(b.place_pawn(0, Field::EMPTY));
}

TEST(BoardShould, notMakeMoveOnOccupiedField){
    Board b;
    b.place_pawn(0, Field::WHITE);
    b.place_pawn(1, Field::BLACK);
    ASSERT_FALSE(b.place_pawn(1, Field::WHITE));
    b.place_pawn(3, Field::WHITE);
    ASSERT_FALSE(b.place_pawn(0, Field::BLACK));
}

TEST(BoardShould, notGoToNextPhasePrematurely){
    Board b;
    for(int i = 0; i < 16; i+=2){
        b.place_pawn(i, Field::WHITE);
        b.place_pawn(i + 1, Field::BLACK);
    }
    ASSERT_EQ(b.get_phase(), GamePhase::FIRST_PHASE);
}

TEST(BoardShould, startWithWhitePlayerMove){
    Board b;
    ASSERT_FALSE(b.place_pawn(0, Field::BLACK));
    ASSERT_TRUE(b.place_pawn(0, Field::WHITE));
    ASSERT_EQ(b.get_field(0), Field::WHITE);
}

TEST(BoardShould, notAllowOnePlayerToMoveTwice){
    Board b;
    ASSERT_TRUE(b.place_pawn(0, Field::WHITE));
    ASSERT_FALSE(b.place_pawn(1, Field::WHITE));
    b.place_pawn(2, Field::BLACK);
    ASSERT_TRUE(b.place_pawn(1, Field::WHITE));
}
