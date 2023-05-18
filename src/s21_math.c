#include "s21_math.h"

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
  if (0 <= compare_float(x, s21_PI)) {
    do {
      x -= s21_PI;
    } while (0 <= compare_float(x, s21_PI));
  }

  if ((0 <= compare_float(x, s21_PI)) && (-1 == compare_float(x, s21_PI))) {
    x -= s21_PI;
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

long double s21_sin(double x) { return s21_cos(x - s21_PI); }

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
    root = s21_NAN;
  }
  return root;
}

// long double s21_pow(double base, double exp) {}
