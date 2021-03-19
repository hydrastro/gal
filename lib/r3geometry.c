#include <stdio.h>
#include "matrix.h"
#include "fraction.h"
#include "r3geometry.h"

// code from the old side repository
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
        printFraction(plane.x);
        printf("x + ");
        printFraction(plane.y);
        printf("y + ");
        printFraction(plane.z);
        printf("z + ");
        printFraction(plane.d);
        printf(" = 0\n");
}

// TODO: important: unify the getInvariant functions.....

fraction_t getConicCubicInvariant(fraction_t matrix[3][3]) {
//printMatrix(3, 3, matrix);printf("\n");

    return getMatrixDeterminant(3, matrix);
}
fraction_t getConicQuadraticInvariant(fraction_t matrix[3][3]) {
//printMatrix(2, 2, matrix);printf("\n");
    return getMatrixDeterminant(2, matrix);
}
fraction_t getConicLinearInvariant(fraction_t matrix[3][3]) {
//printMatrix(2, 2, matrix);printf("\n");

    return getMatrixTrace(2, matrix);
}

fraction_t getQuadraticQuarticInvariant(fraction_t matrix[4][4]) {

    return getMatrixDeterminant(4, matrix);
}
fraction_t getQuadraticCubicInvariant(fraction_t matrix[4][4]) {

    return getMatrixDeterminant(3, matrix);
}
fraction_t getQuadraticQuadraticInvariant(fraction_t matrix[4][4]) {
    fraction_t cubeSubmatrix[3][3], squareSubmatrix[2][2], invariant;
    getSubmatrix(3, 3, matrix, 3, 3, cubeSubmatrix);
    getSubmatrix(2, 2, cubeSubmatrix, 2, 2, squareSubmatrix);
    invariant = getMatrixDeterminant(2, squareSubmatrix);
    getSubmatrix(2, 2, cubeSubmatrix, 1, 1, squareSubmatrix);
    invariant = addFractions(invariant, getMatrixDeterminant(2, squareSubmatrix));
    getSubmatrix(2, 2, cubeSubmatrix, 0, 0, squareSubmatrix);
    invariant = addFractions(invariant, getMatrixDeterminant(2, squareSubmatrix));

    return invariant;
}
fraction_t getQuadraticLinearInvariant(fraction_t matrix[4][4]) {

    return getMatrixTrace(3, matrix);
}


// TODO: define enum types for conics? and make a different function for the output
void printConicType(fraction_t matrix[3][3]) {
    int compairsonResult;
    fraction_t cubicInvariant, quadraticInvariant, linearInvariant, product, zeroFraction;
    cubicInvariant = getConicCubicInvariant(matrix);
    quadraticInvariant = getConicQuadraticInvariant(matrix);
    linearInvariant = getConicLinearInvariant(matrix);
    zeroFraction = getFraction(0, 1);

printf("\nci: ");printFraction(cubicInvariant);
printf("\nqi: ");printFraction(quadraticInvariant);
printf("\nli: ");printFraction(linearInvariant);

    compairsonResult = compareFractions(quadraticInvariant, zeroFraction);
    // we are not considering the case 0/0
    // we need to make sure that every fraction (0 / x) with x not equal 0, is reduced to 0/1
    printf("\nConic type: ");
    if(compareFractions(cubicInvariant, getFraction(0, 1)) == 0) {
        if(compairsonResult > 0) {
            printf("conic which degenerates in two secand lines, imaginary and conjugated");
        } else if(compairsonResult < 0) {
            printf("coniche spezzate in due rette secanti, reali distinte");
            printf("conic which degenerates in two secant lines, real and distinct");
        } else {
            printf("conic which degenereates in two parallel lines");
        }
    } else {
        if(compairsonResult > 0) {
            product = multiplyFractions(cubicInvariant, linearInvariant);
            compairsonResult = compareFractions(product, zeroFraction);
            if(compairsonResult > 0) {
                printf("imaginary ellipe");
            } else {
                printf("real ellipse");
            }
        } else if(compairsonResult < 0) {
            printf("hyperbola");
        } else {
            printf("parabola");
        }
    }
    printf(".\n");
}

void printQuadraticType(fraction_t matrix[4][4]) {
    int compairsonResult;
    fraction_t quarticInvariant, cubicInvariant, quadraticInvariant, linearInvariant, product, zeroFraction;
    quarticInvariant = getQuadraticQuarticInvariant(matrix);
    cubicInvariant = getQuadraticCubicInvariant(matrix);
    quadraticInvariant = getQuadraticQuadraticInvariant(matrix);
    linearInvariant = getQuadraticLinearInvariant(matrix);
    zeroFraction = getFraction(0, 1);
}
