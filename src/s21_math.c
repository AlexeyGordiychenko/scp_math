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
      if (s21_fabs(root - n) < s21_epsilon) {
        break;
      }
      n = root;
    }
  } else if (x == 0) {
    root = 0;
  } else {
    root = s21_nan;
  }
  return root;
}

// long double s21_pow(double base, double exp) {}

long double s21_sin(double x) {
  int sign = (x >= 0) ? 1 : -1;

  x = s21_fmod(s21_fabs(x), 2 * my_PI);
  if (x > my_PI) {
    x -= my_PI;
    sign *= -1;
  }
  return result;
}

long double s21_cos(double x) {
  x = s21_fmod(s21_fabs(x), 2 * my_PI);
  int sign = 1;
  if (x > my_PI / 2 && x < 3 * my_PI / 2) {
    sign = -1;
  }
  return sign * s21_sqrt(1 - pow(s21_sin(x), 2));
}

long double s21_log(double x) {
  long double result = 0.0;
  if (x > 0.0) {
    long double guess = x;
    while (1) {
      long double error = s21_exp(guess) - x;

long double s21_fmod(double x, double y) {
  return (long double)(x - y * floor(x / y));
}

int main() {
  printf("%.6Lf\n", s21_sin(-2738.10869));
  printf("%.6f\n\n", sin(-2738.10869));

  printf("%.6Lf\n", s21_cos(67756.23));
  printf("%.6f\n\n", cos(67756.23));

  printf("%.6Lf\n", s21_tan(982.89155));
  printf("%.6f\n\n", tan(982.89155));

  printf("%.6Lf\n", s21_fmod(1342.3574355, 34.56787));
  printf("%.6f\n\n", fmod(1342.3574355, 34.56787));
}