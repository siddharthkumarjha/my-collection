#include "2d-grid.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

// Demonstrate some basic assertions.
TEST(TwoDGridTest, Case1) {
    std::vector<std::vector<int>> cards = {{1, 1, 0}, {3, 0, 0}, {6, 0, 1}, {4, 0, 2}, {5, 2, 0}, {7, 1, 1}, {2, 1, 2}};
    std::vector<std::vector<int>> moves = {{6, 0, 1, 2, 0}};
    int query = 6;

    EXPECT_THAT(solution(cards, moves, query), ElementsAre(2, 0));
}

TEST(TwoDGridTest, Case2) {
    std::vector<std::vector<int>> cards = {{1, 1, 0}, {3, 0, 0}, {6, 0, 1}, {4, 0, 2}, {5, 2, 0}, {7, 1, 1}, {2, 1, 2}};
    std::vector<std::vector<int>> moves = {{6, 0, 1, 2, 0}, {7, 0, 1, 0, 2}};
    int query = 2;

    EXPECT_THAT(solution(cards, moves, query), ElementsAre(2, 2));
}

TEST(TwoDGridTest, Case3) {
    std::vector<std::vector<int>> cards = {{1, 1, 0}, {3, 0, 0}, {6, 0, 1}, {4, 0, 2}, {5, 2, 0}, {7, 1, 1}, {2, 1, 2}};
    std::vector<std::vector<int>> moves = {{6, 0, 1, 3, 0}, {7, 0, 1, 0, 2}};
    int query = 5;

    EXPECT_THAT(solution(cards, moves, query), ElementsAre(2, 0));
}

TEST(TwoDGridTest, Case4) {
    std::vector<std::vector<int>> cards = {{1, 1, 0}, {3, 0, 0}, {6, 0, 1}, {4, 0, 2}, {5, 2, 0}, {7, 1, 1}, {2, 1, 2}};
    std::vector<std::vector<int>> moves = {{1, 1, 0, 2, 0}, {1, 2, 0, 1, 1}, {1, 1, 1, 2, 1}};
    int query = 1;

    EXPECT_THAT(solution(cards, moves, query), ElementsAre(2, 1));
}

TEST(TwoDGridTest, Case5) {
    std::vector<std::vector<int>> cards = {{1, 1, 0}, {3, 0, 0}, {6, 0, 1}, {4, 0, 2}, {5, 2, 0}, {7, 1, 1}, {2, 1, 2}};
    std::vector<std::vector<int>> moves = {{4, 0, 2, 1, 1}, {7, 2, 1, 0, 2}, {1, 0, 1, 2, 1}, {5, 2, 0, 0, 1}, {3, 0, 0, 1, 1}, {2, 0, 2, 1, 0}, {6, 1, 1, 2, 1}};
    int query = 4;

    EXPECT_THAT(solution(cards, moves, query), ElementsAre(1, 1));
}

TEST(TwoDGridTest, Case6) {
    std::vector<std::vector<int>> cards = {{1, 1, 0}, {3, 0, 0}, {6, 0, 1}, {4, 0, 2}, {5, 2, 0}, {7, 1, 1}, {2, 1, 2}};
    std::vector<std::vector<int>> moves = {{3, 0, 0, 0, 1}};
    int query = 3;

    EXPECT_THAT(solution(cards, moves, query), ElementsAre(0, 1));
}