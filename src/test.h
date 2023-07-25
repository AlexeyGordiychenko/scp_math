#include <check.h>
#include <limits.h>
#include <math.h>

#include "scp_math.h"

#define SCP_TITLE "\033[1;46mSCP_"
#define SCP_CLR_GRN "\033[32m"
#define SCP_CLR_RED "\033[31m"
#define SCP_CLR_NONE "\033[0m"
#define SCP_TITLE_ABS SCP_TITLE "ABS" SCP_CLR_NONE
#define SCP_TITLE_ACOS SCP_TITLE "ACOS" SCP_CLR_NONE
#define SCP_TITLE_ASIN SCP_TITLE "ASIN" SCP_CLR_NONE
#define SCP_TITLE_ATAN SCP_TITLE "ATAN" SCP_CLR_NONE
#define SCP_TITLE_CEIL SCP_TITLE "CEIL" SCP_CLR_NONE
#define SCP_TITLE_COS SCP_TITLE "COS" SCP_CLR_NONE
#define SCP_TITLE_EXP SCP_TITLE "EXP" SCP_CLR_NONE
#define SCP_TITLE_FABS SCP_TITLE "FABS" SCP_CLR_NONE
#define SCP_TITLE_FLOOR SCP_TITLE "FLOOR" SCP_CLR_NONE
#define SCP_TITLE_FMOD SCP_TITLE "FMOD" SCP_CLR_NONE
#define SCP_TITLE_FMOD_E SCP_TITLE "FMOD_EXTENDED" SCP_CLR_NONE
#define SCP_TITLE_LOG SCP_TITLE "LOG" SCP_CLR_NONE
#define SCP_TITLE_POW SCP_TITLE "POW" SCP_CLR_NONE
#define SCP_TITLE_POW_E SCP_TITLE "POW_EXTENDED" SCP_CLR_NONE
#define SCP_TITLE_SIN SCP_TITLE "SIN" SCP_CLR_NONE
#define SCP_TITLE_SQRT SCP_TITLE "SQRT" SCP_CLR_NONE
#define SCP_TITLE_TAN SCP_TITLE "TAN" SCP_CLR_NONE
#define SCP_ASSERT_INT_FAIL                                             \
  "Failed: value = " SCP_CLR_GRN "%d" SCP_CLR_NONE                      \
  " Result: s21 = " SCP_CLR_RED "%d" SCP_CLR_NONE " std = " SCP_CLR_RED \
  "%d" SCP_CLR_NONE
#define SCP_ASSERT_LD_1P_FAIL                                               \
  "Failed: value = " SCP_CLR_GRN "%e" SCP_CLR_NONE                          \
  " Result: s21 = " SCP_CLR_RED "%.16Le" SCP_CLR_NONE " std = " SCP_CLR_RED \
  "%.16Le" SCP_CLR_NONE
#define SCP_ASSERT_LD_2P_FAIL                                                \
  "Failed: value1 = " SCP_CLR_GRN "%e" SCP_CLR_NONE " value2 = " SCP_CLR_GRN \
  "%e" SCP_CLR_NONE " Result: s21 = " SCP_CLR_RED "%.16Le" SCP_CLR_NONE      \
  " std = " SCP_CLR_RED "%.16Le" SCP_CLR_NONE

static const int tc_int[] = {-1,         1,      -21,     21,      123456789,
                             -123456789, 000123, -000123, INT_MIN, INT_MAX,
                             0,          -0,     +0};
static const double tc_double[] = {-21.21,      21.21,
                                   -41.4567861, 1.5,
                                   -2,          1,
                                   -1,          -0.1,
                                   0.1,         0.2,
                                   -0.2,        -1e-6,
                                   -1e-9,       0.0,
                                   -0.0,        +0.0,
                                   M_E,         M_PI,
                                   2 * M_PI,    3 * M_PI,
                                   M_PI_2,      -9999999999.999999,
                                   SCP_NAN,     SCP_INF,
                                   -SCP_INF};
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
    M_E,      SCP_NAN,   // 12
    SCP_NAN,  M_E,       // 13
    SCP_NAN,  SCP_NAN,   // 14
    SCP_INF,  M_E,       // 15
    M_E,      SCP_INF,   // 16
    SCP_INF,  SCP_INF,   // 17
    -SCP_INF, M_E,       // 18
    M_E,      -SCP_INF,  // 19
    -SCP_INF, -SCP_INF,  // 20
    SCP_INF,  2,         // 21
    2,        SCP_INF,   // 22
    SCP_INF,  SCP_INF,   // 23
    -SCP_INF, 2,         // 24
    2,        -SCP_INF,  // 25
    -SCP_INF, -SCP_INF,  // 26
    0,        M_E,       // 27
    125893,   125893,    // 28
    -1,       3,         // 29
    -15,      3,         // 30
};

// static const double tc_double[] = {
//     -1.0, 1.0,  -1.1, 1.1, -0.1, 0.1,     DBL_MIN,  DBL_MAX,
//     0.0,  -0.0, +0.0, M_E, M_PI, SCP_NAN, -SCP_INF, SCP_INF};
// static const double tc_double[] = {
//     -1.0, 1.0,  -1.1, 1.1, -0.1, 0.1,     DBL_MIN,  DBL_MAX,
//     0.0,  -0.0, +0.0, M_E, M_PI, SCP_NAN, -SCP_INF, SCP_INF};

Suite* scp_generic_ts(const TTest* test_func, int loops_num, char* title);

void scp_generic_ld_1p_test(int idx, long double (*scp_func)(double),
                            double (*std_func)(double));

void scp_generic_ld_2p_test(int idx, long double (*scp_func)(double, double),
                            double (*std_func)(double, double));
void scp_generic_ld_2p_test_ext(int idx,
                                long double (*scp_func)(double, double),
                                double (*std_func)(double, double));