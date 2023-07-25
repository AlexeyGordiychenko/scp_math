#include <stdio.h>
#include <stdlib.h>

#define SCP_NAN (0.0 / 0.0)
#define SCP_INF (1.0 / 0.0)
#define SCP_TOLERANCE 1e-6
#define SCP_PI 3.14159265358979323846
#define SCP_PI_2 1.57079632679489661923
#define SCP_E 2.7182818284590452354
#define SCP_EPSILON (long double)1e-11
#define SCP_DMAX 1.7976931348623157E+308
#define SCP_DMIN -1.7976931348623157E+308
#define SCP_TAN_PI_2 16331239353195370.000000

// Computes absolute value of an integer value
int scp_abs(int x);

// Computes absolute value of a floating-point value
long double scp_fabs(double x);

// Computes square root
long double scp_sqrt(double x);

// Raises a number to the given power
long double scp_pow(double base, double exp);

// Returns e raised to given power
long double scp_exp(double x);

// Returns the nearest integer not less than the given value
long double scp_ceil(double x);

// Returns the nearest integer not greater than the given value
long double scp_floor(double x);

// Computes sine
long double scp_sin(double x);

// Computes cosine
long double scp_cos(double x);

// Computes tangent
long double scp_tan(double x);

// Remainder of the floating-point division operation
long double scp_fmod(double x, double y);

// Computes arc sine
long double scp_asin(double x);

// Computes arc cosine
long double scp_acos(double x);

// Computes arc tangent
long double scp_atan(double x);

// Computes natural logarithm
long double scp_log(double x);

// Checks if x is infinite
int scp_isinf(double x);

// Checks if x is NaN
int scp_isnan(double x);
