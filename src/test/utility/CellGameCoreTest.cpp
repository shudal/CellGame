//
// Created by perci on 2020/5/21.
//

#include <src/utility/CellGameCore.h>
#include <vector>
#include "gtest/gtest.h"
TEST(CellGameCoreTest, SampleTest) {
    CellGameCore core;
    std::vector<std::vector<int>> vs;
    vs.push_back(std::vector<int> {1,1,1});
    vs.push_back(std::vector<int> {0,0,0});
    vs.push_back(std::vector<int> {0,0,0});
    std::vector<std::vector<int>> vs2 = core.process(vs);

    ASSERT_EQ(vs2[0][0], 0);
    ASSERT_EQ(vs2[0][1], 1);
    ASSERT_EQ(vs2[0][2], 0);
    ASSERT_EQ(vs2[1][1], 1);

    return;
}

TEST(CellGameCoreTest, SampleTest2) {
    CellGameCore core;
    std::vector<std::vector<int>> vs;
    vs.push_back(std::vector<int> {1,0,0});
    vs.push_back(std::vector<int> {0,1,0});
    vs.push_back(std::vector<int> {0,0,1});
    std::vector<std::vector<int>> vs2 = core.process(vs);

    ASSERT_EQ(vs2[0][0], 0);
    ASSERT_EQ(vs2[0][1], 0);
    ASSERT_EQ(vs2[0][2], 0);
    ASSERT_EQ(vs2[1][1], 1);
}
