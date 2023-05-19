#define s21_nan (0.0 / 0.0)
#define s21_PI 3.14159265358979323846
#define s21_PI_2 1.57079632679489661923
#define s21_E 2.7182818284590452354
#define s21_EPSILON 1e-6

// Computes absolute value of an integer value
int s21_abs(int x);

// Computes absolute value of a floating-point value
long double s21_fabs(double x);

// Computes square root
long double s21_sqrt(double x);

// Raises a number to the given power
long double s21_pow(double base, double exp);

// Returns e raised to given power
long double s21_exp(double x);

// Returns the nearest integer not less than the given value
long double s21_ceil(double x);

// Returns the nearest integer not greater than the given value
long double s21_floor(double x);

// Computes sine
long double s21_sin(double x);

// Computes cosine
long double s21_cos(double x);

// Computes tangent
long double s21_tan(double x);

// Remainder of the floating-point division operation
long double s21_fmod(double x, double y);

// Computes arc sine
long double s21_asin(double x);

// Computes arc cosine
long double s21_acos(double x);

int convert(double x);

int equal(double x, double y);

long double s21_log(double x);
