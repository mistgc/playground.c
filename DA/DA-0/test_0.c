#define DA_IMPLEMENTATION
#include "da_0.h"
#include <stdio.h>
#include <stdlib.h>

void test_int_arr() {
  da_Array *int_arr = NULL;
  da_Array_new(int, int_arr);

  da_Array_push(int, int_arr, 1);
  da_Array_push(int, int_arr, 2);
  da_Array_push(int, int_arr, 3);

  da_Array_for_each(int, int_arr, elem, { *elem += 1; });
  da_Array_free(int_arr);
}

void test_float_arr() {
  da_Array *float_arr = NULL;
  da_Array_new(float, float_arr);

  da_Array_push(float, float_arr, 1.);
  da_Array_push(float, float_arr, 2.);
  da_Array_push(float, float_arr, 3.);

  da_Array_for_each(float, float_arr, elem, { *elem += 1.; });
  da_Array_free(float_arr);
}

void test_at() {
  da_Array *arr = NULL;
  da_Array_new(int, arr);

  da_Array_push(int, arr, 1);
  da_Array_push(int, arr, 2);
  da_Array_push(int, arr, 3);

  assert(1 == da_Array_at(int, arr, 0));
  assert(2 == da_Array_at(int, arr, 1));
  assert(3 == da_Array_at(int, arr, 2));
}

int main(int argc, char *argv[]) {
  test_int_arr();
  test_float_arr();
  test_at();

  return 0;
}
