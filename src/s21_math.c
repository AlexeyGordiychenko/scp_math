#include "s21_math.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int compare_float(double f1, double f2) {
  double precision = 0.00000000000000000001;
  if ((f1 - precision) < f2)
    return -1;
  else if ((f1 + precision) > f2)
    return 1;
  else
    return 0;
}

long double s21_cos(double x) {
  if (x < 0.0f) x = -x;
  if (0 <= compare_float(x, M_PI)) {
    do {
      x -= M_PI;
    } while (0 <= compare_float(x, M_PI));
  }

  if ((0 <= compare_float(x, M_PI)) && (-1 == compare_float(x, M_PI))) {
    x -= M_PI;
    return (long double)((-1) *
                         (1.0f -
                          (x * x / 2.0f) *
                              (1.0f -
                               (x * x / 12.0f) *
                                   (1.0f -
                                    (x * x / 30.0f) *
                                        (1.0f -
                                         (x * x / 56.0f) *
                                             (1.0f -
                                              (x * x / 90.0f) *
                                                  (1.0f -
                                                   (x * x / 132.0f) *
                                                       (1.0f - (x * x /
                                                                182.0f)))))))));
  }
  return (
      long double)(1.0f -
                   (x * x / 2.0f) *
                       (1.0f -
                        (x * x / 12.0f) *
                            (1.0f -
                             (x * x / 30.0f) *
                                 (1.0f -
                                  (x * x / 56.0f) *
                                      (1.0f -
                                       (x * x / 90.0f) *
                                           (1.0f -
                                            (x * x / 132.0f) *
                                                (1.0f - (x * x / 182.0f))))))));
}

double s21_sin(double x) { return s21_cos(x - M_PI); }
#include "s21_math.h"

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
      if (s21_fabs(root - n) < 0.0000000000000001) {
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

int main() {
  printf("%Lf\n", s21_cos(12.355));
  printf("%f", cos(12.355));
  printf("\n\n%f", M_PI);
  printf("\n\n%LF", (long double) 103993/33102);
}