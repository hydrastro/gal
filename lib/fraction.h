#ifndef GAL_FRACTION_H
#define GAL_FRACTION_H
#include <stdbool.h>
#include <stddef.h>

/* if a term of a fraction is greater than this value, it will be printed as a float */
/* NOTE: it can be set to INT_MAX, for printing only fractions, or to 0, for printing only floats */
#define GAL_FRACTION_FLOAT_LIMIT 1000

/* sets how many digits can be printed after the floating point */
#define GAL_FRACTION_FLOAT_PRINTF_PRECISION 4

/* sets for how many digits two fractions can be considered approximately equal */
#define GAL_FRACTION_APPROXIMATION_DIGIT_PRECISION 3

/* defines a new type for fractions */
typedef struct fraction_t{
    int numerator;
    int denominator;
} fraction_t;

int gcd(int x, int y);
fraction_t getFraction(int numerator, int denominator);
fraction_t addFractions(fraction_t x, fraction_t y);
fraction_t multiplyFractionByInteger(fraction_t x, int y);
fraction_t subtractFractions(fraction_t x, fraction_t y);
fraction_t multiplyFractions(fraction_t x, fraction_t y);
fraction_t invertFraction(fraction_t x);
fraction_t fractionAbsoluteValue(fraction_t x);
fraction_t divideFractions(fraction_t x, fraction_t y);
fraction_t divideFractionByInteger(fraction_t x, int y);
fraction_t reduceFraction(fraction_t x);
fraction_t readFraction();
fraction_t invertFractionSign(fraction_t x);
void printFraction(fraction_t x);
int compareFractions(fraction_t x, fraction_t y);
fraction_t floatToFraction(float f);
fraction_t doubleToFraction(double d);
fraction_t powerFractionByDouble(fraction_t x, double y);
fraction_t powerFraction(fraction_t x, fraction_t y);
fraction_t rootFractionByInteger(fraction_t x, int y);
fraction_t sqrtFraction(fraction_t x);
fraction_t approximateFraction(fraction_t x);
bool fractionsApproximatelyEquals(fraction_t x, fraction_t y, int precision);
bool canBeSafelyMultiplied(int x, int y);
bool canBeSafelyAdded(int x, int y);
bool isDoubleFinite(double d);

#endif /* GAL_FRACTION_H */
