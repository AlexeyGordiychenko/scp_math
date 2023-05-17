#include "s21_math.h"

#include <stdio.h>
int s21_abs(int x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}

long double s21_fabs(double x) {
  if (x < 0.0) {
    x *= -1.0;
  }
  return (long double)x;
}

long double s21_sqrt(double x) {
  long double n = x;
  long double root;

  if (x > 0) {
    while (1) {
      root = 0.5 * (n + (x / n));
      if (s21_fabs(root - n) < 0.000000000000001) {
        break;
      }
      n = root;
    }
  } else if (x == 0) {
    root = 0;
  } else {
    root = my_nan;
  }
  return root;
}

long double s21_pow(double base, double exp) {}
