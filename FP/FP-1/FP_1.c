#include "FP_1.h"

void int_add(const void *a, const void *b, const void *ret) {
  *(int *)ret = *(int *)a + *(int *)b;
}

void int_mult(const void *a, const void *b, const void *ret) {
  *(int *)ret = *(int *)a * *(int *)b;
}

void float_add(const void *a, const void *b, const void *ret) {
  *(float *)ret = *(float *)a + *(float *)b;
}

int int_sum(int arr[], size_t arr_len) {
  Vec *v = Vec_from_array(arr, sizeof(int), arr_len);
  int ret = 0;
  Vec_reduce(v, int_add, &ret);
  Vec_free(v);
  return ret;
}

int int_factorial(int arr[], size_t arr_len) {
  Vec *v = Vec_from_array(arr, sizeof(int), arr_len);
  int ret = 1;
  Vec_reduce(v, int_mult, &ret);
  Vec_free(v);
  return ret;
}

float float_sum(float arr[], size_t arr_len) {
  Vec *v = Vec_from_array(arr, sizeof(float), arr_len);
  float ret = 0;
  Vec_reduce(v, float_add, &ret);
  Vec_free(v);
  return ret;
}

int main(int argc, char *argv[]) {

  int int_arr[] = {1, 2, 3, 4, 5};
  printf("int_sum = %d\n",
         int_sum(int_arr, sizeof(int_arr) / sizeof(int_arr[0])));
  printf("int_sum = %d\n",
         int_factorial(int_arr, sizeof(int_arr) / sizeof(int_arr[0])));

  float float_arr[] = {1.0, 2.0, 3.0, 1.0, 2.0};
  printf("float_sum = %lf\n",
         float_sum(float_arr, sizeof(float_arr) / sizeof(float_arr[0])));
  return EXIT_SUCCESS;
}
