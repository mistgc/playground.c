void mx_matmul(float *xout, float *x, float *w, int n, int d) {
  // W (d,n) @ x (n,) -> xout (d,)
  for (int i = 0; i < d; i++) {
    float val = 0.0f;
    for (int j = 0; j < n; j++) {
      val += w[i * n + j] * x[j];
    }
    xout[i] = val;
  }
}
