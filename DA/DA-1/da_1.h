#ifndef DA_H_
#define DA_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DA_REALLOC(p, s) realloc(p, s)
#define DA_FREE(p) free(p)

#define DA_HEADER(arr) ((da_Array_header *)(arr)-1)

#define da_Array_push(arr, val)                                                \
  (da_Array_maybe_grow(arr, 1), (arr)[DA_HEADER(arr)->length++] = (val))
#define da_Array_pop(arr)                                                      \
  (DA_HEADER(arr)->length--, (arr)[DA_HEADER(arr)->length])
#define da_Array_last(arr) ((arr)[DA_HEADER(arr)->length - 1])
#define da_Array_free(arr)                                                     \
  ((void)((arr) ? DA_FREE(DA_HEADER(arr)) : (void)0), (arr) = NULL)
#define da_Array_del(arr, i) da_Array_deln(arr, i, 1)
#define da_Array_deln(arr, i, n)                                               \
  (memmove(&(arr)[i], &(arr)[i + n],                                           \
           sizeof *(arr) * (DA_HEADER(arr)->length - n - (i))),                \
   DA_HEADER(arr)->length -= (n))
#define da_Array_ins(arr, i, v) (da_Array_insn(arr, i, 1), arr[i] = (v))
#define da_Array_insn(arr, i, n)                                               \
  (da_Array_addn(arr, n),                                                      \
   memmove(&(arr)[i + n], &(arr)[i],                                           \
           sizeof *(arr) * (DA_HEADER(arr)->length - (n) - (i))))
#define da_Array_addn(arr, n) ((void)da_Array_addn_index(arr, n))
#define da_Array_addn_index(arr, n)                                            \
  (da_Array_maybe_grow(arr, n),                                                \
   (n) ? (DA_HEADER(arr)->length += (n), DA_HEADER(arr)->length - (n))         \
       : da_Array_len(arr))
#define da_Array_maybe_grow(arr, size)                                         \
  ((!(arr) || DA_HEADER(arr)->length + (size) > DA_HEADER(arr)->capacity)      \
       ? (da_Array_grow(arr, size, 0))                                         \
       : 0)
#define da_Array_grow(arr, size, min_cap)                                      \
  ((arr) = da_Array_growf((arr), sizeof *(arr), (size), (min_cap)))
#define da_Array_len(arr) ((arr) ? (ptrdiff_t)DA_HEADER(arr)->length : 0)
#define da_Array_cap(arr) ((arr) ? DA_HEADER(arr)->capacity : 0)
#define da_Array_map(arr, new_arr, item, body)                                 \
  do {                                                                         \
    size_t arr##__length = da_Array_len(arr);                                  \
    for (size_t arr##__i = 0; arr##__i < arr##__length; arr##__i++) {          \
      typeof(*new_arr) new_arr##__item;                                        \
      typeof(*arr) item = arr[arr##__i];                                       \
      new_arr##__item = (body);                                                \
      da_Array_push(new_arr, new_arr##__item);                                 \
    }                                                                          \
  } while (0)
#define da_Array_filter(arr, new_arr, item, body)                              \
  do {                                                                         \
    size_t arr##__length = da_Array_len(arr);                                  \
    for (size_t arr##__i = 0; arr##__i < arr##__length; arr##__i++) {          \
      typeof(*arr) item = arr[arr##__i];                                       \
      if ((body)) {                                                            \
        da_Array_push(new_arr, item);                                          \
      }                                                                        \
    }                                                                          \
  } while (0)

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
