#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

typedef struct {
  size_t size;
  size_t capacity;
  char data[]; // flexible array members
} Header__;

typedef Header__ *Vector;

inline size_t vecSize(const void *data) {
  if (data == nullptr)
    return 0;
  const Vector header = (Vector)data;
  return header[-1].size;
}

inline size_t vecCap(const void *data) {
  if (data == nullptr)
    return 0U;
  const Vector header = (Vector)data;
  return header[-1].capacity;
}

static inline Vector vec_new__(size_t elemSiz, size_t capacity) {
  assert(capacity < UINT32_MAX);
  assert(elemSiz < UINT32_MAX / 100);

  Vector header = (Vector)malloc(elemSiz * capacity + sizeof(Header__));
  header->capacity = (uint32_t)capacity;
  header->size = 0U;
  return header;
}

static inline Vector vec_realloc__(Vector vec, size_t elemSiz,
                                   size_t capacity) {
  assert(capacity < UINT32_MAX);
  assert(elemSiz < UINT32_MAX / 100);
  if (vec == nullptr) {
    return vec_new__(elemSiz, capacity);
  }

  uint32_t size = vecSize(vec->data);

  Vector header = (Vector)realloc(vec, elemSiz * capacity + sizeof(Header__));
  header->capacity = (uint32_t)capacity;
  header->size = size;

  return header;
}

int main(void) {
  // Create a vector
  size_t elemSize = sizeof(int);
  size_t capacity = 10;
  Vector vec = vec_new__(elemSize, capacity);

  // store data in vector
  int *data = (int *)vec->data;
  for (size_t i = 0; i < capacity; ++i) {
    data[i] = i;
    vec->size++;
  }

  // print it
  uint32_t size = vecSize(data);
  for (size_t i = 0; i < size; ++i) {
    printf("Value at index %zu: %d\n", i, data[i]);
  }
  printf("Vector size: %u\n", size);

  // Reallocate vector
  vec = vec_realloc__(vec, elemSize, 20);
  data = (int *)vec->data;

  capacity = vecCap(data);
  for (size_t i = 10; i < capacity; ++i) {
    data[i] = i;
    vec->size++;
  }

  size = vecSize(data);
  for (size_t i = 0; i < size; ++i) {
    printf("Value at index %zu: %d\n", i, data[i]);
  }

  printf("Vector size: %u\n", size);

  free(vec);
  return 0;
}
