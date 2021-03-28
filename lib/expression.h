#ifndef GAL_EXPRESSION_H
#define GAL_EXPRESSION_H
#include <stdbool.h>
#include "fraction.h"

typedef struct expressionTerm_t{
    char variableName;
    fraction_t realCoefficient;
    fraction_t realExponent;
    fraction_t complexCoefficient;
    fraction_t complexExponent;
} expressionTerm_t;

typedef enum {FUNCTION_SIN, FUNCTION_COS, FUNCTION_TAN, FUNCTION_LOG} expressionFunction_t;

typedef enum {EXPRESSION_STRING_TERM, EXPRESSION_STRING_SYMBOL, EXPRESSION_STRING_FUNCTION} expressionElementType_t;

typedef struct expressionChainElement_t{
    expressionElementType_t type;
    expressionTerm_t value;
    char symbol;
    expressionFunction_t functionName;
    struct expressionChainElement_t *nextElement;
} expressionChainElement_t;

char *readString(size_t size);
expressionChainElement_t *parseString(char *expression);
bool isInArray(void *lookfor, void *array[], int arraySize);
void printStringChain(expressionChainElement_t *start);

/*
void getExpression();
void readExpression();
void printExpression();
void addExpressions();
void subtractExpressions();
void multiplyExpressions();
void divideExpressions();
void solveExpression();
*/

#endif /* GAL_EXPRESSION_H */
