#include "s21_math.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
      if (s21_fabs(root - n) < 0.000001) {
        break;
      }
      n = root;
    }
  } else if (x == 0) {
    root = 0;
  } else {
    root = s21_NAN;
  }
  return root;
}

// long double s21_pow(double base, double exp) {}

long double s21_sin(double x) {
  int sign = (x >= 0) ? 1 : -1;

  x = fmod(s21_fabs(x), 2 * my_PI);
  if (x > my_PI) {
    x -= my_PI;
    sign *= -1;
  }
  if (x > my_PI / 2) x = my_PI - x;

  long double sum = x;
  double t = x;

  for (int n = 3; s21_fabs(t) > eps; n += 2)
    sum += t = -t * x * x / n / (n - 1);

  return sum * sign;
}

long double s21_cos(double x) { return s21_sqrt(1 - pow(s21_sin(x), 2)); }

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

int main() {
  printf("%.6Lf\n", s21_cos(12.355));
  printf("%.6f\n\n", cos(12.355));

  printf("%.6Lf\n", s21_sin(12.355));
  printf("%.6f\n\n", sin(12.355));

  printf("%.6Lf\n", s21_tan(12.355));
  printf("%.6f\n\n", tan(12.355));

  printf("%.6f\n", my_PI);
  printf("%.6f", M_PI);
}