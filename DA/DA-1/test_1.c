#define DA_IMPLEMENTATION

#include "da_1.h"
#include <assert.h>
#include <stdio.h>

void test_int_array() {
  int *arr = NULL;
  da_Array_push(arr, 1);
  da_Array_push(arr, 2);
  da_Array_push(arr, 3);

  assert(1 == arr[0]);
  assert(2 == arr[1]);
  assert(3 == arr[2]);

  assert(3 == da_Array_len(arr));
  assert(3 == da_Array_last(arr));

  assert(3 == da_Array_pop(arr));

  assert(2 == da_Array_len(arr));
  assert(2 == da_Array_last(arr));

  da_Array_del(arr, 0);

  assert(2 == arr[0]);
  assert(1 == da_Array_len(arr));
  assert(2 == da_Array_last(arr));

  da_Array_ins(arr, 0, 4);
  assert(4 == arr[0]);
  assert(2 == da_Array_len(arr));
  assert(2 == da_Array_last(arr));

  da_Array_free(arr);
  assert(NULL == arr);
}

void test_float_array() {
  float *arr = NULL;
  da_Array_push(arr, 1.);
  da_Array_push(arr, 2.);
  da_Array_push(arr, 3.);

  assert(1. == arr[0]);
  assert(2. == arr[1]);
  assert(3. == arr[2]);

  assert(3. == da_Array_len(arr));
  assert(3. == da_Array_last(arr));

  assert(3. == da_Array_pop(arr));

  assert(2. == da_Array_len(arr));
  assert(2. == da_Array_last(arr));

  da_Array_del(arr, 0);

  assert(2. == arr[0]);
  assert(1. == da_Array_len(arr));
  assert(2. == da_Array_last(arr));

  da_Array_ins(arr, 0, 4);
  assert(4. == arr[0]);
  assert(2. == da_Array_len(arr));
  assert(2. == da_Array_last(arr));

  da_Array_free(arr);
  assert(NULL == arr);
}
int main(int argc, char *argv[]) {
  test_int_array();
  test_float_array();

  return 0;
}
