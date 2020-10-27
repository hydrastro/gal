#include <math.h>
#include <stdio.h>
#include "fraction_t.h"

// calculates the greatest common divisor between two integers
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

// returns a fraction type, reduced to the lowest terms, from two integers, a numerator and a denominator
struct fraction_t getFraction(int numerator, int denominator){
    fraction_t x;
    denominator = (denominator == 0) ? 1 : denominator;

    x.numerator = numerator;
    x.denominator = denominator;
    x = reduceFraction(x);

    return x;
}

// adds two fraction types and returns the result reduced to the lowest terms
struct fraction_t addFractions(fraction_t x, fraction_t y){
    int c = gcd(x.denominator, y.denominator);

    return getFraction(x.denominator / c * y.numerator + y.denominator / c * x.numerator, x.denominator / c * y.denominator);
}

// multiplies a fraction by an integer number and returns the result reduced to the lowest terms
struct fraction_t multiplyFractionByInteger(fraction_t x, int r){

    return getFraction(r * x.numerator, x.denominator);
}

// performs the subtraction between two fractions and returns the result reduced to the lowest terms
struct fraction_t subtractFractions(fraction_t x, fraction_t y){

    return addFractions(x, multiplyFractionByInteger(y, -1));
}

// performs the multiplication between two fractions and returns the result reduced to the lowest terms
struct fraction_t multiplyFractions(fraction_t x, fraction_t y){

    return getFraction(x.numerator * y.numerator, x.denominator * y.denominator);
}

// performs the division between two fractions and returns the result reduced to the lowest terms
struct fraction_t divideFractions(fraction_t x, fraction_t y){

    return multiplyFractions(x, invertFraction(y));
}

// divides a fraction by an integer
struct fraction_t divideFractionByInteger(fraction_t x, int r){

    return getFraction(r / x.numerator, x.denominator);
}


// returns, reduced to the lowest terms, the inverted fraction
struct fraction_t invertFraction(fraction_t x){

    return getFraction(x.denominator, x.numerator);
}

// returns, reduced to the lowest terms, the absolute value of the fraction
struct fraction_t fractionAbsoluteValue(fraction_t x){

    return getFraction(abs(x.numerator), abs(x.denominator));
}

// reduces a fraction to its minimal terms
struct fraction_t reduceFraction(fraction_t x){
    int c = gcd(x.numerator, x.denominator);
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

// reads a fraction, reduced to the lowest terms, from the user input ("numerator/denominator"), and returns it as a fraction type. The default denominator value is 1
struct fraction_t readFraction(){
    int x, y;
    if(scanf("%d/%d", &x, &y) == 1){
        y = 1;
    }

    return getFraction(x, y);
}

// inverts the sign of a fraction
struct fraction_t invertFractionSign(fraction_t x){

    return getFraction(-x.numerator, x.denominator);
}

// prints a fraction on the screen
void printFraction(fraction_t x){
    if(x.numerator == 0 || x.denominator == 1){
        if(x.denominator == 0){
            printf("undefined");
        } else {
            printf("%d", x.numerator);
        }
    } else {
        if(x.denominator == 0){
            printf("impossible");
        } else {
            printf("%d/%d", x.numerator, x.denominator);
        }
    }
}

// todo: expand matrix: add row/s, add column/s
// todo: reduce matrix: remove row/s, remove column/s