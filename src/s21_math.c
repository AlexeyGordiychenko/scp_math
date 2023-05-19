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

long double s21_ceil(double x) {
  int integer_part = (int)x;
  long double result;
  if (x > 0 && x > integer_part) {
    result = (long double)(integer_part + 1);
  } else if (x < 0 && x < integer_part) {
    result = (long double)(integer_part - 1);
  } else {
    result = (long double)integer_part;
  }
  return result;
}

long double s21_floor(double x) {
  int integer_part = (int)x;
  return (long double)integer_part;
}

long double s21_log(double x) {
  long double result = 0.0;
  if (x > 0.0) {
    long double guess = x;
    while (1) {
      long double error = s21_exp(guess) - x;

      if (s21_fabs(error) < s21_epsilon) {
        result = guess;
        break;
      }

      long double derivative = s21_exp(guess);
      guess -= error / derivative;
    }
  }
  return result;
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
    for (int i = 1; s21_fabs(term) > s21_epsilon; i++) {
      term *= x / (long double)i;
      result += term;
    }
  }
  return result;
}
