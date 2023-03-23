#ifndef DA_H_
#define DA_H_

#include <stdlib.h>

#define DA_REALLOC(p, s) realloc(p, s)
#define DA_FREE(p) free(p)

#define DA_HEADER(arr) ((da_Array_header *)(arr)-1)

#define da_Array_push(arr, val)                                                \
  (da_Array_maybe_grow(arr, 1), (arr)[DA_HEADER(arr)->length++] = (val))
// TODO:
// #define da_Array_pop(arr)
// #define da_Array_del(arr, i)
// #define da_Array_ins(arr, i, v)
// #define da_Array_last(arr)
// #define da_Array_free(arr)
#define da_Array_maybe_grow(arr, size)                                         \
  ((!(arr) || DA_HEADER(arr)->length + (size) > DA_HEADER(arr)->capacity)      \
       ? (da_Array_grow(arr, size, 0))                                         \
       : 0)
#define da_Array_grow(arr, size, min_cap)                                      \
  ((arr) = da_Array_growf((arr), sizeof *(arr), (size), (min_cap)))
#define da_Array_len(arr) ((arr) ? DA_HEADER(arr)->length : 0)
#define da_Array_cap(arr) ((arr) ? DA_HEADER(arr)->capacity : 0)

typedef struct {
  size_t length;
  size_t capacity;
} da_Array_header;

#ifdef DA_IMPLEMENTATION

#define DA_ARRAY_DEFAULT_CAPACITY 4

void *da_Array_growf(void *arr, size_t elem_size, size_t add_len,
                     size_t min_cap) {
  void *new_arr = NULL;
  size_t min_len = da_Array_len(arr) + add_len;

  if (min_len > min_cap) {
    min_cap = min_len;
  }

  if (min_cap < da_Array_cap(arr)) {
    return arr;
  }

  if (min_cap < 2 * da_Array_cap(arr)) {
    min_cap = 2 * da_Array_cap(arr);
  } else {
    min_cap = DA_ARRAY_DEFAULT_CAPACITY;
  }

  new_arr = DA_REALLOC((arr) ? DA_HEADER(arr) : NULL,
                       elem_size * min_cap + sizeof(da_Array_header));
  new_arr = (char *)new_arr + sizeof(da_Array_header);
  if (arr == NULL) {
    DA_HEADER(new_arr)->length = 0;
  }

  DA_HEADER(new_arr)->capacity = min_cap;

  return new_arr;
}

#endif // DA_IMPLEMENTATION

#endif // DA_H_
