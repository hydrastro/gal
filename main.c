#include <stdio.h>
#include "gal.h"

int main(void){
    setbuf(stdout, NULL);
    unsigned int rows, columns;
    int completeMatrixRank, reducedMatrixRank;
    fraction_t determinant;

    printf("Matrix rows: ");
    scanf("%u", &rows);
    printf("Matrix columns: ");
    scanf("%u", &columns);
    fraction_t matrix[rows][columns];
    fraction_t upperTriangularMatrix[rows][columns];

    readMatrix(rows, columns, matrix);
    copyMatrix(rows, columns, matrix, upperTriangularMatrix);

    printf("\nStarting matrix:\n");
    printMatrix(rows, columns, matrix);

    gaussElimination(rows, columns, upperTriangularMatrix);
    printf("\nRow echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    completeMatrixRank = getMatrixRank(rows, columns, matrix);
    reducedMatrixRank = getMatrixRank(rows, columns, upperTriangularMatrix);
    printf("\nComplete matrix rank: %d\nReduced matrix rank: %d\n", completeMatrixRank, reducedMatrixRank);

    gaussJordanElimination(rows, columns, upperTriangularMatrix);
    printf("\nReduced row echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    determinant = getDeterminant(rows, columns, matrix);
    printf("\nMatrix determinant:");
    printFraction(determinant);

    return(0);
}
