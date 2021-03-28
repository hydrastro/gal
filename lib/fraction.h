#ifndef GAL_FRACTION_H
#define GAL_FRACTION_H
#include <stddef.h>

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
#endif /* GAL_FRACTION_H */
