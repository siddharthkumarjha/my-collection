#include "minWindowSubstr.hpp"
#include <algorithm>
std::string minWindow(std::string s, std::string t) {
  int32_t windowSize = t.size();
  int32_t n = s.size();

  std::sort(t.begin(), t.end());

  while (windowSize <= n) {
    for (int32_t j = 0; j <= n - windowSize; j++) {
      std::string subStr = s.substr(j, windowSize);
      std::sort(subStr.begin(), subStr.end());

      bool contained = std::ranges::includes(subStr.begin(), subStr.end(),
                                             t.begin(), t.end());
      if (contained) {
        return s.substr(j, windowSize);
      }
    }
    windowSize++;
  }

  return "";
}
