#ifndef FRACTION_T
#define FRACTION_T

// defines a new type for fractions
typedef struct fraction_t{
  int numerator;
  int denominator;
} fraction_t;

int gcd(int x, int y);
struct fraction_t getFraction(int numerator, int denominator);
struct fraction_t addFractions(fraction_t x, fraction_t y);
struct fraction_t multiplyFractionByInteger(fraction_t x, int r);
struct fraction_t subtractFractions(fraction_t x, fraction_t y);
struct fraction_t multiplyFractions(fraction_t x, fraction_t y);
struct fraction_t invertFraction(fraction_t x);
struct fraction_t fractionAbsoluteValue(fraction_t x);
struct fraction_t divideFractions(fraction_t x, fraction_t y);
struct fraction_t divideFractionByInteger(fraction_t x, int r);
struct fraction_t reduceFraction(fraction_t x);
struct fraction_t readFraction();
struct fraction_t invertFractionSign(fraction_t x);
void printFraction(fraction_t x);

#endif //FRACTION_T
