#include "scp_math.h"

int scp_abs(int x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}

long double scp_fabs(double x) {
  if (x < 0.0) {
    x *= -1.0;
  }
  return (long double)x;
}

long double scp_sqrt(double x) {
  long double n = x;
  long double root;

  if (x > 0) {
    if (scp_isinf(x)) {
      root = SCP_INF;
    } else {
      while (1) {
        root = 0.5 * (n + (x / n));
        if (scp_fabs(root - n) < SCP_EPSILON) {
          break;
        }
        n = root;
      }
    }
  } else if (x == 0) {
    root = 0;
  } else {
    root = SCP_NAN;
  }
  return root;
}

long double scp_ceil(double x) {
  long long integer_part = (long long)x;
  long double result;
  if (x == SCP_INF) {
    result = SCP_INF;
  } else if (x == -SCP_INF) {
    result = -SCP_INF;
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

long double scp_floor(double x) {
  long double result;
  if (x == SCP_INF || scp_isnan(x)) {
    result = x;
  } else if (x == -SCP_INF) {
    result = -SCP_INF;
  } else if (x == 0.0) {
    result = 0.0;
  } else if (x == -0.0) {
    result = -0.0;
  } else {
    long double integer_part = (long double)((long long)x);
    if (integer_part == x) {
      result = integer_part;
    } else if (x < 0.0 && scp_fabs(integer_part - x) <= 1) {
      result = integer_part - 1.0;
    } else if (integer_part >= 0 || scp_fabs(integer_part - x) <= 1) {
      result = integer_part;
    } else {
      result = x;
    }
  }
  return result;
}

long double scp_pow(double base, double exp) {
  long double result = SCP_NAN;
  if (base == 1) {
    result = 1.0;
  } else if (exp == 0.0) {
    result = 1.0;
  } else if (exp == 1.0) {
    result = base;
  } else if (scp_isnan(base)) {
    result = SCP_NAN;
  } else if (base == 0.0) {
    if (exp < 0.0 && scp_fmod(exp, 2) != 0.0 && (long long)exp == exp) {
      result = SCP_INF;
    } else if (exp < 0.0 && scp_fmod(exp, 2) == 0.0 && (long long)exp == exp) {
      result = SCP_INF;
    } else if (exp > 0.0 && (long long)exp == exp && scp_fmod(exp, 2) != 0.0) {
      result = 0.0;
    } else if (exp > 0.0 && (long long)exp == exp && scp_fmod(exp, 2) == 0.0) {
      result = 0.0;
    } else {
      result = 0.0;
    }
  } else if (base == -0.0) {
    if (exp < 0.0 && scp_fmod(exp, 2) != 0.0 && (long long)exp == exp) {
      result = -SCP_INF;
    } else if (exp < 0.0 && scp_fmod(exp, 2) == 0.0 && (long long)exp == exp) {
      result = SCP_INF;
    } else if (exp > 0.0 && (long long)exp == exp && scp_fmod(exp, 2) != 0.0) {
      result = -0.0;
    } else if (exp > 0.0 && (long long)exp == exp && scp_fmod(exp, 2) == 0.0) {
      result = 0.0;
    } else {
      result = 0.0;
    }
  } else if (scp_isnan(exp)) {
    result = SCP_NAN;
  } else if (base == -1.0 && scp_isinf(exp)) {
    result = 1;
  } else if (exp == -SCP_INF && scp_fabs(base) < 1.0) {
    result = SCP_INF;
  } else if (exp == -SCP_INF && scp_fabs(base) > 1.0) {
    result = 0.0;
  } else if (exp == SCP_INF && scp_fabs(base) < 1.0) {
    result = 0.0;
  } else if (exp == SCP_INF && scp_fabs(base) > 1.0) {
    result = SCP_INF;
  } else if (base < 0.0 && (long long)exp != exp && !scp_isinf(base)) {
    result = SCP_NAN;
  } else if (base == SCP_INF && exp < 0.0) {
    result = 0.0;
  } else if (base == SCP_INF && exp > 0.0) {
    result = SCP_INF;
  } else if (base == -SCP_INF && scp_fmod(exp, 2) != 0.0 && exp < 0.0 &&
             (long long)exp == exp) {
    result = -0.0;
  } else if (base == -SCP_INF && scp_fmod(exp, 2) == 0.0 && exp < 0.0 &&
             (long long)exp == exp) {
    result = 0.0;
  } else if (base == -SCP_INF && scp_fmod(exp, 2) != 0.0 && exp > 0.0 &&
             (long long)exp == exp) {
    result = -SCP_INF;
  } else if (base == -SCP_INF && scp_fmod(exp, 2) == 0.0 && exp > 0.0 &&
             (long long)exp == exp) {
    result = SCP_INF;
  } else if (base == -SCP_INF) {
    result = SCP_INF;
  } else if (base >= SCP_DMAX) {
    result = -0.0;
  } else if (base <= SCP_DMIN) {
    result = -0.0;
  } else if (!scp_isinf(base) && !scp_isinf(exp)) {
    if ((long long)exp == exp && (long long)exp % 2 != 0 && base < 0.0) {
      result = -scp_exp(exp * scp_log(scp_fabs(base)));
    } else {
      result = scp_exp(exp * scp_log(scp_fabs(base)));
    }
  }
  return result;
}

long double scp_exp(double x) {
  long double result = 1.0;
  if (x == -SCP_INF || x <= SCP_DMIN) {
    result = 0.0;
  } else if (x == SCP_INF || x >= SCP_DMAX) {
    result = SCP_INF;
  } else if (x < 0.0) {
    result = 1.0 / scp_exp(-x);
  } else {
    long double term = 1.0;
    int n = 1;

    while (scp_fabs(term) > SCP_EPSILON && n <= 100000 && result < SCP_DMAX &&
           result >= SCP_DMIN) {
      term *= (long double)(x / n);
      result += term;
      n++;
    }

    if (result < 0.0) {
      result = 0.0;
    } else if (n > 100000) {
      result = SCP_INF;
    }
  }
  return (double)result;
}

long double scp_sin(double x) {
  x = scp_fmod(x, 2.0 * SCP_PI);
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

long double scp_cos(double x) {
  long double result = 0;
  if (!scp_isnan(x) && !scp_isinf(x) && scp_fabs(scp_sin(x)) < 1) {
    result = scp_sin((SCP_PI / 2) - x);
  } else if (scp_isnan(x)) {
    result = SCP_NAN;
  } else if (scp_isinf(x)) {
    result = -SCP_NAN;
  }

  return result;
}

long double scp_tan(double x) {
  long double result = 0;
  if (scp_fabs(x) == SCP_PI_2) {
    result = SCP_TAN_PI_2 * ((x < 0) ? -1 : 1);
  } else {
    result = scp_sin(x) / scp_cos(x);
  }
  return result;
}

long double scp_fmod(double x, double y) {
  long double result = 0;
  if (scp_isnan(x) || scp_isnan(y) || scp_isinf(x) || y == 0) {
    result = SCP_NAN;
  } else if (x == 0 && y != 0 && !scp_isnan(y)) {
    result = 0;
  } else if (x != SCP_INF && x != -SCP_INF && (y == SCP_INF || y == -SCP_INF)) {
    result = x;
  } else {
    long long q = x / y;
    result = x - q * y;
  }
  return result;
}

long double scp_asin(double x) {
  double t = x;
  long double sum = SCP_NAN;

  if (scp_fabs(x) < 1) {
    sum = t;
    x *= x;
    long iterations = 0;
    for (int n = 1; scp_fabs(t) > SCP_EPSILON && iterations <= 100000000;
         n += 2, iterations++)
      sum += (t *= x * n / (n + 1)) / (n + 2);
  } else if (x == 1) {
    sum = SCP_PI / 2;
  } else if (x == -1) {
    sum = -SCP_PI / 2;
  }
  return sum;
}

long double scp_acos(double x) {
  long double res = SCP_NAN;

  if (scp_fabs(x) <= 1) {
    res = SCP_PI / 2 - scp_asin(x);
  }
  return res;
}

long double scp_atan(double x) {
  long double result = 0;
  if (x == -SCP_INF) {
    result = -SCP_PI / 2;
  } else if (x == SCP_INF) {
    result = SCP_PI / 2;
  } else {
    result = scp_asin(x / scp_sqrt(1.0 + x * x));
  }
  return result;
}

long double scp_log(double x) {
  long double result = 0.0;
  if (x > 0.0) {
    if (!scp_isinf(x)) {
      long double guess = x;
      int iterations = 0;
      while (1) {
        iterations++;
        long double error = scp_exp(guess) - x;

        if (scp_fabs(error) < SCP_EPSILON || iterations >= 100000) {
          result = guess;
          if (iterations >= 100000) {
            result = SCP_INF;
          }
          break;
        }

        long double derivative = scp_exp(guess);
        guess -= error / derivative;
      }
    } else {
      result = SCP_INF;
    }
  } else if (x == 0.0) {
    result = -SCP_INF;
  } else {
    result = -SCP_NAN;
  }
  return result;
}

int scp_isinf(double x) { return scp_fabs(x) == SCP_INF; }

int scp_isnan(double x) { return x != x; }
