#ifndef DA_H_
#define DA_H_

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#define DA_ARRAY_DEFAULT_CAPABILITY 16

#define da_Array_new(T, ret)                                                   \
  do {                                                                         \
    ret = __da_Array_new(sizeof(T), "" #T);                                    \
  } while (0)

#define da_Array_free(self)                                                    \
  do {                                                                         \
    __da_Array_free(self);                                                     \
    self = NULL;                                                               \
  } while (0)

#define da_Array_push(T, self, elem)                                           \
  do {                                                                         \
    __da_Array_grow(self, self->__elem_size);                                  \
    *(T *)(self->__elems + (self->__count * self->__elem_size)) = elem;        \
    self->__count += 1;                                                        \
  } while (0)

#define da_Array_pop(T, self, ret)                                             \
  do {                                                                         \
    *ret = *(T *)(self->__elems + (self->__count * self->__elem_size));        \
    self->__count -= 1;                                                        \
  } while (0)

#define da_Array_for_each(T, self, elem, body)                                 \
  for (size_t __da_array_index = 0; __da_array_index < self->__count;          \
       __da_array_index++) {                                                   \
    T *elem = self->__elems + (__da_array_index * self->__elem_size);          \
    body;                                                                      \
  }

#define da_Array_at(T, self, index) *(T *)__da_Array_at(self, index)

typedef struct {
  size_t __count;
  size_t __capability;
  size_t __elem_size;
  const char *__elem_type;
  void *__elems;
} da_Array;

#define DA_IMPLEMENTATION
#ifdef DA_IMPLEMENTATION

da_Array *__da_Array_new(size_t elem_size, const char *elem_type) {
  da_Array *ret = (da_Array *)malloc(sizeof(da_Array));
  *ret = (da_Array){
      .__count = 0,
      .__elem_size = elem_size,
      .__elem_type = elem_type,
      .__elems = NULL,
  };
  return ret;
}

void __da_Array_grow(da_Array *self, size_t size) {
  size_t old_capability = self->__capability;
  if (self->__capability == 0) {
    self->__capability = DA_ARRAY_DEFAULT_CAPABILITY;
  } else {
    while (self->__capability < self->__count + size) {
      // capability = capability * 1.5
      self->__capability += self->__capability >> 1;
    }
  }
  if (old_capability != self->__capability) {
    self->__elems = realloc(self->__elems, self->__capability);
  }
}

void *__da_Array_at(da_Array *self, size_t index) {
  assert(index < self->__count);
  return self->__elems + (self->__elem_size * index);
}

void __da_Array_free(da_Array *ptr) {
  assert(ptr != NULL);
  free(ptr->__elems);
  free(ptr);
}

#endif // DA_IMPLEMENTATION

#endif // DA_H_
