#include <check.h>
#include <limits.h>
#include <math.h>

#include "s21_math.h"

#define S21_TITLE "\033[1;46mS21_"
#define S21_CLR_GRN "\033[32m"
#define S21_CLR_RED "\033[31m"
#define S21_CLR_NONE "\033[0m"
#define S21_TITLE_ABS S21_TITLE "ABS" S21_CLR_NONE
#define S21_TITLE_ACOS S21_TITLE "ACOS" S21_CLR_NONE
#define S21_TITLE_ASIN S21_TITLE "ASIN" S21_CLR_NONE
#define S21_TITLE_ATAN S21_TITLE "ATAN" S21_CLR_NONE
#define S21_TITLE_CEIL S21_TITLE "CEIL" S21_CLR_NONE
#define S21_TITLE_COS S21_TITLE "COS" S21_CLR_NONE
#define S21_TITLE_EXP S21_TITLE "EXP" S21_CLR_NONE
#define S21_TITLE_FABS S21_TITLE "FABS" S21_CLR_NONE
#define S21_TITLE_FLOOR S21_TITLE "FLOOR" S21_CLR_NONE
#define S21_TITLE_FMOD S21_TITLE "FMOD" S21_CLR_NONE
#define S21_TITLE_LOG S21_TITLE "LOG" S21_CLR_NONE
#define S21_TITLE_POW S21_TITLE "POW" S21_CLR_NONE
#define S21_TITLE_SIN S21_TITLE "SIN" S21_CLR_NONE
#define S21_TITLE_SQRT S21_TITLE "SQRT" S21_CLR_NONE
#define S21_TITLE_TAN S21_TITLE "TAN" S21_CLR_NONE
#define S21_ASSERT_INT_FAIL                                             \
  "Failed: value = " S21_CLR_GRN "%d" S21_CLR_NONE                      \
  " Result: s21 = " S21_CLR_RED "%d" S21_CLR_NONE " std = " S21_CLR_RED \
  "%d" S21_CLR_NONE
#define S21_ASSERT_LD_1P_FAIL                                            \
  "Failed: value = " S21_CLR_GRN "%e" S21_CLR_NONE                       \
  " Result: s21 = " S21_CLR_RED "%Le" S21_CLR_NONE " std = " S21_CLR_RED \
  "%Le" S21_CLR_NONE
#define S21_ASSERT_LD_2P_FAIL                                                \
  "Failed: value1 = " S21_CLR_GRN "%e" S21_CLR_NONE " value2 = " S21_CLR_GRN \
  "%e" S21_CLR_NONE " Result: s21 = " S21_CLR_RED "%Le" S21_CLR_NONE         \
  " std = " S21_CLR_RED "%Le" S21_CLR_NONE

static const int tc_int[] = {-1,         1,      -21,     21,      123456789,
                             -123456789, 000123, -000123, INT_MIN, INT_MAX,
                             0,          -0,     +0};
static const double tc_double[] = {
    -21.21, 21.21, -41.4567861, 36.67132, 1.5, -2, 1, -1, -0.1, 0.1, 0.2, -0.2,
    1e-6, -1e-6, 1e-9, -1e-9, 0.0, -0.0, +0.0, M_E, M_PI, 2 * M_PI, 3 * M_PI,
    M_PI_2, 9999999999.999999, -9999999999.999999, s21_NAN, s21_INF, -s21_INF,
    // additional
    M_LOG2E, M_LOG10E, M_LN2, M_LN10, M_PI_4, M_1_PI, M_2_PI, M_2_SQRTPI,
    M_SQRT2, M_SQRT1_2, 1e-10, -1e-10, 1e10, -1e10, 1e20, -1e20, 1e-20, -1e-20};
static const double tc_double_2p[] = {
    1.0,      2.0,       // 0
    0.0,      0.0,       // 1
    0.0,      1.1,       // 2
    1.1,      0.0,       // 3
    -1.0,     2.0,       // 4
    1.0,      -2.0,      // 5
    -1.0,     -2.0,      // 6
    -1.21,    2.42,      // 7
    1.21,     -2.42,     // 8
    -1.21,    -2.42,     // 9
    -1.0,     M_E,       // 10
    M_E,      M_E,       // 11
    M_E,      s21_NAN,   // 12
    s21_NAN,  M_E,       // 13
    s21_NAN,  s21_NAN,   // 14
    s21_INF,  M_E,       // 15
    M_E,      s21_INF,   // 16
    s21_INF,  s21_INF,   // 17
    -s21_INF, M_E,       // 18
    M_E,      -s21_INF,  // 19
    -s21_INF, -s21_INF,  // 20
    s21_INF,  2,         // 21
    2,        s21_INF,   // 22
    s21_INF,  s21_INF,   // 23
    -s21_INF, 2,         // 24
    2,        -s21_INF,  // 25
    -s21_INF, -s21_INF,  // 26
    0,        M_E,       // 27
    125893,   125893,    //
    -1,       3          //
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
