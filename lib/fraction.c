#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fraction.h"

/* if a term of a fraction is greater than this value, it will be printed as a float */
/* NOTE: it can be set to INT_MAX, for printing only fractions, or to 0, for printing only floats */
#define GAL_FRACTION_FLOAT_LIMIT 0

/* sets how many digits can be printed after the floating point */
#define GAL_FRACTION_FLOAT_PRINTF_PRECISION 4

/* calculates the greatest common divisor between two integers */
int gcd(int x, int y){
    int gcd, remainder;
    while(x != 0){
        remainder = y % x;
        y = x;
        x = remainder;
    }
    gcd = y;

    return gcd;
}

/* returns a fraction type, reduced to the lowest terms, from two integers, a numerator and a denominator */
fraction_t getFraction(int numerator, int denominator){
    fraction_t x;
    denominator = (denominator == 0) ? 1 : denominator;
    x.numerator = numerator;
    x.denominator = denominator;
    x = reduceFraction(x);

    return x;
}

/* adds two fraction types and returns the result reduced to the lowest terms */
fraction_t addFractions(fraction_t x, fraction_t y){
    int c, l, m, n;
    c = gcd(x.denominator, y.denominator);
    l = (x.denominator / c) * y.numerator;
    m = (y.denominator / c) * x.numerator;
    n = (x.denominator / c) * y.denominator;
    if((y.numerator != 0 && (l / y.numerator) != (x.denominator / c)) || (x.numerator != 0 && (m / x.numerator) != (y.denominator / c)) || (y.denominator != 00 && (n / y.denominator) != (x.denominator / c))){
        /* overflowing */
        if((abs(x.numerator) > abs(y.numerator) && abs(x.numerator) > abs(y.denominator)) || (abs(x.numerator) > abs(y.numerator) && abs(x.numerator) > abs(y.denominator))){

            return addFractions(approximateFraction(x), y);
        }

        return addFractions(x, approximateFraction(y));
    }

    return getFraction(x.denominator / c * y.numerator + y.denominator / c * x.numerator, x.denominator / c * y.denominator);
}



/* multiplies a fraction by an integer number and returns the result reduced to the lowest terms */
fraction_t multiplyFractionByInteger(fraction_t x, int y){
    int c;
    c = y * x.numerator;
    if(y != 0 &&  c / y != x.numerator){

        return multiplyFractionByInteger(approximateFraction(x), y);
    }

    return getFraction(y * x.numerator, x.denominator);
}

/* performs the subtraction between two fractions and returns the result reduced to the lowest terms */
fraction_t subtractFractions(fraction_t x, fraction_t y){

    return addFractions(x, multiplyFractionByInteger(y, -1));
}

/* performs the multiplication between two fractions and returns the result reduced to the lowest terms */
fraction_t multiplyFractions(fraction_t x, fraction_t y){
    int c, d;
    c = x.numerator * y.numerator;
    d = x.denominator * y.denominator;
    if((x.numerator != 0) && ((c / x.numerator) != y.numerator)){
        if(abs(x.numerator) > abs(y.numerator)){

            return multiplyFractions(approximateFraction(x), y);
        }

        return multiplyFractions(x, approximateFraction(y));
    }
    if((x.denominator != 0) && ((d / x.denominator) != y.denominator)){
        if(abs(x.denominator) > abs(y.denominator)){

            return multiplyFractions(approximateFraction(x), y);
        }

        return multiplyFractions(x, approximateFraction(y));
    }

    return getFraction(x.numerator * y.numerator, x.denominator * y.denominator);
}

/* performs the division between two fractions and returns the result reduced to the lowest terms */
fraction_t divideFractions(fraction_t x, fraction_t y){

    return multiplyFractions(x, invertFraction(y));
}

/* divides a fraction by an integer */
fraction_t divideFractionByInteger(fraction_t x, int y){

    return getFraction(y / x.numerator, x.denominator);
}


/* returns, reduced to the lowest terms, the inverted fraction */
fraction_t invertFraction(fraction_t x){

    return getFraction(x.denominator, x.numerator);
}

/* returns, reduced to the lowest terms, the absolute value of the fraction */
fraction_t fractionAbsoluteValue(fraction_t x){

    return getFraction(abs(x.numerator), abs(x.denominator));
}

/* reduces a fraction to its minimal terms */
fraction_t reduceFraction(fraction_t x){
    int c;
    c = gcd(x.numerator, x.denominator);
    if(abs(c) != 1){
        x.numerator /= c;
        x.denominator /= c;
    } else {
        x.numerator = x.numerator;
        x.denominator = x.denominator;
    }
    if (x.denominator < 0){
        x.numerator = -x.numerator;
        x.denominator = -x.denominator;
    }

    return x;
}

/* reads a fraction, reduced to the lowest terms, from the user input ("numerator/denominator"), and returns it as a fraction type. The default denominator value is 1 */
fraction_t readFraction(){
    int x, y;
    if(scanf("%d/%d", &x, &y) == 1){
        y = 1;
    }

    return getFraction(x, y);
}

/* inverts the sign of a fraction */
fraction_t invertFractionSign(fraction_t x){

    return getFraction(-x.numerator, x.denominator);
}

/* prints a fraction on the screen */
void printFraction(fraction_t x){
    if(x.numerator == 0 || x.denominator == 1){
        if(x.denominator == 0){
            printf("undefined");

            return;
        }
        printf("%d", x.numerator);

        return;
    }
    if(x.denominator == 0){
        printf("impossible");

        return;
    }
    if(x.numerator < GAL_FRACTION_FLOAT_LIMIT && x.denominator < GAL_FRACTION_FLOAT_LIMIT){
        printf("%d/%d", x.numerator, x.denominator);

        return;
    }
    printf("%.*f", GAL_FRACTION_FLOAT_PRINTF_PRECISION, (double)x.numerator / (double)x.denominator);

    return;
}

/* compares two fractions */
int compareFractions(fraction_t x, fraction_t y){
    fraction_t reducedX, reducedY;
    reducedX = reduceFraction(x);
    reducedY = reduceFraction(y);

    return (reducedX.numerator * reducedY.denominator * reducedX.denominator) - (reducedY.numerator * reducedX.denominator * reducedX.denominator);
}

/* gets the fraction from a given float */
fraction_t floatToFraction(float f){
    int numerator, denominator;
    denominator = 1;
    numerator = (int)f;
    while(f - (int)f != 0.0f && (int)(f * 10.0f) > 0){
        f *= 10.0f;
        numerator = (int)f;
        denominator *= 10;
    }

    return getFraction(numerator, denominator);
}

/* gets the fraction from a given double */
fraction_t doubleToFraction(double d){
    int numerator, denominator;
    denominator = 1;
    numerator = (int)d;
    while(d - (int)d != 0.0 && (int)(d * 10.0) > 0){
        d *= 10.0;
        numerator = (int)d;
        denominator *= 10;
    }

    return getFraction(numerator, denominator);
}

/* calculates the power of a given fraction */
fraction_t powerFractionByDouble(fraction_t x, double y){
    double temp;
    temp = (double)x.numerator / (double)x.denominator;
    temp = pow(temp, y);

    return doubleToFraction(temp);
}

/* calcualtes the fractional power of a given fraction */
fraction_t powerFraction(fraction_t x, fraction_t y){
    double temp;
    temp = (double)y.numerator / (double)y.denominator;

    return powerFractionByDouble(x, temp);
}

/* returns the n-root of a given fraction */
fraction_t rootFractionByInteger(fraction_t x, int y){

    return powerFractionByDouble(x, 1.0 / (float)y);
}

/* returns the square root of a given fraction */
fraction_t sqrtFraction(fraction_t x){

    return rootFractionByInteger(x, 2);
}

/* approximates a fraction */
fraction_t approximateFraction(fraction_t x){
    int i, j;
    i = 0;
    j = 0;
    if(x.numerator % 10 >= 5){
        i++;
    }
    if(x.denominator % 10 >= 5){
        j++;
    }
    x.numerator /= 10;
    x.denominator /= 10;
    x.numerator += i;
    x.denominator += j;

    return getFraction(x.numerator, x.denominator);
}
