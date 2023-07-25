#include "test.h"

START_TEST(abs_tests) {
  int a = scp_abs(tc_int[_i]);
  int b = abs(tc_int[_i]);
  ck_assert_msg(a == b, SCP_ASSERT_INT_FAIL, tc_int[_i], a, b);
}
END_TEST

START_TEST(acos_tests) { scp_generic_ld_1p_test(_i, scp_acos, acos); }
END_TEST

START_TEST(asin_tests) { scp_generic_ld_1p_test(_i, scp_asin, asin); }
END_TEST

START_TEST(atan_tests) { scp_generic_ld_1p_test(_i, scp_atan, atan); }
END_TEST

START_TEST(ceil_tests) { scp_generic_ld_1p_test(_i, scp_ceil, ceil); }
END_TEST

START_TEST(cos_tests) { scp_generic_ld_1p_test(_i, scp_cos, cos); }
END_TEST

START_TEST(exp_tests) { scp_generic_ld_1p_test(_i, scp_exp, exp); }
END_TEST

START_TEST(fabs_tests) { scp_generic_ld_1p_test(_i, scp_fabs, fabs); }
END_TEST

START_TEST(floor_tests) { scp_generic_ld_1p_test(_i, scp_floor, floor); }
END_TEST

START_TEST(fmod_tests) { scp_generic_ld_2p_test(_i, scp_fmod, fmod); }
END_TEST

START_TEST(log_tests) { scp_generic_ld_1p_test(_i, scp_log, log); }
END_TEST

START_TEST(pow_tests) { scp_generic_ld_2p_test(_i, scp_pow, pow); }
END_TEST

START_TEST(sin_tests) { scp_generic_ld_1p_test(_i, scp_sin, sin); }
END_TEST

START_TEST(sqrt_tests) { scp_generic_ld_1p_test(_i, scp_sqrt, sqrt); }
END_TEST

START_TEST(tan_tests) { scp_generic_ld_1p_test(_i, scp_tan, tan); }
END_TEST

int main() {
  int failed = 0;
  int tc_int_len = sizeof(tc_int) / sizeof(tc_int[0]);
  int tc_double_len = sizeof(tc_double) / sizeof(tc_double[0]);
  int tc_double_2p_len = sizeof(tc_double_2p) / sizeof(tc_double_2p[0]) / 2;
  Suite *scp_math_tests[] = {
      scp_generic_ts(abs_tests, tc_int_len, SCP_TITLE_ABS),
      scp_generic_ts(acos_tests, tc_double_len, SCP_TITLE_ACOS),
      scp_generic_ts(asin_tests, tc_double_len, SCP_TITLE_ASIN),
      scp_generic_ts(atan_tests, tc_double_len, SCP_TITLE_ATAN),
      scp_generic_ts(ceil_tests, tc_double_len, SCP_TITLE_CEIL),
      scp_generic_ts(cos_tests, tc_double_len, SCP_TITLE_COS),
      scp_generic_ts(exp_tests, tc_double_len, SCP_TITLE_EXP),
      scp_generic_ts(fabs_tests, tc_double_len, SCP_TITLE_FABS),
      scp_generic_ts(floor_tests, tc_double_len, SCP_TITLE_FLOOR),
      scp_generic_ts(fmod_tests, tc_double_2p_len, SCP_TITLE_FMOD),
      scp_generic_ts(log_tests, tc_double_len, SCP_TITLE_LOG),
      scp_generic_ts(pow_tests, tc_double_2p_len, SCP_TITLE_POW),
      scp_generic_ts(sin_tests, tc_double_len, SCP_TITLE_SIN),
      scp_generic_ts(sqrt_tests, tc_double_len, SCP_TITLE_SQRT),
      scp_generic_ts(tan_tests, tc_double_len, SCP_TITLE_TAN),
      NULL};

  for (int i = 0; scp_math_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(scp_math_tests[i]);

    // srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}

Suite *scp_generic_ts(const TTest *test_func, int loops_num, char *title) {
  Suite *suite = suite_create(title);
  TCase *tc = tcase_create("tc");
  tcase_add_loop_test(tc, test_func, 0, loops_num);
  suite_add_tcase(suite, tc);
  return suite;
}

void scp_generic_ld_1p_test(int idx, long double (*scp_func)(double),
                            double (*std_func)(double)) {
  long double a = scp_func(tc_double[idx]);
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
    res = fabsl(a - b) <= SCP_TOLERANCE;
  }
  ck_assert_msg(res, SCP_ASSERT_LD_1P_FAIL, tc_double[idx], a, b);
}

void scp_generic_ld_2p_test(int idx, long double (*scp_func)(double, double),
                            double (*std_func)(double, double)) {
  long double a = scp_func(tc_double_2p[idx * 2], tc_double_2p[idx * 2 + 1]);
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
    res = fabsl(a - b) <= SCP_TOLERANCE;
  }
  ck_assert_msg(res, SCP_ASSERT_LD_2P_FAIL, tc_double_2p[idx * 2],
                tc_double_2p[idx * 2 + 1], a, b);
}
