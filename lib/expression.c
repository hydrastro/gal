#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expression.h"
#include "fraction.h"

/* reads a string */
char *readString(size_t size){
    char *string;
    int character;
    size_t length;
    length = 0;
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
    string[length++] = '\0';

    return realloc(string, sizeof(char)*length);
}

/* creates the string chain */
expressionChainElement_t *parseString(char *expression){
    int i, numberCount, di;
    expressionChainElement_t *currentElement, *previousElement;
    fraction_t numberDigit;
    numberCount = 0;
    previousElement = NULL;

    for(i = strlen(expression) - 1; i >= 0; i--){
        currentElement = malloc(sizeof(expressionChainElement_t));
        currentElement->nextElement = previousElement;
        if(expression[i] <= '9' && expression[i] >= '0'){
             currentElement->type = EXPRESSION_STRING_TERM;
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
             /* here there's the need to differentiate between functions and brackets */
             currentElement->type = EXPRESSION_STRING_SYMBOL;
             currentElement->symbol = expression[i];
        }
        previousElement = currentElement;
    }

    return currentElement;
}

bool isInArray(void *lookfor, void *array[], int arraySize){
    int i;
    for(i = 0; i < arraySize; i++){
        if(strcmp(lookfor, array[i]) == 0){

            return true;
        }
    }

    return false;
}

void printStringChain(expressionChainElement_t *start){
    stringElement_t *cursor;
    cursor = start;
    while(cursor->nextElement != NULL){
        if(cursor->type == number){
            printFraction(cursor->value);
        } else {
            printf("%c", cursor->symbol);
        }
        cursor = cursor->nextElement;
    }
    if(cursor->type == number){
        printFraction(cursor->value);
    } else {
        printf("%c", cursor->symbol);
    }
}
