#include <stdio.h>
#include "gal.h"

int main(void){
    setbuf(stdout, NULL);
    /* declarations */
    unsigned int rows, columns;
    int matrixRank;
    fraction_t determinant;

    /* getting the matrix size */
    printf("Matrix rows: ");
    scanf("%u", &rows);
    printf("Matrix columns: ");
    scanf("%u", &columns);

    /* dynamic matrix declaration */
    fraction_t matrix[rows][columns];
    fraction_t upperTriangularMatrix[rows][columns];

    /* getting  the matrix values */
    readMatrix(rows, columns, matrix);
    copyMatrix(rows, columns, matrix, upperTriangularMatrix);

    /* TODO: put all of this code outside of the main method */
    /* displaying the input matrix */
    printf("\nStarting matrix:\n");
    printMatrix(rows, columns, matrix);

    /* performing and displaying the row echelon form */
    gaussElimination(rows, columns, matrix, upperTriangularMatrix);
    printf("\nRow echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    /* getting and displaying the matrix rank */
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

        return(0);
    }

    /* getting the matrix determinant */
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

    return(0);
}
