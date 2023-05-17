#include <stdio.h>
#include <stdlib.h>

#define s21_NAN (0.0 / 0.0L)
#define s21_INF (1.0 / 0.0L)
#define s21_TOLERANCE 1e-6
#define s21_PI 3.14159265358979323846

int compare_float(double f1, double f2);

// Computes cosine
long double s21_cos(double x);

// Computes sine
double s21_sin(double x);

// Computes absolute value of an integer value
int s21_abs(int x);

// Computes absolute value of a floating-point value
long double s21_fabs(double x);

// Computes square root
long double s21_sqrt(double x);

// Raises a number to the given power
// long double s21_pow(double base, double exp);