#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t len;
  size_t elem_size;
  void *elems;
} Vec;

typedef void *(*Vec_reduce_callback)(const void *prev, const void *curr);

Vec *Vec_new(size_t len, size_t elem_size) {
  Vec *v = (Vec *)malloc(sizeof(Vec));
  *v = (Vec){
      .len = len,
      .elem_size = elem_size,
      .elems = malloc(len * elem_size),
  };
  return v;
};

void Vec_set_value(Vec *self, void *value, size_t index) {
  assert(self->len > index);
  memcpy(self->elems + (index * self->elem_size), value, self->elem_size);
}

Vec *Vec_from_array(void *arr, size_t elem_size, size_t arr_len) {
  Vec *v = Vec_new(arr_len, elem_size);
  for (int i = 0; i < arr_len; i++) {
    Vec_set_value(v, arr + (i * elem_size), i);
  }
  return v;
}

void Vec_free(Vec *self) {
  if (self->len > 0 && self->elems != NULL) {
    free(self->elems);
  }
}

void *_Vec_reduce(const Vec *self, Vec_reduce_callback callback,
                  void *init_value, size_t i) {
  if (i >= self->len) {
    return init_value;
  }
  void *ret = callback(init_value, self->elems + (i * self->elem_size));
  if (init_value != NULL) {
    free(init_value);
  }
  return _Vec_reduce(self, callback, ret, i + 1);
}

void *Vec_reduce(const Vec *self, Vec_reduce_callback callback,
                 void *init_value) {
  void *ret = callback(init_value, self->elems);
  return _Vec_reduce(self, callback, ret, 1);
}
