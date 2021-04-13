#include <stdio.h>
#include "gal.h"

int algebraFunctions(){
    unsigned int rows, columns;
    /* getting the matrix size */
    printf("Matrix rows: ");
    scanf("%u", &rows);
    printf("Matrix columns: ");
    scanf("%u", &columns);

    /* dynamic matrix declaration */
    fraction_t matrix[rows][columns];

    /* getting  the matrix values */
    readMatrix(rows, columns, matrix);

    /* displaying the input matrix */
    printf("\nStarting matrix:\n");
    printMatrix(rows, columns, matrix);

    /* performing and displaying the row echelon form */
    fraction_t upperTriangularMatrix[rows][columns];
    copyMatrix(rows, columns, matrix, upperTriangularMatrix);
    gaussElimination(rows, columns, matrix, upperTriangularMatrix);
    printf("\nRow echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    /* getting and displaying the matrix rank */
    int matrixRank;
    matrixRank = getMatrixRank(rows, columns, matrix);
    printf("\nMatrix rank: %d\n", matrixRank);

    /* performing and displaying the reduced row echelon form */
    gaussJordanElimination(rows, columns, matrix, upperTriangularMatrix);
    printf("\nReduced row echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    /* getting the marix kernel basis */
    fraction_t kernelBasis[columns - matrixRank][columns];
    getMatrixKernelBasis(rows, columns, matrixRank, matrix, kernelBasis);
    printf("\nMatrix kernel basis (by row, transposed):\n");
    printMatrix(columns - matrixRank, columns, kernelBasis);
    printf("\n");

    /* getting the matrix image basis */
    fraction_t imageBasis[matrixRank][rows];
    getMatrixImageBasis(rows, columns, matrixRank, matrix, imageBasis);
    printf("\nMatrix image basis (by row, transposed):\n");
    printMatrix(matrixRank, rows, imageBasis);
    printf("\n");

    if(rows != columns){

        return 0;
    }

    /* getting the matrix determinant */
    fraction_t determinant;
    determinant = getMatrixDeterminant(rows, matrix);
    printf("\nMatrix determinant: ");
    printFraction(determinant);
    printf("\n");

    /* calculates the inverse */
    if(determinant.numerator != 0){
        fraction_t inverse[rows][columns];
        invertMatrix(rows, matrix, inverse);
        printf("\nInverse matrix:\n");
        printMatrix(rows, columns, inverse);
        printf("\n");
    }

    /* calculates the orthogonal matrix */
    fraction_t orthogonalMatrix[rows][columns];
    printf("\nGrahm-Schmidt orthogonal matrix:\n");
    grahmSchmidtOrthogonalization(rows, columns, matrix, orthogonalMatrix);
    printMatrix(rows, columns, orthogonalMatrix);

    /* orthonormalizes the orthogonal matrix */
    fraction_t orthonormalizedMatrix[rows][columns];
    printf("\nGrahm-Schmidt orthonormalized matrix (Q):\n");
    orthonormalizeMatrix(rows, columns, orthogonalMatrix, orthonormalizedMatrix);
    printMatrix(rows, columns, orthonormalizedMatrix);

    /* calculates the upper triangular matrix of the QR decomposition */
    fraction_t RMatrix[rows][columns];
    printf("\nGrahm-Schmidt upper-triangular matrix(R):\n");
    transposeMatrix(rows, columns, orthonormalizedMatrix, RMatrix);
    multiplyMatrix(rows, rows, rows, RMatrix, matrix, RMatrix);
    printMatrix(rows, columns, RMatrix);

    /* calculates the eigenvalues of the matrix */
    fraction_t eigenvalues[rows][1];
    printf("\nMatrix eigenvalues:\n");
    findEigenvalues(rows, matrix, eigenvalues);
    printMatrix(rows, 1, eigenvalues);

    /* calculates the Moore-Penorse pseudoinverse */
    fraction_t pseudoinverse[rows][columns];
    printf("\nMoore-Penorse pseudoinverse matrix:\n");
    moorePenrosePseudoinverse(rows, matrix, pseudoinverse);
    printMatrix(rows, columns, pseudoinverse);
    printf("\n");

    return 0;
}

int invariantsAndClassificationFunctions(){
    unsigned int rows, columns;
    /* getting the matrix size */
    printf("Matrix rows: ");
    scanf("%u", &rows);
    printf("Matrix columns: ");
    scanf("%u", &columns);

    /* dynamic matrix declaration */
    fraction_t matrix[rows][columns];

    /* getting  the matrix values */
    readMatrix(rows, columns, matrix);

    /* displaying the input matrix */
    printf("\nStarting matrix:\n");
    printMatrix(rows, columns, matrix);

    /* checking if the matrix is symmetric */
    if(!isMatrixSymmetric(rows, rows, matrix)){
        fprintf(stderr, "\nerror: the entered matrix is not symmetric.\n");

        return -1;
    }

    /* calculating the invariants of the coninc/quadric */
    fraction_t linearInvariant, quadraticInvariant, cubicInvariant, quarticInvariant;
    if(rows == 4){
        printf("\nQuartic invariant:\t");
        quarticInvariant = getQuarticInvariant(rows, matrix);
        printFraction(quarticInvariant);
    }
    printf("\nCubic invariant:\t");
    cubicInvariant = getCubicInvariant(rows, matrix);
    printFraction(cubicInvariant);
    printf("\nQuadratic invariant:\t");
    quadraticInvariant = getQuadraticInvariant(rows, matrix);
    printFraction(quadraticInvariant);
    printf("\nLinear invariant:\t");
    linearInvariant = getLinearInvariant(rows, matrix);
    printFraction(linearInvariant);
    printf("\n");

    /* classifying its type if it's a conic or a quadric */
    if(rows == 4){
        printQuadricType(matrix);
    } else {
        printConicType(matrix);
    }

    return 0;
}

int main(void){
    setbuf(stdout, NULL);
    unsigned int action;
    char readChar;

    /* program header */
    printf("GAL - Linear Algebra and Geometry\n");

    /* option menu */
    printf("\nAlgebra\n");
    printf("0. Compute everything.\n");
    printf("\nGeometry\n");
    printf("1. Calculate the parametric form of a cartesian line.\n");
    printf("2. Calculate the cartesian form of a parametric line.\n");
    printf("3. Calculate the intersectoin of a line and a plane.\n");
    printf("4. Calculate the intersection of two lines.\n");
    printf("5. Calculate the equation of a plane given three points.\n");
    printf("6. Calculate the invariants of a conic and classify it.\n");
    printf("7. Calculate the invariants of a quadric and classify it.\n");

    /* scanning and checking wheter the input is valid */
    action = 0;
    printf("\nSelect an option (default = 0): ");
    readChar = fgetc(stdin);
    if(readChar != '\n'){
        action = readChar - '0';
    }
    printf("\n");
    if(action > 7){
        fprintf(stderr, "error: invalid option entered.\n");
    }

    switch(action){
        default:
        case 0:
            algebraFunctions();

            break;
        case 6:
        case 7:
            invariantsAndClassificationFunctions();

            break;
   }

    return 0;
}
