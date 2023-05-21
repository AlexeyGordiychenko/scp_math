#include <check.h>
#include <limits.h>
#include <math.h>

#include "s21_math.h"

#define S21_TITLE "\033[1;46mS21_"
#define S21_CLR_GRN "\033[32m"
#define S21_CLR_RED "\033[31m"
#define S21_CLR_NONE "\033[0m"
#define S21_TITLE_ABS S21_TITLE "ABS" S21_CLR_NONE
#define S21_TITLE_FABS S21_TITLE "FABS" S21_CLR_NONE
#define S21_TITLE_SQRT S21_TITLE "SQRT" S21_CLR_NONE
#define S21_TITLE_POW S21_TITLE "POW" S21_CLR_NONE
#define S21_TITLE_EXP S21_TITLE "EXP" S21_CLR_NONE
#define S21_TITLE_CEIL S21_TITLE "CEIL" S21_CLR_NONE
#define S21_TITLE_FLOOR S21_TITLE "FLOOR" S21_CLR_NONE
#define S21_TITLE_SIN S21_TITLE "SIN" S21_CLR_NONE
#define S21_TITLE_COS S21_TITLE "COS" S21_CLR_NONE
#define S21_TITLE_TAN S21_TITLE "TAN" S21_CLR_NONE
#define S21_TITLE_FMOD S21_TITLE "FMOD" S21_CLR_NONE
#define S21_TITLE_ASIN S21_TITLE "ASIN" S21_CLR_NONE
#define S21_TITLE_ACOS S21_TITLE "ACOS" S21_CLR_NONE
#define S21_TITLE_ATAN S21_TITLE "ATAN" S21_CLR_NONE
#define S21_ASSERT_INT_FAIL                                             \
  "Failed: value = " S21_CLR_GRN "%d" S21_CLR_NONE                      \
  " Result: s21 = " S21_CLR_RED "%d" S21_CLR_NONE " std = " S21_CLR_RED \
  "%d" S21_CLR_NONE
#define S21_ASSERT_LD_1P_FAIL                                            \
  "Failed: value = " S21_CLR_GRN "%f" S21_CLR_NONE                       \
  " Result: s21 = " S21_CLR_RED "%Lf" S21_CLR_NONE " std = " S21_CLR_RED \
  "%Lf" S21_CLR_NONE
#define S21_ASSERT_LD_2P_FAIL                                                \
  "Failed: value1 = " S21_CLR_GRN "%f" S21_CLR_NONE " value2 = " S21_CLR_GRN \
  "%f" S21_CLR_NONE " Result: s21 = " S21_CLR_RED "%Lf" S21_CLR_NONE         \
  " std = " S21_CLR_RED "%Lf" S21_CLR_NONE

static const int tc_int[] = {-1,         1,      -21,     21,      123456789,
                             -123456789, 000123, -000123, INT_MIN, INT_MAX,
                             0,          -0,     +0};
static const double tc_double[] = {
    -21.21,   21.21,   -41.4567861,
    36.67132, 1.5,     -2,
    1,        -1,      -0.1,
    0.1,      0.2,     -0.2,
    0.0,      -0.0,    +0.0,
    M_E,      M_PI,    2 * M_PI,
    3 * M_PI, M_PI_2,  99999999999999999999.99999999999,
    s21_nan,  s21_inf, -s21_inf};
static const double tc_double_2p[] = {
    1.0,     2.0,      // 0
    0.0,     0.0,      // 1
    0.0,     1.1,      // 2
    1.1,     0.0,      // 3
    -1.0,    2.0,      // 4
    1.0,     -2.0,     // 5
    -1.0,    -2.0,     // 6
    -1.21,   2.42,     // 7
    1.21,    -2.42,    // 8
    -1.21,   -2.42,    // 9
    -1.0,    M_E,      // 10
    M_E,     M_E,      // 11
    M_E,     s21_nan,  // 12
    s21_nan, M_E,      // 13
};

// static const double tc_double[] = {
//     -1.0, 1.0,  -1.1, 1.1, -0.1, 0.1,     DBL_MIN,  DBL_MAX,
//     0.0,  -0.0, +0.0, M_E, M_PI, s21_NAN, -s21_INF, s21_INF};
// static const double tc_double[] = {
//     -1.0, 1.0,  -1.1, 1.1, -0.1, 0.1,     DBL_MIN,  DBL_MAX,
//     0.0,  -0.0, +0.0, M_E, M_PI, s21_NAN, -s21_INF, s21_INF};

Suite* s21_generic_ts(const TTest* test_func, int loops_num, char* title);

void s21_generic_ld_1p_test(int idx, long double (*s21_func)(double),
                            double (*std_func)(double));

void s21_generic_ld_2p_test(int idx, long double (*s21_func)(double, double),
                            double (*std_func)(double, double));
