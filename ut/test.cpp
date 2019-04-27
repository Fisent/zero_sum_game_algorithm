#include "gtest/gtest.h"
#include <vector>
#include <utility>

#include "BoardTests.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
