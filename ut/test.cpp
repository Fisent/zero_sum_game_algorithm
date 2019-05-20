#include "gtest/gtest.h"
#include <vector>
#include <utility>

#include "BoardFirstPhaseTests.hpp"
#include "BoardSecondPhaseTests.hpp"
#include "EdgeTests.hpp"
#include "BoardEvaluationTests.hpp"
#include "BoardStateMachineTests.hpp"
#include "BoardThirdPhaseTests.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
