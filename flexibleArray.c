#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t size;
  size_t capacity;
  char data[]; // flexible array members
} VHeader;

typedef VHeader *Vector;

[[gnu::always_inline]]
static inline size_t vec_size(const void *data) {
  if (data == nullptr)
    return 0;
  const Vector header = (Vector)data;
  return header[-1].size;
}

[[gnu::always_inline]]
static inline size_t vec_cap(const void *data) {
  if (data == nullptr)
    return 0U;
  const Vector header = (Vector)data;
  return header[-1].capacity;
}

[[gnu::always_inline]]
static inline void *vec_new(size_t elemSiz, size_t capacity) {
  assert(capacity < UINT64_MAX);
  assert(elemSiz < UINT32_MAX / 100);

  Vector header = (Vector)malloc(elemSiz * capacity + sizeof(VHeader));
  header->capacity = capacity;
  header->size = 0U;
  return &(header[1]);
}

[[gnu::always_inline]]
static inline void vec_realloc(Vector *vec, size_t elemSiz, size_t capacity) {
  assert(capacity < UINT64_MAX);
  assert(elemSiz < UINT32_MAX / 100);

  if (vec == nullptr) {
    *vec = ((Vector)vec_new(elemSiz, capacity)) - 1;
    return;
  }

  size_t size = vec_size((*vec)->data);

  if (vec_cap((*vec)->data) < capacity) {
    *vec = (Vector)realloc(*vec, elemSiz * capacity + sizeof(VHeader));
    (*vec)->capacity = capacity;
    (*vec)->size = size;
  }
}

[[gnu::always_inline]]
static inline void *vec_expand(void *data, size_t elemSiz) {
  Vector header = nullptr;
  if (data == nullptr) {
    header = ((Vector)vec_new(elemSiz, 8)) - 1;
  } else {
    header = ((Vector)data) - 1;
  }

  if (header->size == header->capacity) {
    vec_realloc(&header, elemSiz, header->capacity << 1U);
  }
  header->size++;
  return &(header[1]);
}

#define vec_push_back(vec_, value_)                                            \
  {                                                                            \
    void *_tmp_ = vec_expand((vec_), sizeof(*(vec_)));                         \
    (vec_) = (typeof(vec_))(_tmp_);                                            \
    (vec_)[vec_size(vec_) - 1] = value_;                                       \
  }

#define vec_dealloc(vec_)                                                      \
  {                                                                            \
    Vector _tmp_ = ((Vector)vec) - 1;                                          \
    free(_tmp_);                                                               \
    _tmp_ = nullptr;                                                           \
    vec_ = nullptr;                                                            \
  }

int main(void) {
  // Create a vector
  int *vec = nullptr;

  // store data in vector
  for (size_t i = 0; i < 10; ++i) {
    vec_push_back(vec, i);
  }

  // print it
  uint32_t size = vec_size(vec);
  for (size_t i = 0; i < size; ++i) {
    printf("Value at index %zu: %d\n", i, vec[i]);
  }
  printf("Vector size: %u\n", size);

  for (size_t i = 9; i < 20; ++i) {
    vec_push_back(vec, i);
  }

  size = vec_size(vec);
  for (size_t i = 0; i < size; ++i) {
    printf("Value at index %zu: %d\n", i, vec[i]);
  }

  printf("Vector size: %u\n", size);
  printf("Vector capacity: %zu\n", vec_cap(vec));

  // dealloc vec! manage your memory :)
  vec_dealloc(vec);
  return 0;
}
