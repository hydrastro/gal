#ifdef GAL_EQUATION_H
#define GAL_EQUATION_H
#include "fraction.h"

// TODO: functions for this structure
typedef struct equationTerm_t{
    char variableName;
    fraction_t realCoefficient;
    fraction_t realExponent;
    fraction_t complexCoefficient;
    fraction_t complexExponent;
} equationTerm_t;


void getEquation();
void readEquation();
void printEquation();


void addEquations();
void subtractEquations();
void multiplyEquations();
void divideEquations();


void solveEquation();


#endif //GAL_EQUATION_H
