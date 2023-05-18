#define s21_nan (0.0 / 0.0)
#define s21_e (long double)2.718281
#define s21_epsilon (long double)0.000001

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