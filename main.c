/*
 * example imputs: ./main.exe < input
 */

#include <stdio.h>
#include "gal.h"

int main(void){
    setbuf(stdout, NULL);
    // declarations
    unsigned int rows, columns;
    int matrixRank;
    fraction_t determinant;

    // getting the matrix size
    printf("Matrix rows: ");
    scanf("%u", &rows);
    printf("Matrix columns: ");
    scanf("%u", &columns);

    // dynamic matrix declaration
    fraction_t matrix[rows][columns];
    fraction_t upperTriangularMatrix[rows][columns];

    // getting  the matrix values
    readMatrix(rows, columns, matrix);
    copyMatrix(rows, columns, matrix, upperTriangularMatrix);

    // displaying the input matrix
    printf("\nStarting matrix:\n");
    printMatrix(rows, columns, matrix);

    // performing and displaying the row echelon form
    gaussElimination(rows, columns, upperTriangularMatrix, 0);
    printf("\nRow echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    // getting and displaying the matrix rank
    matrixRank = getMatrixRank(rows, columns, matrix);
    printf("\nMatrix rank: %d\n", matrixRank);

    // performing and displaying the reduced row echelon form
    gaussJordanElimination(rows, columns, upperTriangularMatrix);
    printf("\nReduced row echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    // getting the matrix determinant
    determinant = getDeterminant(rows, columns, matrix);
    printf("\nMatrix determinant: ");
    printFraction(determinant);
    printf("\n");

    // getting the marix bases
    fraction_t bases[columns][columns];
    getMatrixBases(rows, columns, matrixRank, matrix, bases);
    printf("\nMatrix bases (by row):\n");
    printMatrix(columns - 1 - matrixRank, columns - 1, bases);
    printf("\n");

    return(0);
}
