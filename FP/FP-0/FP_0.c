#include "FP_0.h"

/************
 * int array
 ************/

void *vec_add_int_handler(const void *a, const void *b) {
  int *ret = (int *)malloc(sizeof(int));
  *ret = *(int *)a + *(int *)b;
  return ret;
}

void *vec_mult_int_handler(const void *a, const void *b) {
  int *ret = (int *)malloc(sizeof(int));
  *ret = *(int *)a * *(int *)b;
  return ret;
}

int sum_int(int arr[], size_t arr_len) {
  Vec *v = Vec_from_array(arr, sizeof(int), arr_len);
  int *init_value = (int *)malloc(sizeof(int));
  *init_value = 0;
  int *pret = (int *)Vec_reduce(v, vec_add_int_handler, init_value);
  int ret = *pret;
  free(pret);
  free(init_value);
  Vec_free(v);
  v = NULL;
  return ret;
}

int factorial_int(int arr[], size_t arr_len) {
  Vec *v = Vec_from_array(arr, sizeof(int), arr_len);
  int *init_value = (int *)malloc(sizeof(int));
  *init_value = 1;
  int *pret = (int *)Vec_reduce(v, vec_mult_int_handler, init_value);
  int ret = *pret;
  free(pret);
  free(init_value);
  Vec_free(v);
  v = NULL;
  return ret;
}

/************
 * float array
 ************/

void *vec_add_float_handler(const void *a, const void *b) {
  float *ret = (float *)malloc(sizeof(float));
  *ret = *(float *)a + *(float *)b;
  return ret;
}

float sum_float(float arr[], size_t arr_len) {
  Vec *v = Vec_from_array(arr, sizeof(float), arr_len);
  float *init_value = (float *)malloc(sizeof(float));
  *init_value = 0.;
  float *pret = (float *)Vec_reduce(v, vec_add_float_handler, init_value);
  float ret = *pret;
  free(pret);
  free(init_value);
  Vec_free(v);
  v = NULL;
  return ret;
}

int main(int argc, char *argv[]) {
  int int_arr[] = {1, 2, 3, 4, 5};
  printf("sum_int = %d\n",
         sum_int(int_arr, sizeof(int_arr) / sizeof(int_arr[0])));
  printf("factorial_int = %d\n",
         factorial_int(int_arr, sizeof(int_arr) / sizeof(int_arr[0])));

  float float_arr[] = {1.0, 1.0, 2.0, 2.0};
  printf("sum_float = %f\n",
         sum_float(float_arr, sizeof(float_arr) / sizeof(float_arr[0])));
  return 0;
}
