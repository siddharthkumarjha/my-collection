#include <cstdio>
#include <cstring>

#define __FILENAME__                                                           \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

int main(void) {
  std::printf("[%s:%d]\n", __FILENAME__, __LINE__);
  return 0;
}
