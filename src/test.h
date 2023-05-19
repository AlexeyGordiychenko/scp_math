#include <check.h>
#include <limits.h>
#include <math.h>

#include "s21_math.h"

#define S21_TITLE_BG "\033[46m|S21_"
#define S21_TITLE_END "|\033[0m"
#define S21_TITLE_ABS S21_TITLE_BG "ABS" S21_TITLE_END
#define S21_TITLE_FABS S21_TITLE_BG "FABS" S21_TITLE_END
#define S21_TITLE_SQRT S21_TITLE_BG "SQRT" S21_TITLE_END
#define S21_TITLE_POW S21_TITLE_BG "POW" S21_TITLE_END
#define S21_TITLE_EXP S21_TITLE_BG "EXP" S21_TITLE_END
#define S21_TITLE_CEIL S21_TITLE_BG "CEIL" S21_TITLE_END
#define S21_TITLE_FLOOR S21_TITLE_BG "FLOOR" S21_TITLE_END
#define S21_TITLE_SIN S21_TITLE_BG "SIN" S21_TITLE_END
#define S21_TITLE_COS S21_TITLE_BG "COS" S21_TITLE_END
#define S21_TITLE_TAN S21_TITLE_BG "TAN" S21_TITLE_END
#define S21_TITLE_FMOD S21_TITLE_BG "FMOD" S21_TITLE_END
#define S21_TITLE_ASIN S21_TITLE_BG "ASIN" S21_TITLE_END
#define S21_TITLE_ACOS S21_TITLE_BG "ACOS" S21_TITLE_END

static const int tc_int[] = {-21, 21, INT_MIN, INT_MAX, 0, -0, +0};
static const double tc_double[] = {-21.0, 21.0, -41.4567861, 371.67131,
                                   -0.1,  0.1,  0.0,         -0.0,
                                   +0.0,  M_E,  M_PI,        s21_NAN};
static const double tc_double_2p[] = {
    1.0,     2.0,      // 0
    0.0,     0.0,      // 1
    -1.0,    2.0,      // 2
    1.0,     -2.0,     // 3
    -1.0,    -2.0,     // 4
    -1.0,    M_E,      // 5
    M_E,     M_E,      // 6
    M_E,     s21_NAN,  // 7
    s21_NAN, M_E,      // 8
};

// static const double tc_double[] = {
//     -1.0, 1.0,  -1.1, 1.1, -0.1, 0.1,     DBL_MIN,  DBL_MAX,
//     0.0,  -0.0, +0.0, M_E, M_PI, s21_NAN, -s21_INF, s21_INF};
// static const double tc_double[] = {
//     -1.0, 1.0,  -1.1, 1.1, -0.1, 0.1,     DBL_MIN,  DBL_MAX,
//     0.0,  -0.0, +0.0, M_E, M_PI, s21_NAN, -s21_INF, s21_INF};

Suite* s21_generic_ts(const TTest* test_func, int loops_num, char* title);

void s21_generic_ld_test(int idx, long double (*s21_func)(double),
                         double (*std_func)(double));

void s21_generic_ld_2p_test(int idx, long double (*s21_func)(double, double),
                            double (*std_func)(double, double));
