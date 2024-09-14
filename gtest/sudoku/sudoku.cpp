#include "sudoku.hpp"
#include <cstdio>
// Converts A[][] to its transpose
void transpose(vector<vector<char>> &A) {
  constexpr int N = 9;
  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      swap(A[i][j], A[j][i]);
}

bool isValidSudoku(vector<vector<char>> &board) {
  for (const auto &chrarr : board) {
    // compare row
    std::array<uint8_t, 10> hash;
    hash.fill(0);
    for (const auto &chr : chrarr) {
      if (chr >= '0' && chr <= '9' && ++hash[chr - '0'] && hash[chr - '0'] > 1)
        return false;
    }
  }

  for (const auto &chrarr : board) {
    std::printf("[ ");
    for (const auto &chr : chrarr) {
      std::printf("%c, ", chr);
    }
    std::printf("\033[2D ]\n");
  }

  std::printf("=======================================\n");

  transpose(board);

  for (const auto &chrarr : board) {
    std::printf("[ ");
    for (const auto &chr : chrarr) {
      std::printf("%c, ", chr);
    }
    std::printf("\033[2D ]\n");
  }

  for (const auto &chrarr : board) {
    // compare cols
    std::array<uint8_t, 10> hash;
    hash.fill(0);
    for (const auto &chr : chrarr) {
      if (chr >= '0' && chr <= '9' && ++hash[chr - '0'] && hash[chr - '0'] > 1)
        return false;
    }
  }

  return true;
}
