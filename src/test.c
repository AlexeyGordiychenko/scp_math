#include <check.h>
#include <limits.h>
#include <math.h>

#include "s21_math.h"

#define S21_TITLE_BG "\033[46m|S21_"
#define S21_TITLE_END "|\033[0m"
#define S21_TITLE_ABS S21_TITLE_BG "ABS" S21_TITLE_END
#define S21_TITLE_FABS S21_TITLE_BG "FABS" S21_TITLE_END
#define S21_TITLE_SQRT S21_TITLE_BG "SQRT" S21_TITLE_END
#define S21_TITLE_SIN S21_TITLE_BG "SIN" S21_TITLE_END
#define S21_TITLE_COS S21_TITLE_BG "COS" S21_TITLE_END

static const int tc_int[] = {-21, 21, INT_MIN, INT_MAX, 0, -0, +0};
static const double tc_double[] = {-1.0, 1.0,     -1.1,    1.1,     -0.1,
                                   0.1,  DBL_MIN, DBL_MAX, 0.0,     -0.0,
                                   +0.0, M_E,     M_PI,    s21_NAN, -s21_INF};
// static const double tc_double[] = {
//     -1.0, 1.0,  -1.1, 1.1, -0.1, 0.1,     DBL_MIN,  DBL_MAX,
//     0.0,  -0.0, +0.0, M_E, M_PI, s21_NAN, -s21_INF, s21_INF};

START_TEST(abs_tests) {
  ck_assert_int_eq(s21_abs(tc_int[_i]), abs(tc_int[_i]));
}
END_TEST

void s21_generic_ld_test(int idx, long double (*s21_func)(double),
                         double (*std_func)(double)) {
  long double a = s21_func(tc_double[idx]);
  long double b = std_func(tc_double[idx]);

  if (isnan(a) || isnan(b)) {
    ck_assert_int_eq(isnan(a), isnan(b));
  } else if (isinf(a) || isinf(b)) {
    ck_assert_int_eq(isinf(a), isinf(b));
  } else {
    ck_assert_double_eq_tol((double)s21_func(tc_double[idx]),
                            std_func(tc_double[idx]), s21_TOLERANCE);
  }
}

START_TEST(fabs_tests) { s21_generic_ld_test(_i, s21_fabs, fabs); }
END_TEST

START_TEST(sqrt_tests) { s21_generic_ld_test(_i, s21_sqrt, sqrt); }
END_TEST

START_TEST(sin_tests) { s21_generic_ld_test(_i, s21_sin, sin); }
END_TEST

START_TEST(cos_tests) { s21_generic_ld_test(_i, s21_cos, cos); }
END_TEST

Suite *s21_generic_ts(const TTest *test_func, int loops_num, char *title) {
  Suite *suite = suite_create(title);
  TCase *tc = tcase_create("tc");
  tcase_add_loop_test(tc, test_func, 0, loops_num);
  suite_add_tcase(suite, tc);
  return suite;
}

int main() {
  int failed = 0;
  int tc_int_len = sizeof(tc_int) / sizeof(tc_int[0]);
  int tc_double_len = sizeof(tc_double) / sizeof(tc_double[0]);
  Suite *s21_math_tests[] = {
      s21_generic_ts(abs_tests, tc_int_len, S21_TITLE_ABS),
      s21_generic_ts(fabs_tests, tc_double_len, S21_TITLE_FABS),
      s21_generic_ts(sqrt_tests, tc_double_len, S21_TITLE_SQRT),
      s21_generic_ts(sin_tests, tc_double_len, S21_TITLE_SIN),
      s21_generic_ts(cos_tests, tc_double_len, S21_TITLE_COS),
      NULL};

  for (int i = 0; s21_math_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_math_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}