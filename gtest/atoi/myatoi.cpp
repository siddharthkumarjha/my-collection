#include "myatoi.hpp"
#include <cstdint>

int myAtoi(string s) {
  size_t n = s.size();
  size_t i = 0;
  while (i < n) {
    if (s[i] != ' ')
      break;
    i++;
  }

  bool posSign = true;
  if (s[i] == '-')
    posSign = false;
  if (s[i] == '-' || s[i] == '+')
    i++;

  while (i < n) {
    if (s[i] != '0')
      break;
    i++;
  }

  uint32_t res = 0;
  constexpr const uint32_t max = (static_cast<uint32_t>(INT_MAX) + 1U) / 10;
  constexpr const uint32_t max__ = static_cast<uint32_t>(INT_MAX) + 1U;

  bool overflow = false;

  while (i < n) {
    if (res > max) {
      overflow = true;
      break;
    }

    if (s[i] >= '0' && s[i] <= '9')
      res = (res * 10) + (s[i] - '0');
    else
      break;

    i++;
  }

  if (i < n && !(s[i] >= '0' && s[i] <= '9'))
    overflow = false;

  if (res == 0U)
    return 0;

  if (posSign && !overflow && res < INT_MAX)
    return static_cast<int32_t>(res);
  else if (posSign)
    return INT_MAX;
  else if (!posSign && !overflow && res < max__)
    return static_cast<int32_t>((UINT32_MAX * res));
  return INT_MIN;
}
