#define DA_IMPLEMENTATION

#include "da_1.h"
#include <assert.h>

void test_int_array() {
  int *arr = NULL;
  da_Array_push(arr, 1);
  da_Array_push(arr, 2);
  da_Array_push(arr, 3);

  assert(1 == arr[0]);
  assert(2 == arr[1]);
  assert(3 == arr[2]);
}
int main(int argc, char *argv[]) {
  test_int_array();

  return 0;
}
