#include <stdio.h>
#include "fraction.h"
#include "matrix.h"
#include "r3geometry.h"

/* reads a plane form the user input*/
Plane_t readPlane(){
    Plane_t plane;
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

/* prints a given plane */
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

/* reads a line in parametric from */
/* START TODO */
lineParametricForm_t readLineParametricForm(){
    Point_t applicationPoint;
    Vector_t directionVector;
}

/* reads a line in cartesian from */
lineCartesianForm_t readLineCartesianForm(){
    Plane_t firstPlane;
    Plane_t secondPlane;
}

/* reads a point from the user input */
Point_t readPoint(){
}

/* reads a vector from the user input */
Vector_t readVector(){
}
/* END TODO */

/* calculates the linear invariant of a given conic or quadric */
fraction_t getLinearInvariant(int rows, fraction_t matrix[rows][rows]){
    fraction_t submatrix[rows - 1][rows - 1];
    getSubmatrix(rows, rows, matrix, rows - 1, rows - 1, submatrix);

    return getMatrixTrace(rows - 1, submatrix);
}

/* calculates the quadratic invariant of a given conic or quadric */
fraction_t getQuadraticInvariant(int rows, fraction_t matrix[rows][rows]){
    int i, j;
    fraction_t tempDeterminant, invariant;
    invariant = getFraction(0, 1);
    for(i = 0; i < rows - 1; i++){
        for(j = i + 1; j < rows - 1; j++){
            tempDeterminant = multiplyFractions(matrix[i][i], matrix[j][j]);
            tempDeterminant = subtractFractions(tempDeterminant, multiplyFractions(matrix[i][j], matrix[j][i]));
            invariant = addFractions(invariant, tempDeterminant);
        }
    }

    return invariant;
}

/* calculates the cubic invariant of a given conic or quadric */
fraction_t getCubicInvariant(int rows, fraction_t matrix[rows][rows]){
    int i, j;
    fraction_t tempMatrix[rows - 1][rows - 1];
    if(rows == 3){
        copyMatrix(rows, rows, matrix, tempMatrix);
    } else {
        /* not sure if this is suitable for rows > 4 */
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                tempMatrix[i][j] = matrix[i][j];
            }
        }
    }
    
    return getMatrixDeterminant(3, tempMatrix);
}

/* calculates the quartic invariant of a given quadric */
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
    if(compareFractions(cubicInvariant, zeroFraction) == 0){
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
                printf("imaginary ellipse");
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

void printQuadricType(fraction_t matrix[4][4]){
    int compairsonResult, rank, multiplicationCompairsonResult, quadraticRank, i;
    fraction_t quarticInvariant, cubicInvariant, quadraticInvariant, linearInvariant, zeroFraction, quadraticSubmatrix[3][3], quadraticEigenvalues[3][1], eigenvalueProduct;
    quarticInvariant = getQuarticInvariant(4, matrix);
    cubicInvariant = getCubicInvariant(4, matrix);
    quadraticInvariant = getQuadraticInvariant(4, matrix);
    linearInvariant = getLinearInvariant(4, matrix);
    zeroFraction = getFraction(0, 1);
    rank = getMatrixRank(4, 4, matrix);
    compairsonResult = compareFractions(quadraticInvariant, zeroFraction);
    multiplicationCompairsonResult = compareFractions(multiplyFractions(linearInvariant, cubicInvariant), zeroFraction);

    printf("\nQuadric type: ");
    if(compareFractions(quarticInvariant, zeroFraction) == 0){
        switch(rank){
            default:
            case 3:
                if(compareFractions(cubicInvariant, zeroFraction) == 0){
                    if(compairsonResult > 0){
                        printf("cilinder, imaginary (hasn't real points) or elliptic (has real points), idk");
                    } else if(compairsonResult < 0){
                        printf("hyperbolic cylinder");
                    } else {
                        printf("parabolic cylinder");
                    }
                } else {
                    if(compairsonResult > 0 &&  multiplicationCompairsonResult > 0){
                        printf("imaginary cone");
                    } else {
                        printf("real cone");
                    }
                }
            break;
            case 2:
                getSubmatrix(4, 4, matrix, 3, 3, quadraticSubmatrix);
                quadraticRank = getMatrixRank(3, 3, quadraticSubmatrix);
                if(quadraticRank == 2){
                    findEigenvalues(3, quadraticSubmatrix, quadraticEigenvalues);
                    eigenvalueProduct = getFraction(1, 1);
                    for(i = 0; i < 3; i++){
                        if(!fractionsApproximatelyEquals(quadraticEigenvalues[i][0], zeroFraction, GAL_FRACTION_APPROXIMATION_DIGIT_PRECISION)){
                            eigenvalueProduct = multiplyFractions(eigenvalueProduct, quadraticEigenvalues[i][0]);
                        }
                    }
                    if(compareFractions(eigenvalueProduct, zeroFraction) > 0){
                        printf("couple of imaginary conjugated secant planes");
                    } else {
                        printf("couple of real secant planes.");
                    }
                } else {
                    printf("coubple of parallel planes: real (has real points) or imaginary and conjugated (hasn't real points)");
                }
            break;
            case 1:
                printf("double plane");
            break;
        }
    } else {
        if(compareFractions(cubicInvariant, zeroFraction) == 0){
            if(compareFractions(quarticInvariant, zeroFraction) > 0){
                printf("hyperbolic paraboloid");
            } else {
                printf("elliptic paraboloid");
            }
        } else {
            if(compareFractions(quarticInvariant, zeroFraction) > 0){
                if(compairsonResult > 0 &&  multiplicationCompairsonResult > 0){
                    printf("imaginary ellipsoid");
                } else {
                    printf("one-sheet hyperboloid");
                }
            } else {
                if(compairsonResult > 0 &&  multiplicationCompairsonResult > 0){
                    printf("real ellipsoid");
                } else {
                    printf("two-sheet hyperboloid");
                }
            }
        }
    }
    printf(".\n");
}
