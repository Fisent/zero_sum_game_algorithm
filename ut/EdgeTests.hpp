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

TEST(EdgeShould, equalToOtherEdgeWithTheSameValuesButOnOtherPlaces){
    Edge first{3, 8};
    Edge second{8, 3};
    ASSERT_EQ(first, second);
}

TEST(EdgeShould, checkIfContainsField){
    Edge e{1, 10};
    ASSERT_TRUE(e.contains(1));
    ASSERT_TRUE(e.contains(10));
    ASSERT_FALSE(e.contains(3));
}

TEST(EdgeShould, getOtherEnd){
    Edge e{3, 7};
    ASSERT_EQ(e.get_other_end(7), 3);
    ASSERT_EQ(e.get_other_end(3), 7);
    ASSERT_EQ(e.get_other_end(5), -1);   
}