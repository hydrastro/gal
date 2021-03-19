#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fraction.h"

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
fraction_t getFraction(int numerator, int denominator){
    fraction_t x;
    denominator = (denominator == 0) ? 1 : denominator;

    x.numerator = numerator;
    x.denominator = denominator;
    x = reduceFraction(x);

    return x;
}

// adds two fraction types and returns the result reduced to the lowest terms
fraction_t addFractions(fraction_t x, fraction_t y){
    int c = gcd(x.denominator, y.denominator);

    return getFraction(x.denominator / c * y.numerator + y.denominator / c * x.numerator, x.denominator / c * y.denominator);
}

// multiplies a fraction by an integer number and returns the result reduced to the lowest terms
fraction_t multiplyFractionByInteger(fraction_t x, int y){

    return getFraction(y * x.numerator, x.denominator);
}

// performs the subtraction between two fractions and returns the result reduced to the lowest terms
fraction_t subtractFractions(fraction_t x, fraction_t y){

    return addFractions(x, multiplyFractionByInteger(y, -1));
}

// performs the multiplication between two fractions and returns the result reduced to the lowest terms
fraction_t multiplyFractions(fraction_t x, fraction_t y){

    return getFraction(x.numerator * y.numerator, x.denominator * y.denominator);
}

// performs the division between two fractions and returns the result reduced to the lowest terms
fraction_t divideFractions(fraction_t x, fraction_t y){

    return multiplyFractions(x, invertFraction(y));
}

// divides a fraction by an integer
fraction_t divideFractionByInteger(fraction_t x, int y){

    return getFraction(y / x.numerator, x.denominator);
}


// returns, reduced to the lowest terms, the inverted fraction
fraction_t invertFraction(fraction_t x){

    return getFraction(x.denominator, x.numerator);
}

// returns, reduced to the lowest terms, the absolute value of the fraction
fraction_t fractionAbsoluteValue(fraction_t x){

    return getFraction(abs(x.numerator), abs(x.denominator));
}

// reduces a fraction to its minimal terms
fraction_t reduceFraction(fraction_t x){
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
fraction_t readFraction(){
    int x, y;
    if(scanf("%d/%d", &x, &y) == 1){
        y = 1;
    }

    return getFraction(x, y);
}

// inverts the sign of a fraction
fraction_t invertFractionSign(fraction_t x){

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

char *readString(size_t size){
    char *string;
    int character;
    size_t length = 0;
    string = realloc(NULL, sizeof(char)*size);
    if(!string){

         return string;
    }
    while(EOF != (character = fgetc(stdin)) && character != '\n'){
        string[length++] = character;
        if(length == size){
            string = realloc(string, sizeof(char)*(size += 16));
            if(!string){

                return string;
            }
        }
    }
    string[length++]='\0';

    return realloc(string, sizeof(char)*length);
}

// creates the string chain
stringElement_t *parseString(char *expression){
    int i, numberCount = 0,di;
    stringElement_t *currentElement, *previousElement;
    fraction_t numberDigit;
    previousElement = NULL;

    for(i = strlen(expression) - 1; i >= 0; i--){
        currentElement = malloc(sizeof(stringElement_t));
        currentElement->nextElement = previousElement;
        if(expression[i] <= '9' && expression[i] >= '0'){
             currentElement->type = number;

             currentElement->value = getFraction(expression[i] - '0', 1);

             while(expression[i - 1] <= '9' && expression[i - 1] >= '0' && i > 0){
                        i--;
                 numberCount++;
                 numberDigit = getFraction((expression[i] - '0'), 1);
                   numberDigit = multiplyFractionByInteger(numberDigit, pow(10, numberCount));
                 currentElement->value = addFractions(currentElement->value, numberDigit);
             }
             numberCount = 0;
        } else {
             currentElement->type = symbol;
             currentElement->symbol = expression[i];
    }

        /*this is useless
        else if(expression[i] == '+'){
             currentElement->type = addition;
             currentElement->symbol = '+';
        } else if(expression[i] == '-'){
             currentElement->type = subtraction;
             currentElement->symbol = '-';
        } else if(expression[i] == '*'){
             currentElement->type = multiplication;
             currentElement->symbol = '*';
        } else if(expression[i] == '/'){
             currentElement->type = division;
             currentElement->symbol = '/';
        } else if(expression[i] == '^'){
             currentElement->type = power;
             currentElement->symbol = '^';
        } else if(expression[i] == '('){
             currentElement->type = openBracket;
             currentElement->symbol = '(';
        } else if(expression[i] == ')'){
             currentElement->type = closedBracket;
             currentElement->symbol = ')';
        } else {
//            if(!(&currentCharacter == "\0" && i >= 0)){

                 // invalid characters
                //return NULL;
//            }
        }*/
        previousElement = currentElement;
    }

    return currentElement;
}

bool in_array(void *lookfor, void *array[], int arraySize){
    int i;
    for(i = 0; i < arraySize; i++){
        if(strcmp(lookfor, array[i]) == 0){

            return true;
        }
    }

    return false;
}

void printStringChain(stringElement_t *start){
    stringElement_t *cursor;
    cursor = start;
    while(cursor->nextElement != NULL){
        if(cursor->type == number){
            printFraction(cursor->value);
        } else{
            printf("%c", cursor->symbol);
        }
        cursor = cursor->nextElement;
    }
        if(cursor->type == number){
            printFraction(cursor->value);
        } else{
            printf("%c", cursor->symbol);
        }
}

// compares two fractions
int compareFractions(fraction_t x, fraction_t y){
    fraction_t reducedX, reducedY;
    reducedX = reduceFraction(x);
    reducedY = reduceFraction(y);

    return (reducedX.numerator * reducedY.denominator * reducedX.denominator) - (reducedY.numerator * reducedX.denominator * reducedX.denominator);
}

// gets the fraction from a given float
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

// gets the fraction from a given double
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

// calculates the power of a given fraction
fraction_t powerFractionByDouble(fraction_t x, double y){
    double temp;
    temp = (double)x.numerator / (double)x.denominator;
    temp = pow(temp, y);

    return doubleToFraction(temp);
}

// calcualtes the fractional power of a given fraction
fraction_t powerFraction(fraction_t x, fraction_t y){
    double temp;
    temp = (double)y.numerator / (double)y.denominator;

    return powerFractionByDouble(x, temp);
}

// returns the n-root of a given fraction
fraction_t rootFractionByInteger(fraction_t x, int y){

    return powerFractionByDouble(x, 1.0 / (float)y);
}

fraction_t sqrtFraction(fraction_t x){

    return rootFractionByInteger(x, 2);
}
