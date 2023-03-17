#include <stdio.h>
#include <stdlib.h>

/*
 * Delete the duplicate elements in an array.
 */
void unique(int *arr, size_t *arr_size) {
  size_t size = *arr_size;
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (arr[i] == arr[j]) {
        for (int k = j; k < size; k++) {
          arr[k] = arr[k + 1];
        }
        size--;
        j--;
      }
    }
  }
  *arr_size = size;
}

int arr[] = {1, 1, 1, 3, 3, 2, 3, 5, 9, 1, 4, 2, 8, 2, 8, 4, 6, 6, 7};

int main(int argc, char *argv[]) {

  size_t arr_size = sizeof(arr) / sizeof(arr[0]);

  for (int i = 0; i < arr_size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  unique(arr, &arr_size);

  for (int i = 0; i < arr_size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
