#include "permString.hpp"

std::vector<int> findSubstring(std::string s, std::vector<std::string> &words) {

  int32_t wordSize = words[0].size();
  int32_t windowSize = wordSize * words.size();
  int32_t subStrSz = windowSize / wordSize;
  int32_t n = s.size() - windowSize;

  std::vector<int> ans;
  std::vector<std::string> subStr;
  subStr.reserve(subStrSz);

  for (int32_t i = 0; i <= n; i++) {

    subStr.clear();
    for (int32_t j = i; j < i + windowSize; j += wordSize) {
      subStr.push_back(s.substr(j, wordSize));
    }

    if (std::is_permutation(subStr.begin(), subStr.end(), words.begin())) {
      ans.push_back(i);
    }
  }

  return ans;
}
