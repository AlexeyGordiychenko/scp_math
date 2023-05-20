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
      if (s21_fabs(root - n) < s21_EPSILON) {
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

long double s21_pow(double base, double exp) {
  long double result = 1.0;
  result = s21_exp(exp * s21_log(base));
  return result;
}

long double s21_exp(double x) {
  long double result = 1.0;
  if (x == 1.0) {
    result = 1.0;
  } else if (x == 0.0) {
    result = 0.0;
  } else {
    long double term = 1.0;
    for (int i = 1; s21_fabs(term) > s21_EPSILON; i++) {
      term *= x / (long double)i;
      result += term;
    }
  }
  return result;
}

long double s21_fmod(double x, double y) {
  return (long double)(x - y * s21_floor(x / y));
}

long double s21_sin(double x) {
  int sign = (x >= 0) ? 1 : -1;

  x = s21_fmod(s21_fabs(x), 2 * s21_PI);
  if (x > s21_PI) {
    x -= s21_PI;
    sign *= -1;
  }
  if (x > s21_PI / 2) x = s21_PI - x;

  long double sum = x;
  double t = x;

  for (int n = 3; s21_fabs(t) > s21_EPSILON; n += 2)
    sum += t = -t * x * x / n / (n - 1);

  return sum * sign;
}

long double s21_cos(double x) {
  x = s21_fmod(s21_fabs(x), 2 * s21_PI);
  int sign = 1;

  if (x > s21_PI / 2 && x < 3 * s21_PI / 2) {
    sign = -1;
  }

  return sign * s21_sqrt(1 - pow(s21_sin(x), 2));
}

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

long double s21_asin(double x) {
  double t = x;
  long double sum = s21_NAN;

  if (s21_fabs(x) < 1) {
    sum = t;
    x *= x;
    for (int n = 1; s21_fabs(t) > s21_EPSILON; n += 2)
      sum += (t *= x * n / (n + 1)) / (n + 2);
  } else if (x == 1) {
    sum = s21_PI / 2;
  } else if (x == -1) {
    sum = -s21_PI / 2;
  }
  return sum;
}

long double s21_acos(double x) {
  long double res = s21_NAN;

  if (s21_fabs(x) <= 1) {
    res = s21_PI / 2 - s21_asin(x);
  }
  return res;
}

long double s21_atan(double x) { return s21_asin(x / s21_sqrt(1.0 + x * x)); }

  printf("%.6Lf\n", s21_asin(-0.19802));
  printf("%.6f\n\n", asin(-0.19802));

  printf("%.6Lf\n", s21_acos(0.2456));
  printf("%.6f\n\n", acos(0.2456));

      long double derivative = s21_exp(guess);
      guess -= error / derivative;
    }
  }
  return result;
}