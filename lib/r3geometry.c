#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"
#include "matrix.h"
#include "r3geometry.h"

/* reads a plane form the user input*/
plane_t readPlane(){
    plane_t plane;
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
void printPlane(plane_t plane){
    if(plane.x.numerator != 0){
        if(plane.x.denominator != 1){
            printf("(");
        }
        printFraction(plane.x);
        if(plane.x.denominator != 1){
            printf(")");
        }
        printf("x + ");
    }
    if(plane.y.numerator != 0){
        if(plane.y.denominator != 1){
            printf("(");
        }
        printFraction(plane.y);
        if(plane.y.denominator != 1){
            printf(")");
        }
        printf("y + ");
    }
    if(plane.z.numerator != 0){
        if(plane.z.denominator != 1){
            printf("(");
        }
        printFraction(plane.z);
        if(plane.z.denominator != 1){
            printf(")");
        }
        printf("z ");
    }
    if(plane.x.denominator != 0){
        printf("+ ");
        printFraction(plane.d);
    }

    printf(" = 0\n");
}

/* reads a line in parametric from */
lineParametricForm_t readLineParametricForm(){
    fraction_t zeroFraction;
    lineParametricForm_t line;
    printf("Application point coordinates:\n");
    line.applicationPoint = readPoint();
    printf("Direction vector:\n");
    readVector(line.directionVector);
    zeroFraction = getFraction(0, 1);
    if(compareFractions(line.directionVector[0][0], zeroFraction) == 0 && compareFractions(line.directionVector[0][1], zeroFraction) == 0 && compareFractions(line.directionVector[0][2], zeroFraction) == 0){
        fprintf(stderr, "\nerror: invalid direction vector entered\n");

        exit(-1);
    }
    printf("\n");

    return line;
}

/* prints a line in parametric form */
void printLineParametricForm(lineParametricForm_t line){
    printf("Application point coordinates: ");
    printPoint(line.applicationPoint);
    printf("\n");
    printf("Direction vector: ");
    printVector(line.directionVector);
    printf("\n");
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
    printf("\n");

    return line;
}

/* prints a line in cartesian form */
void printLineCartesianForm(lineCartesianForm_t line){
    printf("First plane: ");
    printPlane(line.firstPlane);
    printf("Second plane: ");
    printPlane(line.secondPlane);
    printf("\n");
}

/* reads a line either parametric or cartesian */
line_t readLine(){
    line_t line;
    fraction_t response;
    printf("In which form is the line?\n0. Parametric form.\n1. Cartesian form.\n\nSelect an option: ");
    response = readFraction();
    printf("\n");
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
point_t readPoint(){
    point_t point;
    printf("x: ");
    point.x = readFraction();
    printf("y: ");
    point.y = readFraction();
    printf("z: ");
    point.z = readFraction();

    return point;
}

/* prints a point */
void printPoint(point_t point){
    printf("(");
    printFraction(point.x);
    printf(", ");
    printFraction(point.y);
    printf(", ");
    printFraction(point.z);
    printf(")");
}

/* reads a vector (a 1x3 matrix) from the user input */
void readVector(fraction_t vector[3][1]){
    printf("x: ");
    vector[0][0] = readFraction();
    printf("y: ");
    vector[1][0] = readFraction();
    printf("z: ");
    vector[2][0] = readFraction();
}

/* prints a vector (a 1x3 matrix) */
void printVector(fraction_t vector[3][1]){
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
    parametricLine.directionVector[1][0] = completeMatrix[1][3];
    parametricLine.directionVector[2][0] = completeMatrix[2][3];
    parametricLine.applicationPoint.x = completeMatrix[0][4];
    parametricLine.applicationPoint.y = completeMatrix[1][4];
    parametricLine.applicationPoint.z = completeMatrix[2][4];

    return parametricLine;
}

/* calculates the cartesian form of a given parametric form line */
lineCartesianForm_t lineParametricToCartesianForm(lineParametricForm_t line){
    lineCartesianForm_t cartesianLine;
    fraction_t completeMatrix[3][5], identityMatrix[3][3], tempPoint[3][1], resultMatrix[2][4], tempPlane[1][4];
    getIdentityMatrix(3, identityMatrix);
    insertMatrixIntoMatrix(3, 5, completeMatrix, 0, 1, 3, 3, identityMatrix);
    getPointMatrix(line.applicationPoint, tempPoint);
    insertMatrixIntoMatrix(3, 5, completeMatrix, 0, 4, 3, 1, tempPoint);
    completeMatrix[0][4] = invertFractionSign(completeMatrix[0][4]);
    completeMatrix[1][4] = invertFractionSign(completeMatrix[1][4]);
    completeMatrix[2][4] = invertFractionSign(completeMatrix[2][4]);
    cartesianLine.firstPlane.x = getFraction(1, 1);
    insertMatrixIntoMatrix(3, 5, completeMatrix, 0, 0, 3, 1, line.directionVector);
    gaussJordanElimination(3, 5, completeMatrix, completeMatrix);
    if(getPivotColumn(3, 5, completeMatrix, 0) < getPivotColumn(3, 5, completeMatrix, 1)){
        swapRows(3, 5, completeMatrix, 0, 1);
    }
    if(getPivotColumn(3, 5, completeMatrix, 0) < getPivotColumn(3, 5, completeMatrix, 2)){
        swapRows(3, 5, completeMatrix, 0, 2);
    }
    getSubmatrix(3, 5, completeMatrix, 0, 0, resultMatrix);
    getMatrixRow(2, 4, resultMatrix, 0, tempPlane);
    cartesianLine.firstPlane = getPlaneFromMatrix(tempPlane);
    getMatrixRow(2, 4, resultMatrix, 1, tempPlane);
    cartesianLine.secondPlane = getPlaneFromMatrix(tempPlane);

    return cartesianLine;
}

/* calculates the matrix associated with a given plane */
void getPlaneMatrix(plane_t plane, fraction_t matrix[1][4]){
    matrix[0][0] = plane.x;
    matrix[0][1] = plane.y;
    matrix[0][2] = plane.z;
    matrix[0][3] = plane.d;
}

/* calculates the plane associated to a given row matrix */
plane_t getPlaneFromMatrix(fraction_t matrix[1][4]){
    plane_t plane;
    plane.x = matrix[0][0];
    plane.y = matrix[0][1];
    plane.z = matrix[0][2];
    plane.d = matrix[0][3];

    return plane;
}

/* calculates the matrix associated with a given point */
void getPointMatrix(point_t point, fraction_t matrix[3][1]){
    matrix[0][0] = point.x;
    matrix[1][0] = point.y;
    matrix[2][0] = point.z;
}

/* calculates the matrix associated with a given cartesian form line */
void getCartesianLineMatrix(lineCartesianForm_t line, fraction_t matrix[2][4]){
    fraction_t firstPlaneMatrix[1][4], secondPlaneMatrix[1][4];
    getPlaneMatrix(line.firstPlane, firstPlaneMatrix);
    getPlaneMatrix(line.secondPlane, secondPlaneMatrix);
    changeMatrixRow(2, 4, matrix, 0, firstPlaneMatrix);
    changeMatrixRow(2, 4, matrix, 1, secondPlaneMatrix);
}

/* calculates the reciprocal position of two given lines */
int getLinesReciprocalPosition(line_t firstLine, line_t secondLine){
    int rank;
    fraction_t completeMatrix[3][3], tempRow[1][3], tempColumnPoint[3][1], tempRowPoint[1][3], coefficientsMatrix[2][3];
    transposeMatrix(3, 1, firstLine.parametricForm.directionVector, tempRow);
    insertMatrixIntoMatrix(3, 3, completeMatrix, 0, 0, 1, 3, tempRow);
    transposeMatrix(3, 1, secondLine.parametricForm.directionVector, tempRow);
    insertMatrixIntoMatrix(3, 3, completeMatrix, 1, 0, 1, 3, tempRow);
    getPointMatrix(firstLine.parametricForm.applicationPoint, tempColumnPoint);
    transposeMatrix(3, 1, tempColumnPoint, tempRow);
    getPointMatrix(secondLine.parametricForm.applicationPoint, tempColumnPoint);
    transposeMatrix(3, 1, tempColumnPoint, tempRowPoint);
    subtractMatrix(1, 3, tempRow, tempRowPoint, tempRow);
    insertMatrixIntoMatrix(3, 3, completeMatrix, 2, 0, 1, 3, tempRow);
    rank = getMatrixRank(3, 3, completeMatrix);
    if(rank == 3){
        /* the lines do not intersect, niether are parallel */

        return 3;
    } else if(rank == 2){
        completeMatrix[2][0].numerator = 0;
        completeMatrix[2][1].numerator = 0;
        completeMatrix[2][2].numerator = 0;
        rank = getMatrixRank(3, 3, completeMatrix);
        if(rank == 2){
            /* the lines intersect */

            return 2;
        } else {
            /* the lines are parallel */

            return 1;
        }
    } else {
        /* the lines are coincident */

        return 0;
    }
}

/* calculates the intersection point of two lines */
point_t getLinesIntersectionPoint(line_t firstLine, line_t secondLine){
    int rank;
    fraction_t completeMatrix[3][4], tempRow[1][4];
    point_t intersectionPoint;
    if(getLinesReciprocalPosition(firstLine, secondLine) != 2){
        fprintf(stderr, "\nerror: the two lines do not intersect.\n");

        exit(-1);
    }
    getPlaneMatrix(firstLine.cartesianForm.firstPlane, tempRow);
    insertMatrixIntoMatrix(3, 4, completeMatrix, 0, 0, 1, 4, tempRow);
    getPlaneMatrix(firstLine.cartesianForm.secondPlane, tempRow);
    insertMatrixIntoMatrix(3, 4, completeMatrix, 1, 0, 1, 4, tempRow);
    getPlaneMatrix(secondLine.cartesianForm.firstPlane, tempRow);
    insertMatrixIntoMatrix(3, 4, completeMatrix, 2, 0, 1, 4, tempRow);
    gaussJordanElimination(3, 4, completeMatrix, completeMatrix);
    intersectionPoint.x = invertFractionSign(completeMatrix[0][3]);
    intersectionPoint.y = invertFractionSign(completeMatrix[1][3]);
    intersectionPoint.z = invertFractionSign(completeMatrix[2][3]);

    return intersectionPoint;
}

/* calculates a shared plane between two given lines */
plane_t getLinesSharedPlane(line_t firstLine, line_t secondLine){
    int result;
    line_t tempLine;
    result = getLinesReciprocalPosition(firstLine, secondLine);
    if(result != 2 && result != 1){
        fprintf(stderr, "error: the two given lines do not share any");
    }
    if(result == 1){
        tempLine.parametricForm.directionVector[0][0] = subtractFractions(firstLine.parametricForm.applicationPoint.x, secondLine.parametricForm.applicationPoint.x);
        tempLine.parametricForm.directionVector[1][0] = subtractFractions(firstLine.parametricForm.applicationPoint.y, secondLine.parametricForm.applicationPoint.y);
        tempLine.parametricForm.directionVector[2][0] = subtractFractions(firstLine.parametricForm.applicationPoint.z, secondLine.parametricForm.applicationPoint.z);
        tempLine.cartesianForm = lineParametricToCartesianForm(tempLine.parametricForm);
    } else {
        tempLine = secondLine;
    }

    return getPlaneGivenTwoDirectionVectors(firstLine.parametricForm.directionVector, tempLine.parametricForm.directionVector, firstLine.parametricForm.applicationPoint);
}

/* prints the reciprocal position of two lines */
void printLinesReciprocalPosition(line_t firstLine, line_t secondLine){
    int result;
    point_t intersectionPoint;
    plane_t sharedPlane;
    result = getLinesReciprocalPosition(firstLine, secondLine);
    switch(result){
        default:
        case 3:
            printf("The two lines do not intersect and are not parallel.\n");

            break;
        case 2:
            intersectionPoint = getLinesIntersectionPoint(firstLine, secondLine);
            printf("The two lines intersect.\n");
            printf("Intersection point: ");
            printPoint(intersectionPoint);
            printf("\n");
            printf("Shared plane: ");
            printPlane(getLinesSharedPlane(firstLine, secondLine));
            printf("\n");

            break;
        case 1:
            printf("The two lines are parallel.\n");
            printf("Shared plane: ");
            printPlane(getLinesSharedPlane(firstLine, secondLine));
            printf("\n");

            break;
        case 0:
            printf("The two lines are identical.\n");

            break;
    }
}

/* calculates the equation of a plane, given two direction vectors and an application point */
plane_t getPlaneGivenTwoDirectionVectors(fraction_t v[3][1], fraction_t w[3][1], point_t point){
    plane_t plane;
    fraction_t completeMatrix[3][6], identityMatrix[3][3], tempColumn[3][1], tempResultMatrix[2][5], resultMatrix[1][4], tempVector[1][3], tempVectors[2][3];
    transposeMatrix(3, 1, v, tempVector);
    insertMatrixIntoMatrix(2, 3, tempVectors, 0, 0, 1, 3, tempVector);
    transposeMatrix(3, 1, w, tempVector);
    insertMatrixIntoMatrix(2, 3, tempVectors, 1, 0, 1, 3, tempVector);
    if(getMatrixRank(2, 3, tempVectors) != 2){
        fprintf(stderr, "\nerror: the two given direction vectors are not linearly independent.\n");

        exit(-1);
    }
    getIdentityMatrix(3, identityMatrix);
    insertMatrixIntoMatrix(3, 6, completeMatrix, 0, 0, 3, 1, v);
    insertMatrixIntoMatrix(3, 6, completeMatrix, 0, 1, 3, 1, w);
    insertMatrixIntoMatrix(3, 6, completeMatrix, 0, 2, 3, 3, identityMatrix);
    getPointMatrix(point, tempColumn);
    insertMatrixIntoMatrix(3, 6, completeMatrix, 0, 5, 3, 1, tempColumn);
    gaussJordanElimination(3, 6, completeMatrix, completeMatrix);
    if(getPivotColumn(3, 6, completeMatrix, 0) < getPivotColumn(3, 6, completeMatrix, 1)){
        swapRows(3, 6, completeMatrix, 0, 1);
    }
    if(getPivotColumn(3, 6, completeMatrix, 0) < getPivotColumn(3, 6, completeMatrix, 2)){
        swapRows(3, 6, completeMatrix, 0, 2);
    }
    getSubmatrix(3, 6, completeMatrix, 2, 0, tempResultMatrix);
    getSubmatrix(2, 5, tempResultMatrix, 1, 0, resultMatrix);

    return getPlaneFromMatrix(resultMatrix);
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
