#define s21_nan (0.0 / 0.0)
#define s21_e (long double)2.7182818284
#define s21_epsilon (long double)0.000000001
#define s21_inf (1.0 / 0.0)

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

// Remainder of the floating-point division operation
long double s21_fmod(double x, double y);

// Computes sine
long double s21_sin(double x);

// Computes cosine
long double s21_cos(double x);

// Computes tangent
long double s21_tan(double x);

// Computes arc sine
long double s21_asin(double x);

// Computes arc cosine
long double s21_acos(double x);

long double s21_atan(double x);

long double s21_log(double x);

// Checks if x is infinite
int s21_isinf(double x);

// Checks if x is NaN
int s21_isnan(double x);
