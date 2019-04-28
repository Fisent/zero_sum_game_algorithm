#include "gtest/gtest.h"

#include "../src/game/Edge.hpp"

TEST(EdgeShould, beCreated){
    Edge e{0, 1};
}

TEST(EdgeShould, connectTwoFields){
    Edge e{0, 1};
    ASSERT_TRUE(e.connects(0, 1));
}

TEST(EdgeShould, checkConnectionBeetwenFieldsAlsoTheOtherWay){
    Edge e{3, 8};
    ASSERT_TRUE(e.connects(3, 8));
    ASSERT_TRUE(e.connects(8, 3));

}