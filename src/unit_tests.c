#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "s21_math.h"

#define TEST_CASE_INT \
  { -21, 21, INT_MIN, INT_MAX, 0, -0, +0, s21_NAN, -s21_INF, s21_INF }
#define TEST_CASE_LD                                                  \
  {                                                                   \
    -1.0, 1.0, -1.1, 1.1, DBL_MIN, DBL_MAX, 0.0, -0.0, +0.0, s21_NAN, \
        -s21_INF, s21_INF                                             \
  }

void assert_int_eq(int a, int b) { ck_assert_int_eq(a, b); }
void assert_ld_eq(double a, double b) {
  ck_assert_double_eq_tol(a, b, s21_TOLERANCE);
}

void assert_int(int (*s21_func)(int), int (*std_func)(int),
                void (*assert_func)(int, int), int *values, int values_len) {
  for (int i = 0; i < values_len; i++) {
    assert_func(s21_func(values[i]), std_func(values[i]));
  }
}

void assert_ld(long double (*s21_func)(double), double (*std_func)(double),
               void (*assert_func)(double, double), double *values,
               double values_len) {
  for (int i = 0; i < values_len; i++) {
    assert_func(s21_func(values[i]), std_func(values[i]));
  }
}

START_TEST(abs_tests) {
  int test_values[] = TEST_CASE_INT;
  int test_values_len = sizeof(test_values) / sizeof(test_values[0]);
  assert_int(s21_abs, abs, assert_int_eq, test_values, test_values_len);
}
END_TEST

START_TEST(fabs_tests) {
  double test_values[] = TEST_CASE_LD;
  int test_values_len = sizeof(test_values) / sizeof(test_values[0]);
  assert_ld(s21_fabs, fabs, assert_ld_eq, test_values, test_values_len);
}
END_TEST

// START_TEST(pow_tests) {
//   ck_assert_float_eq(pow(13.21313, 2.5), s21_pow(13.21313, 2.5));
//   ck_assert_float_eq(pow(32346234.21313, 2.5), s21_pow(32346234.21313, 2.5));
//   ck_assert_float_eq(pow(0, 2.5), s21_pow(0, 2.5));
//   ck_assert_float_eq(pow(2, 18.1), s21_pow(2, 18.1));
//   ck_assert_float_eq(pow(123, -2), s21_pow(123, -2));
//   ck_assert_float_eq(pow(123, 2), s21_pow(123, 2));
//   ck_assert_float_eq(pow(123, 0), s21_pow(123, 0));
//   ck_assert_int_eq(pow(-12.1, -1.1), s21_pow(-12.1, -1.1));
//   ck_assert_double_nan(s21_pow(-12.1, -1.1));
//   ck_assert_double_nan(s21_pow(-12.1, 1.1));
//   ck_assert_ldouble_nan(s21_pow(NAN, NAN));
//   ck_assert_ldouble_eq(pow(INFINITY, 1), s21_pow(INFINITY, 1));
//   ck_assert_ldouble_eq(pow(-INFINITY, 1), s21_pow(-INFINITY, 1));
//   ck_assert_ldouble_eq(pow(INFINITY, INFINITY), s21_pow(INFINITY, INFINITY));
// }
// END_TEST

// START_TEST(sqrt_tests) {
//   ck_assert_int_eq(sqrt(0.0), s21_sqrt(0.0));
//   ck_assert_float_eq(sqrt(1.0), s21_sqrt(1.0));
//   ck_assert_float_eq(sqrt(3.14), s21_sqrt(3.14));
//   ck_assert_float_eq(sqrt(6.28), s21_sqrt(6.28));
//   ck_assert_float_eq(sqrt(2.2343), s21_sqrt(2.2343));
//   ck_assert_double_nan(s21_sqrt(-2.2343));
//   ck_assert_float_eq(sqrt(0.5), s21_sqrt(0.5));
//   ck_assert_ldouble_nan(s21_sqrt(NAN));
//   ck_assert_ldouble_eq(sqrt(INFINITY), s21_sqrt(INFINITY));
//   ck_assert_ldouble_nan(s21_sqrt(-INFINITY));
// }
// END_TEST

Suite *s21_math_tests_create() {
  Suite *s21_math = suite_create("s21_math");
  TCase *s21_math_tests = tcase_create("S21_MATH");
  // tcase_add_test(s21_math_tests, sqrt_tests);
  tcase_add_test(s21_math_tests, abs_tests);
  tcase_add_test(s21_math_tests, fabs_tests);
  // tcase_add_test(s21_math_tests, pow_tests);
  suite_add_tcase(s21_math, s21_math_tests);
  return s21_math;
}

int main() {
  Suite *s21_math = s21_math_tests_create();
  SRunner *s21_math_runner = srunner_create(s21_math);
  int number_failed;
  srunner_run_all(s21_math_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_math_runner);
  srunner_free(s21_math_runner);

  return number_failed == 0 ? 0 : 1;
}