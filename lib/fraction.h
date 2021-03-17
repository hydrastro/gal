#ifndef GAL_FRACTION_H
#define GAL_FRACTION_H
#include <stdbool.h>
#include <stddef.h>

// defines a new type for fractions
typedef struct fraction_t{
    int numerator;
    int denominator;
} fraction_t;

typedef enum {number, symbol} element_t;

typedef struct stringElement_t{
    element_t type;
    fraction_t value;
    char symbol;
    struct stringElement_t *nextElement;
} stringElement_t;

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

// expression functions:
char *readString(size_t size);
stringElement_t *parseString(char *expression);
bool in_array(void *lookfor, void *array[], int arraySize);
void printStringChain(stringElement_t *start);

// TODO: float to fraction, fraction to float
// TODO: power fraction

int compareFractions(fraction_t x, fraction_t y);

#endif //GAL_FRACTION_H
