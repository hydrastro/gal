/*
 * compile command: gcc -o main.exe lib/matrix.c lib/fraction_t.c
 * example imputs: ./main.exe < input1
 */

#include <stdio.h>
#include "gal.h"

int main(void){
    setbuf(stdout, NULL);
    // declarations
    unsigned int rows, columns;
    int completeMatrixRank, reducedMatrixRank;
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
    completeMatrixRank = getMatrixRank(rows, columns, matrix);
    reducedMatrixRank = getMatrixRank(rows, columns, upperTriangularMatrix);
    printf("\nComplete matrix rank: %d\nReduced matrix rank: %d\n", completeMatrixRank, reducedMatrixRank);

    // performing and displaying the reduced row echelon form
    gaussJordanElimination(rows, columns, upperTriangularMatrix);
    printf("\nReduced row echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    // getting the matrix determinant
    determinant = getDeterminant(rows, columns, matrix);
    printf("\nMatrix determinant:");
    printFraction(determinant);

    return(0);
}
