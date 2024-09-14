#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <random>

using rng = std::independent_bits_engine<std::mt19937, 8U, uint8_t>;
struct ByteBuffer {
  uint8_t BufferSize;
  uint8_t ByteBuffer[64];
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::printf("Usage: %s <len>\n", argv[0]);
    return 1;
  }

  struct ByteBuffer bb;
  int len = atoi(argv[1]);

  if (len < 65) {
    bb.BufferSize = static_cast<uint8_t>(len);
  } else {
    std::printf("Error: len %d given too big!!\n\tMax len allowed %hhu", len,
                64);
    return 2;
  }

  std::printf("recvd len: %d\n", len);

  if (bb.BufferSize < 65U) {
    rng gen;
    gen.seed(std::time(nullptr));
    std::generate(bb.ByteBuffer, bb.ByteBuffer + bb.BufferSize, gen);

    for (uint8_t i = 0; i < bb.BufferSize; i++) {
      std::printf("i: %2hhu | %2hhx \n", i + 1, *(bb.ByteBuffer + i));
    }
  } else {
    std::printf("Error: invalid length not storing");
  }
  return 0;
}
