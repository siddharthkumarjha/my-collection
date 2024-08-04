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
  assert(elemSiz < UINT32_MAX / 100);

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

#define vec_back(vec_) (vec_[vec_size(vec_) - 1])
#define vec_front(vec_) (vec_[0])
#define vec_empty(vec_) (vec_size(vec_) == 0)
#define vec_max_size UINT64_MAX

#define vec_reserve(vec_, cap_)                                                \
  {                                                                            \
    if (vec_ == nullptr)                                                       \
      vec_ = (typeof(vec_))vec_new(sizeof(*(vec_)), (cap_));                   \
    else {                                                                     \
      Vector _tmp_ = ((Vector)vec_) - 1;                                       \
      vec_realloc(&_tmp_, sizeof(*(vec_)), cap_);                              \
    }                                                                          \
  }

#define vec_insert_at(vec_, pos_, data_)                                       \
  {                                                                            \
    if (pos_ >= 0U) {                                                          \
      void *_tmp_ = vec_expand((vec_), sizeof(*(vec_)));                       \
      (vec_) = (typeof(vec_))(_tmp_);                                          \
      size_t bkIdx = vec_size(vec_) - 1;                                       \
      for (; bkIdx > pos_; bkIdx--) {                                          \
        (vec_)[bkIdx] = (vec_)[bkIdx - 1];                                     \
      }                                                                        \
      (vec_)[pos_] = data_;                                                    \
    }                                                                          \
  }

int main(void) {
  // Create a vector
  double *vec = nullptr;
  vec_reserve(vec, 22);

  // store data in vector
  for (size_t i = 0; i < 10; ++i) {
    vec_push_back(vec, i * 0.05);
  }

  // print it
  size_t size = vec_size(vec);
  for (size_t i = 0; i < size; ++i) {
    printf("Value at index %zu: %f\n", i, vec[i]);
  }
  printf("Vector size: %zu\n", size);

  for (size_t i = 9; i < 20; ++i) {
    vec_push_back(vec, i);
  }

  vec_insert_at(vec, 10, -100.0008);
  size = vec_size(vec);
  for (size_t i = 0; i < size; ++i) {
    printf("Value at index %zu: %f\n", i, vec[i]);
  }

  vec_insert_at(vec, 0, -10.8);

  printf("Vector size: %zu\n", vec_size(vec));
  printf("Vector capacity: %zu\n", vec_cap(vec));
  printf("with first %f and last %f elements respectively\n", vec_front(vec),
         vec_back(vec));

  // dealloc vec! manage your memory :)
  vec_dealloc(vec);
  return 0;
}
