#include <stdio.h>
#include <stdlib.h>
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
lineParametricForm_t readLineParametricForm(){
    fraction_t zeroFraction;
    lineParametricForm_t line;
    printf("Application point coordinates:\n");
    line.applicationPoint = readPoint();
    printf("Direction vector (by row, transposed):\n");
    readVector(line.directionVector);
    zeroFraction = getFraction(0, 1);
    if(compareFractions(line.directionVector[0][0], zeroFraction) == 0 && compareFractions(line.directionVector[0][1], zeroFraction) == 0 && compareFractions(line.directionVector[0][2], zeroFraction) == 0){
        fprintf(stderr, "\nerror: invalid direction vector entered\n");

        exit(-1);
    }
    return line;
}

/* prints a line in parametric form */
void printLineParametricForm(lineParametricForm_t line){
    printf("Application point coordinates:\n");
    printPoint(line.applicationPoint);
    printf("Direction vector:\n");
    printMatrix(1, 3, line.directionVector);
}

/* reads a line in cartesian from */
lineCartesianForm_t readLineCartesianForm(){
    fraction_t planesMatrix[2][4];
    lineCartesianForm_t line;
    printf("First plane:\n");
    line.firstPlane = readPlane();
    printf("Second plane:\n");
    line.secondPlane = readPlane();
    getCartesianLineMatrix(line, planesMatrix);
    if(getMatrixRank(2, 4, planesMatrix) == 1){
        fprintf(stderr, "\nerror: invalid planes entered\n");

        exit(-1);
    }

    return line;
}

/* prints a line in cartesian form */
void printLineCartesianForm(lineCartesianForm_t line){
    printf("First plane:\n");
    printPlane(line.firstPlane);
    printf("Second plane:\n");
    printPlane(line.secondPlane);
}

/* reads a line either parametric or cartesian */
line_t readLine(){
    line_t line;
    fraction_t response;
    printf("In which form is the line?\n0. Parametric form.\n1. Cartesian form.\n");
    response = readFraction();
    if(response.numerator == 0){
        line.parametricForm = readLineParametricForm();
        line.cartesianForm = lineParametricToCartesianForm(line.parametricForm);
    } else if(response.numerator == 1){
        line.cartesianForm = readLineCartesianForm();
        line.parametricForm = lineCartesianToParametricForm(line.cartesianForm);
    } else {
        fprintf(stderr, "\nerror: invalid line form entered.\n");

        exit(-1);
    }

    return line;
}

/* prints both parametric and cartesian form of a given line */
void printLine(line_t line){
    printLineParametricForm(line.parametricForm);
    printLineCartesianForm(line.cartesianForm);
}

/* reads a point from the user input */
Point_t readPoint(){
    Point_t point;
    printf("x: ");
    point.x = readFraction();
    printf("y: ");
    point.y = readFraction();
    printf("z: ");
    point.z = readFraction();

    return point;
}

/* prints a point */
void printPoint(Point_t point){
    printf("(");
    printFraction(point.x);
    printf(", ");
    printFraction(point.y);
    printf(", ");
    printFraction(point.z);
    printf(")\n");
}

/* reads a vector (a 1x3 matrix) from the user input */
void readVector(fraction_t vector[1][3]){
    printf("x: ");
    vector[0][0] = readFraction();
    printf("y: ");
    vector[0][1] = readFraction();
    printf("z: ");
    vector[0][2] = readFraction();
}

/* prints a vector (a 1x3 matrix) */
void printVector(fraction_t vector[1][3]){
    printf("(");
    printFraction(vector[0][0]);
    printf(", ");
    printFraction(vector[0][1]);
    printf(", ");
    printFraction(vector[0][2]);
    printf(")\n");
}

/* calculates the parametric form of a given cartesian form line */
lineParametricForm_t lineCartesianToParametricForm(lineCartesianForm_t line){
    lineParametricForm_t parametricLine;
    fraction_t planesMatrix[2][4], completeMatrix[3][5], coefficientsMatrix[3][3], termsMatrix[3][2];
    getCartesianLineMatrix(line, planesMatrix);
    expandMatrix(2, 4, planesMatrix, 2, 3, 1, 1, completeMatrix);
    splitMatrixVertically(3, 5, completeMatrix, 3, coefficientsMatrix, termsMatrix);
    splitMatrixVertically(3, 5, completeMatrix, 3, coefficientsMatrix, termsMatrix);
    termsMatrix[0][1] = invertFractionSign(termsMatrix[0][1]);
    termsMatrix[1][1] = invertFractionSign(termsMatrix[1][1]);
    termsMatrix[2][0] = getFraction(1, 1);
    completeMatrixRows(3, 3, coefficientsMatrix, coefficientsMatrix);
    composeMatricesHorizontally(3, 3, 2, coefficientsMatrix, termsMatrix, completeMatrix);
    gaussJordanElimination(3, 5, completeMatrix, completeMatrix);
    /* putting the data in the variable */
    parametricLine.directionVector[0][0] = completeMatrix[0][3];
    parametricLine.directionVector[0][1] = completeMatrix[1][3];
    parametricLine.directionVector[0][2] = completeMatrix[2][3];
    parametricLine.applicationPoint.x = completeMatrix[0][4];
    parametricLine.applicationPoint.y = completeMatrix[1][4];
    parametricLine.applicationPoint.z = completeMatrix[2][4];

    return parametricLine;
}

/* calculates the cartesian form of a given parametric form line */
lineCartesianForm_t lineParametricToCartesianForm(lineParametricForm_t line){
    lineCartesianForm_t cartesianLine;
    cartesianLine.firstPlane.x = getFraction(1, 1);

    return cartesianLine;
}

/* calculates the matrix associated with a given plane */
void getPlaneMatrix(Plane_t plane, fraction_t matrix[1][4]){
    matrix[0][0] = plane.x;
    matrix[0][1] = plane.y;
    matrix[0][2] = plane.z;
    matrix[0][3] = plane.d;
}

/* calculates the matrix associated with a given point */
void getPointMatrix(Point_t point, fraction_t matrix[1][3]){
    matrix[0][0] = point.x;
    matrix[0][1] = point.y;
    matrix[0][2] = point.z;
}

/* calculates the matrix associated with a given cartesian form line */
void getCartesianLineMatrix(lineCartesianForm_t line, fraction_t matrix[2][4]){
    fraction_t firstPlaneMatrix[1][4], secondPlaneMatrix[1][4];
    getPlaneMatrix(line.firstPlane, firstPlaneMatrix);
    getPlaneMatrix(line.secondPlane, secondPlaneMatrix);
    changeMatrixRow(2, 4, matrix, 0, firstPlaneMatrix);
    changeMatrixRow(2, 4, matrix, 1, secondPlaneMatrix);
}

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
                        printf("cilinder, either imaginary (hasn't real points) or elliptic (has real points)");
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
                    printf("couple of parallel planes: either real and distinct (has real points) or imaginary and conjugated (hasn't real points)");
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
