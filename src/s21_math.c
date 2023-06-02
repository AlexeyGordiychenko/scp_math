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
    if (s21_isinf(x)) {
      root = s21_INF;
    } else {
      while (1) {
        root = 0.5 * (n + (x / n));
        if (s21_fabs(root - n) < s21_EPSILON) {
          break;
        }
        n = root;
      }
    }
  } else if (x == 0) {
    root = 0;
  } else {
    root = s21_NAN;
  }
  return root;
}

long double s21_ceil(double x) {
  long long integer_part = (long long)x;
  long double result;
  if (x == s21_INF) {
    result = s21_INF;
  } else if (x == -s21_INF) {
    result = -s21_INF;
  } else if (x == 0) {
    result = 0;
  } else if (x == -0) {
    result = -0;
  } else if (x > 0 && x > integer_part && integer_part >= 0) {
    result = (long double)(integer_part + 1);
  } else if (x < 0 && x < integer_part && integer_part - x <= 1) {
    result = (long double)integer_part;
  } else {
    result = x;
  }
  return result;
}

long double s21_floor(double x) {
  long double result;
  if (x == s21_INF || s21_isnan(x)) {
    result = x;
  } else if (x == -s21_INF) {
    result = -s21_INF;
  } else if (x == 0.0) {
    result = 0.0;
  } else if (x == -0.0) {
    result = -0.0;
  } else {
    long double integer_part = (long double)((long long)x);
    if (integer_part == x) {
      result = integer_part;
    } else if (x < 0.0 && s21_fabs(integer_part - x) <= 1) {
      result = integer_part - 1.0;
    } else if (integer_part >= 0 || s21_fabs(integer_part - x) <= 1) {
      result = integer_part;
    } else {
      result = x;
    }
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 0.0;
  if (base == 1) {
    result = 1.0;
  } else if (exp == 0.0) {
    result = 1.0;
  } else if (exp == 1.0) {
    result = base;
  } else if (s21_isnan(base)) {
    result = s21_NAN;
  } else if (base == 0.0) {
    if (exp < 0.0 && s21_fmod(exp, 2) != 0.0 && (long long)exp == exp) {
      result = s21_INF;
    } else if (exp < 0.0 && s21_fmod(exp, 2) == 0.0 && (long long)exp == exp) {
      result = s21_INF;
    } else if (exp > 0.0 && (long long)exp == exp && s21_fmod(exp, 2) != 0.0) {
      result = 0.0;
    } else if (exp > 0.0 && (long long)exp == exp && s21_fmod(exp, 2) == 0.0) {
      result = 0.0;
    } else {
      result = 0.0;
    }
  } else if (base == -0.0) {
    if (exp < 0.0 && s21_fmod(exp, 2) != 0.0 && (long long)exp == exp) {
      result = -s21_INF;
    } else if (exp < 0.0 && s21_fmod(exp, 2) == 0.0 && (long long)exp == exp) {
      result = s21_INF;
    } else if (exp > 0.0 && (long long)exp == exp && s21_fmod(exp, 2) != 0.0) {
      result = -0.0;
    } else if (exp > 0.0 && (long long)exp == exp && s21_fmod(exp, 2) == 0.0) {
      result = 0.0;
    } else {
      result = 0.0;
    }
  } else if (base == -1.0 && s21_isinf(exp)) {
    result = 1;
  } else if (base < 0.0 && (long long)exp != exp && !s21_isinf(base)) {
    result = s21_NAN;
  } else if (base == s21_INF && exp < 0.0) {
    result = 0.0;
  } else if (base == s21_INF && exp > 0.0) {
    result = s21_INF;
  } else if (base == -s21_INF && s21_fmod(exp, 2) != 0.0 && exp < 0.0 &&
             (long long)exp == exp) {
    result = -0.0;
  } else if (base == -s21_INF && s21_fmod(exp, 2) == 0.0 && exp < 0.0 &&
             (long long)exp == exp) {
    result = 0.0;
  } else if (base == -s21_INF && s21_fmod(exp, 2) != 0.0 && exp > 0.0 &&
             (long long)exp == exp) {
    result = -s21_INF;
  } else if (base == -s21_INF && s21_fmod(exp, 2) == 0.0 && exp > 0.0 &&
             (long long)exp == exp) {
    result = s21_INF;
  } else if (exp == -s21_INF && s21_fabs(base) < 1.0) {
    result = s21_INF;
  } else if (exp == -s21_INF && s21_fabs(base) > 1.0) {
    result = 0.0;
  } else if (exp == s21_INF && s21_fabs(base) < 1.0) {
    result = 0.0;
  } else if (exp == s21_INF && s21_fabs(base) > 1.0) {
    result = s21_INF;
  } else if (base == -s21_INF) {
    result = s21_INF;
  } else if (base >= s21_DMAX) {
    result = -0.0;
  } else if (base <= s21_DMIN) {
    result = -0.0;
  } else if (!s21_isinf(base) && !s21_isinf(exp)) {
    if ((long long)exp == exp && (long long)exp % 2 != 0 && base < 0.0) {
      result = -s21_exp(exp * s21_log(s21_fabs(base)));
    } else {
      result = s21_exp(exp * s21_log(s21_fabs(base)));
    }
  }
  return result;
}

long double s21_exp(double x) {
  long double result = 1.0;
  if (x == -s21_INF || x <= s21_DMIN + 1) {
    result = 0.0;
  } else if (x == s21_INF || x >= s21_DMAX) {
    result = s21_INF;
  } else if (x == 1.0) {
    result = s21_E;
  } else if (x == 0.0) {
    result = 1.0;
  } else if (s21_isnan(x)) {
    result = s21_NAN;
  } else if (x <= s21_DMIN) {
    result = 0.0;
  } else {
    long double term = 1.0;
    int n = 1;
    while (s21_fabs(term) >= s21_EPSILON && n <= 100000 && result < s21_DMAX &&
           result >= s21_DMIN) {
      term *= (long double)((long double)x / n);
      result += term;
      n++;
    }
    if (n >= 100000) {
      result = s21_INF;
    }
  }
  if (result < 0.0) {
    result = 0.0;
  }
  return (double)result;
}

long double s21_sin(double x) {
  x = s21_fmod(x, 2.0 * s21_PI);
  double result = 0.0;
  double term = x;
  double sign = 1.0;
  double factorial = 1.0;

  for (int n = 1; n <= 15; n++) {
    result += sign * term;
    term *= x * x / ((2 * n) * (2 * n + 1));
    sign *= -1.0;
    factorial *= (2 * n) * (2 * n + 1);
  }

  return result;
}

long double s21_cos(double x) {
  long double result = 0;
  if (!s21_isnan(x) && !s21_isinf(x) && s21_fabs(s21_sin(x)) < 1) {
    result = s21_sin((s21_PI / 2) - x);
  } else if (s21_isnan(x)) {
    result = s21_NAN;
  } else if (s21_isinf(x)) {
    result = -s21_NAN;
  }

  return result;
}

long double s21_tan(double x) {
  long double result = 0;
  if (s21_fabs(x) == s21_PI_2) {
    result = s21_TAN_PI_2 * ((x < 0) ? -1 : 1);
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}

long double s21_fmod(double x, double y) {
  long double result = 0;
  if (s21_isnan(x) || s21_isnan(y) || s21_isinf(x) || y == 0) {
    result = s21_NAN;
  } else if (x == 0 && y != 0 && !s21_isnan(y)) {
    result = 0;
  } else if (x != s21_INF && x != -s21_INF && (y == s21_INF || y == -s21_INF)) {
    result = x;
  } else {
    long long q = x / y;
    result = x - q * y;
  }
  return result;
}

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

long double s21_atan(double x) {
  long double result = 0;
  if (x == -s21_INF) {
    result = -s21_PI / 2;
  } else if (x == s21_INF) {
    result = s21_PI / 2;
  } else {
    result = s21_asin(x / s21_sqrt(1.0 + x * x));
  }
  return result;
}

long double s21_log(double x) {
  long double result = 0.0;
  if (x > 0.0) {
    if (!s21_isinf(x)) {
      long double guess = x;
      int iterations = 0;
      while (1) {
        iterations++;
        long double error = s21_exp(guess) - x;

        if (s21_fabs(error) < s21_EPSILON || iterations >= 1000000) {
          result = guess;
          if (iterations >= 1000000) {
            result = s21_INF;
          }
          break;
        }

        long double derivative = s21_exp(guess);
        guess -= error / derivative;
      }
    } else {
      result = s21_INF;
    }
  } else if (x == 0.0) {
    result = -s21_INF;
  } else {
    result = -s21_NAN;
  }
  return result;
}

int s21_isinf(double x) { return s21_fabs(x) == s21_INF; }

int s21_isnan(double x) { return x != x; }
