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
      root = s21_inf;
    } else {
      while (1) {
        root = 0.5 * (n + (x / n));
        if (s21_fabs(root - n) < s21_epsilon) {
          break;
        }
        n = root;
      }
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
  if (base == 1) {
    result = 1.0;
  } else if (exp == 0.0) {
    result = 1.0;
  } else {
    result = s21_exp(exp * s21_log(base));
  }
  return result;
}

long double s21_exp(double x) {
  // long double result = 1.0;
  // if (x == 1.0) {
  //   result = 1.0;
  // } else if (x == 0.0) {
  //   result = 0.0;
  // } else {
  //   long double term = 1.0;
  //   for (int i = 1; s21_fabs(term) > s21_EPSILON; i++) {
  //     term *= x / (long double)i;
  //     result += term;
  //   }
  // }
  // return result;
  double result = 1.0;
  if (x == 0) {
    result = 1;
  } else if (x == 1.0) {
    result = s21_E;
  } else if (s21_isnan(x)) {
    result = x;
  } else if (s21_isinf(x)) {
    result = (x > 0) ? s21_INF : 0.0;
  } else {
    long double term = 1.0;
    long double prev_term = 0;
    double x_ = (x < -10) ? -x : x;
    // for (int i = 1; s21_fabs(term) > s21_EPSILON; i++) {
    for (long double i = 1; s21_fabs(term - prev_term) > 1e-6; i++) {
      prev_term = term;
      term *= x_ / i;
      result += term;
    }
    if (x < -10) {
      result = 1.0 / result;
    }
  }
  return (long double)result;
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

long double s21_pow(double base, double exp) {
  long double result = 1.0;
  if (base == 1) {
    result = 1.0;
  } else if (exp == 0.0) {
    result = 1.0;
  } else if (base == +0 && s21_fmod(exp, 2) != 0.0) {
    result = s21_inf;
  } else if (base == -0 && s21_fmod(exp, 2) != 0) {
    result = -s21_inf;
  } else if (base == 0 && exp < 0.0 && s21_fmod(exp, 2) == 0) {
    result = +s21_inf;
  } else {
    result = s21_exp(exp * s21_log(base));
  }
  return result;
}

long double s21_exp(double x) {
  long double result = 1.0;
  if (x == 1.0) {
    result = s21_e;
  } else if (x == 0.0) {
    result = 1.0;
  } else if (x == -s21_inf) {
    result = +0.0;
  } else if (x == s21_inf) {
    result = s21_inf;
  } else {
    long double term = 1.0;
    int n = 1;
    while (s21_fabs(term) >= s21_epsilon) {
      term *= (long double)((long double)x / n);
      result += term;
      n++;
    }
  }
  return (double)result;
}

long double s21_sin(double x) {
  int sign = (x >= 0) ? 1 : -1;

  x = s21_fmod(s21_fabs(x), 2 * s21_pi);
  if (x > s21_pi) {
    x -= s21_pi;
    sign *= -1;
  }
  if (x > s21_pi / 2) x = s21_pi - x;

  long double sum = x;
  double t = x;

  for (int n = 3; s21_fabs(t) > s21_epsilon; n += 2)
    sum += t = -t * x * x / n / (n - 1);

  return sum * sign;
}

long double s21_cos(double x) {
  x = s21_fmod(s21_fabs(x), 2 * s21_pi);
  int sign = 1;
  if (x > s21_pi / 2 && x < 3 * s21_pi / 2) {
    sign = -1;
  }
  return sign * s21_sqrt(1 - s21_pow(s21_sin(x), 2));
}

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

long double s21_fmod(double x, double y) {
  return (long double)(x - y * s21_floor(x / y));
}

long double s21_asin(double x) {
  double t = x;
  long double sum = s21_nan;

  if (s21_fabs(x) < 1) {
    sum = t;
    x *= x;
    for (int n = 1; s21_fabs(t) > s21_epsilon; n += 2)
      sum += (t *= x * n / (n + 1)) / (n + 2);
  } else if (x == 1) {
    sum = s21_pi / 2;
  } else if (x == -1) {
    sum = -s21_pi / 2;
  }
  return sum;
}

long double s21_acos(double x) {
  long double res = s21_nan;

  if (s21_fabs(x) <= 1) {
    res = s21_pi / 2 - s21_asin(x);
  }
  return res;
}

long double s21_atan(double x) { return s21_asin(x / s21_sqrt(1.0 + x * x)); }

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

int s21_isinf(double x) { return s21_fabs(x) == s21_inf; }

int s21_isnan(double x) { return x != x; }
