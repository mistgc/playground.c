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

void test_map_array() {
#define PI 3.14159265
#define E 2.7
  int *arr = NULL;
  da_Array_push(arr, 1);
  da_Array_push(arr, 2);
  da_Array_push(arr, 3);

  float *float_arr = NULL;
  da_Array_map(arr, float_arr, item, (item * 2. * PI));

  assert((int)(2. * PI * 100000) == (int)(float_arr[0] * 100000));
  assert((int)(4. * PI * 100000) == (int)(float_arr[1] * 100000));
  assert((int)(6. * PI * 100000) == (int)(float_arr[2] * 100000));

  double *double_arr = NULL;
  da_Array_map(arr, double_arr, item, (item * item * E));

  assert((int)(1. * E * 10000) == (int)(double_arr[0] * 10000));
  assert((int)(4. * E * 10000) == (int)(double_arr[1] * 10000));
  assert((int)(9. * E * 10000) == (int)(double_arr[2] * 10000));

  da_Array_free(arr);
  da_Array_free(float_arr);
  da_Array_free(double_arr);
#undef E
#undef PI
}

int main(int argc, char *argv[]) {
  test_int_array();
  test_float_array();
  test_map_array();

  printf("done!\n");

  return 0;
}
