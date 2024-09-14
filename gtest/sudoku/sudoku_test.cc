#include "sudoku.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SUDOKU_TEST, Case1) {
  vector<vector<char>> board = std::vector<std::vector<char>>(
      {std::vector<char>({'5', '3', '.', '.', '7', '.', '.', '.', '.'}),
       std::vector<char>({'6', '.', '.', '1', '9', '5', '.', '.', '.'}),
       std::vector<char>({'.', '9', '8', '.', '.', '.', '.', '6', '.'}),
       std::vector<char>({'8', '.', '.', '.', '6', '.', '.', '.', '3'}),
       std::vector<char>({'4', '.', '.', '8', '.', '3', '.', '.', '1'}),
       std::vector<char>({'7', '.', '.', '.', '2', '.', '.', '.', '6'}),
       std::vector<char>({'.', '6', '.', '.', '.', '.', '2', '8', '.'}),
       std::vector<char>({'.', '.', '.', '4', '1', '9', '.', '.', '5'}),
       std::vector<char>({'.', '.', '.', '.', '8', '.', '.', '7', '9'})});

  EXPECT_EQ(isValidSudoku(board), true);
}

TEST(SUDOKU_TEST, Case2) {
  vector<vector<char>> board = std::vector<std::vector<char>>(
      {std::vector<char>({'8', '3', '.', '.', '7', '.', '.', '.', '.'}),
       std::vector<char>({'6', '.', '.', '1', '9', '5', '.', '.', '.'}),
       std::vector<char>({'.', '9', '8', '.', '.', '.', '.', '6', '.'}),
       std::vector<char>({'8', '.', '.', '.', '6', '.', '.', '.', '3'}),
       std::vector<char>({'4', '.', '.', '8', '.', '3', '.', '.', '1'}),
       std::vector<char>({'7', '.', '.', '.', '2', '.', '.', '.', '6'}),
       std::vector<char>({'.', '6', '.', '.', '.', '.', '2', '8', '.'}),
       std::vector<char>({'.', '.', '.', '4', '1', '9', '.', '.', '5'}),
       std::vector<char>({'.', '.', '.', '.', '8', '.', '.', '7', '9'})});
  EXPECT_EQ(isValidSudoku(board), false);
}

TEST(SUDOKU_TEST, Case3) {
  std::string str = "barfoofoobarthefoobarman";
  std::vector<std::string> arr = {"bar", "foo", "the"};

  vector<vector<char>> board = std::vector<std::vector<char>>(
      {std::vector<char>({'.', '.', '.', '.', '5', '.', '.', '1', '.'}),
       std::vector<char>({'.', '4', '.', '3', '.', '.', '.', '.', '.'}),
       std::vector<char>({'.', '.', '.', '.', '.', '3', '.', '.', '1'}),
       std::vector<char>({'8', '.', '.', '.', '.', '.', '.', '2', '.'}),
       std::vector<char>({'.', '.', '2', '.', '7', '.', '.', '.', '.'}),
       std::vector<char>({'.', '1', '5', '.', '.', '.', '.', '.', '.'}),
       std::vector<char>({'.', '.', '.', '.', '.', '2', '.', '.', '.'}),
       std::vector<char>({'.', '2', '.', '9', '.', '.', '.', '.', '.'}),
       std::vector<char>({'.', '.', '4', '.', '.', '.', '.', '.', '.'})});
  EXPECT_EQ(isValidSudoku(board), false);
}
