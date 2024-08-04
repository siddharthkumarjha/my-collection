#include "myatoi.hpp"
#include <gtest/gtest.h>

TEST(myAtoi, Case1) {
  std::string s = "42";

  auto start = std::chrono::steady_clock::now();
  int res = myAtoi(s);
  auto stop = std::chrono::steady_clock::now();
  auto diff = stop - start;
  std::cout << "Time: " << diff.count() << " | ";

  auto std_start = std::chrono::steady_clock::now();
  int std_res = stoi(s);
  auto std_stop = std::chrono::steady_clock::now();
  auto std_diff = std_stop - std_start;
  std::cout << "Std Time: " << std_diff.count() << '\n';

  EXPECT_EQ(res, 42);
  EXPECT_EQ(std_res, 42);
}

TEST(myAtoi, Case2) {
  std::string s = " -042";

  auto start = std::chrono::steady_clock::now();
  int res = myAtoi(s);
  auto stop = std::chrono::steady_clock::now();
  auto diff = stop - start;
  std::cout << "Time: " << diff.count() << " | ";

  auto std_start = std::chrono::steady_clock::now();
  int std_res = stoi(s);
  auto std_stop = std::chrono::steady_clock::now();
  auto std_diff = std_stop - std_start;
  std::cout << "Std Time: " << std_diff.count() << '\n';

  EXPECT_EQ(res, -42);
  EXPECT_EQ(std_res, -42);
}

TEST(myAtoi, Case3) {
  std::string s = "1337c0d3";

  auto start = std::chrono::steady_clock::now();
  int res = myAtoi(s);
  auto stop = std::chrono::steady_clock::now();
  auto diff = stop - start;
  std::cout << "Time: " << diff.count() << " | ";

  auto std_start = std::chrono::steady_clock::now();
  int std_res = stoi(s);
  auto std_stop = std::chrono::steady_clock::now();
  auto std_diff = std_stop - std_start;
  std::cout << "Std Time: " << std_diff.count() << '\n';

  EXPECT_EQ(res, 1337);
  EXPECT_EQ(std_res, 1337);
}

TEST(myAtoi, Case4) {
  std::string s = "0-1";

  auto start = std::chrono::steady_clock::now();
  int res = myAtoi(s);
  auto stop = std::chrono::steady_clock::now();
  auto diff = stop - start;
  std::cout << "Time: " << diff.count() << " | ";

  auto std_start = std::chrono::steady_clock::now();
  int std_res = stoi(s);
  auto std_stop = std::chrono::steady_clock::now();
  auto std_diff = std_stop - std_start;
  std::cout << "Std Time: " << std_diff.count() << '\n';

  EXPECT_EQ(res, 0);
  EXPECT_EQ(std_res, 0);
}

TEST(myAtoi, Case5) {
  std::string s = "words and 987";

  auto start = std::chrono::steady_clock::now();
  int res = myAtoi(s);
  auto stop = std::chrono::steady_clock::now();
  auto diff = stop - start;
  std::cout << "Time: " << diff.count() << " | ";

  int std_res = 0;
  auto std_start = std::chrono::steady_clock::now();
  try {
    std_res = stoi(s);
  } catch (exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
  }
  auto std_stop = std::chrono::steady_clock::now();
  auto std_diff = std_stop - std_start;
  std::cout << "Std Time: " << std_diff.count() << '\n';

  EXPECT_EQ(res, 0);
  EXPECT_EQ(std_res, 0);
}
