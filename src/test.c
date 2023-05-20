#include "test.h"

START_TEST(abs_tests) {
  int a = s21_abs(tc_int[_i]);
  int b = abs(tc_int[_i]);
  ck_assert_msg(a == b, S21_ASSERT_INT_FAIL, tc_int[_i], a, b);
}
END_TEST

START_TEST(fabs_tests) { s21_generic_ld_1p_test(_i, s21_fabs, fabs); }
END_TEST

START_TEST(sqrt_tests) { s21_generic_ld_1p_test(_i, s21_sqrt, sqrt); }
END_TEST

START_TEST(pow_tests) { s21_generic_ld_2p_test(_i, s21_pow, pow); }
END_TEST

START_TEST(exp_tests) { s21_generic_ld_1p_test(_i, s21_exp, exp); }
END_TEST

START_TEST(ceil_tests) { s21_generic_ld_1p_test(_i, s21_ceil, ceil); }
END_TEST

START_TEST(floor_tests) { s21_generic_ld_1p_test(_i, s21_floor, floor); }
END_TEST

START_TEST(sin_tests) { s21_generic_ld_1p_test(_i, s21_sin, sin); }
END_TEST

START_TEST(cos_tests) { s21_generic_ld_1p_test(_i, s21_cos, cos); }
END_TEST

START_TEST(tan_tests) { s21_generic_ld_1p_test(_i, s21_tan, tan); }
END_TEST

START_TEST(fmod_tests) { s21_generic_ld_2p_test(_i, s21_fmod, fmod); }
END_TEST

START_TEST(asin_tests) { s21_generic_ld_1p_test(_i, s21_asin, asin); }
END_TEST

START_TEST(acos_tests) { s21_generic_ld_1p_test(_i, s21_acos, acos); }
END_TEST

int main() {
  int failed = 0;
  int tc_int_len = sizeof(tc_int) / sizeof(tc_int[0]);
  int tc_double_len = sizeof(tc_double) / sizeof(tc_double[0]);
  int tc_double_2p_len = sizeof(tc_double_2p) / sizeof(tc_double_2p[0]) / 2;
  Suite *s21_math_tests[] = {
      s21_generic_ts(abs_tests, tc_int_len, S21_TITLE_ABS),
      s21_generic_ts(fabs_tests, tc_double_len, S21_TITLE_FABS),
      s21_generic_ts(sqrt_tests, tc_double_len, S21_TITLE_SQRT),
      s21_generic_ts(pow_tests, tc_double_2p_len, S21_TITLE_POW),
      s21_generic_ts(exp_tests, tc_double_len, S21_TITLE_EXP),
      s21_generic_ts(ceil_tests, tc_double_len, S21_TITLE_CEIL),
      s21_generic_ts(floor_tests, tc_double_len, S21_TITLE_FLOOR),
      s21_generic_ts(sin_tests, tc_double_len, S21_TITLE_SIN),
      s21_generic_ts(cos_tests, tc_double_len, S21_TITLE_COS),
      s21_generic_ts(tan_tests, tc_double_len, S21_TITLE_TAN),
      s21_generic_ts(fmod_tests, tc_double_2p_len, S21_TITLE_FMOD),
      s21_generic_ts(asin_tests, tc_double_len, S21_TITLE_ASIN),
      s21_generic_ts(acos_tests, tc_double_len, S21_TITLE_ACOS),
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

Suite *s21_generic_ts(const TTest *test_func, int loops_num, char *title) {
  Suite *suite = suite_create(title);
  TCase *tc = tcase_create("tc");
  tcase_add_loop_test(tc, test_func, 0, loops_num);
  suite_add_tcase(suite, tc);
  return suite;
}

void s21_generic_ld_1p_test(int idx, long double (*s21_func)(double),
                            double (*std_func)(double)) {
  long double a = s21_func(tc_double[idx]);
  long double b = std_func(tc_double[idx]);
  int a_isnan = isnan(a);
  int a_isinf = isinf(a);
  int b_isnan = isnan(b);
  int b_isinf = isinf(b);
  int res;
  if (a_isnan || b_isnan) {
    res = a_isnan && b_isnan;
  } else if (a_isinf || b_isinf) {
    res = a_isinf && b_isinf;
  } else {
    res = fabsl(a - b) <= s21_TOLERANCE;
  }
  ck_assert_msg(res, S21_ASSERT_LD_1P_FAIL, tc_double[idx], a, b);
}

void s21_generic_ld_2p_test(int idx, long double (*s21_func)(double, double),
                            double (*std_func)(double, double)) {
  long double a = s21_func(tc_double_2p[idx * 2], tc_double_2p[idx * 2 + 1]);
  long double b = std_func(tc_double_2p[idx * 2], tc_double_2p[idx * 2 + 1]);

  int a_isnan = isnan(a);
  int a_isinf = isinf(a);
  int b_isnan = isnan(b);
  int b_isinf = isinf(b);
  int res;
  if (a_isnan || b_isnan) {
    res = a_isnan && b_isnan;
  } else if (a_isinf || b_isinf) {
    res = a_isinf && b_isinf;
  } else {
    res = fabsl(a - b) <= s21_TOLERANCE;
  }
  ck_assert_msg(res, S21_ASSERT_LD_2P_FAIL, tc_double_2p[idx * 2],
                tc_double_2p[idx * 2 + 1], a, b);
}
