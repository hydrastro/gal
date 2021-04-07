#include <stdio.h>
#include "matrix.h"
#include "fraction.h"
#include "r3geometry.h"

/* code from the old side repository */
Plane_t readPlane(Plane_t plane){
    printf("ax + by + cz + d = 0\n");
    printf("a: ");
    plane.x = readFraction();
    printf("b: ");
    plane.y = readFraction();
    printf("c: ");
    plane.z = readFraction();
    printf("d: ");
    plane.d = readFraction();

    return plane;
}

void printPlane(Plane_t plane){
    printf("(");
    printFraction(plane.x);
    printf(")x + (");
    printFraction(plane.y);
    printf(")y + (");
    printFraction(plane.z);
    printf(")z + ");
    printFraction(plane.d);
    printf(" = 0\n");
}

fraction_t getLinearInvariant(int rows, fraction_t matrix[rows][rows]){

    return getMatrixTrace(rows - 1, matrix);
}

fraction_t getQuadraticInvariant(int rows, fraction_t matrix[rows][rows]){
    int currentRowsNumber, i, j;
    fraction_t tempDeterminant, invariant;
    for(i = 0; i < rows; i++){
        for(j = i + 1; j < rows; j++){
            tempDeterminant = multiplyFractions(matrix[i][i], matrix[j][j]);
            tempDeterminant = subtractFractions(tempDeterminant, multiplyFractions(matrix[i][j], matrix[j][i]));
            invariant = addFractions(invariant, tempDeterminant);            
        }
    }
    return invariant;
}

fraction_t getCubicInvariant(int rows, fraction_t matrix[rows][rows]){

    return getMatrixDeterminant(3, matrix);
}

fraction_t getQuarticInvariant(int rows, fraction_t matrix[rows][rows]){

    return getMatrixDeterminant(4, matrix);
}


/* TODO: define enum types for conics? and make a different function for the output */
void printConicType(fraction_t matrix[3][3]){
    int compairsonResult;
    fraction_t cubicInvariant, quadraticInvariant, linearInvariant, product, zeroFraction;
    cubicInvariant = getCubicInvariant(3, matrix);
    quadraticInvariant = getQuadraticInvariant(3, matrix);
    linearInvariant = getLinearInvariant(3, matrix);
    zeroFraction = getFraction(0, 1);

    compairsonResult = compareFractions(quadraticInvariant, zeroFraction);
    /* we are not considering the case 0/0; we need to make sure that every fraction (0 / x) with x not equal 0, is reduced to 0/1 */
    printf("\nConic type: ");
    if(compareFractions(cubicInvariant, getFraction(0, 1)) == 0){
        if(compairsonResult > 0){
            printf("conic which degenerates in two secand lines, imaginary and conjugated");
        } else if(compairsonResult < 0){
            printf("conic which degenerates in two secant lines, real and distinct");
        } else {
            printf("conic which degenereates in two parallel lines");
        }
    } else {
        if(compairsonResult > 0){
            product = multiplyFractions(cubicInvariant, linearInvariant);
            compairsonResult = compareFractions(product, zeroFraction);
            if(compairsonResult > 0){
                printf("imaginary ellipe");
            } else {
                printf("real ellipse");
            }
        } else if(compairsonResult < 0){
            printf("hyperbola");
        } else {
            printf("parabola");
        }
    }
    printf(".\n");
}

void printQuadraticType(fraction_t matrix[4][4]){
    int compairsonResult;
    fraction_t quarticInvariant, cubicInvariant, quadraticInvariant, linearInvariant, product, zeroFraction;
    quarticInvariant = getQuarticInvariant(4, matrix);
    cubicInvariant = getCubicInvariant(4, matrix);
    quadraticInvariant = getQuadraticInvariant(4, matrix);
    linearInvariant = getLinearInvariant(4, matrix);
    zeroFraction = getFraction(0, 1);
}
