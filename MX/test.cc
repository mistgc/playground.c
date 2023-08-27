#include "matmul.h"
#include <iostream>

void test_matmul() {
  float a[] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
  float b[] = {2., 4., 6., 8., 10., 12., 14., 16., 18.};

  int d = 3;
  int n = 3;

  float *out = new float[d];

  mx_matmul(out, a, b, n, d);

  for (auto i = 0; i < d; i++) {
    std::cout << out[i] << " ";
  }

  std::cout << '\n';

  delete[] out;
}

int main() {
  test_matmul();

  return 0;
}
