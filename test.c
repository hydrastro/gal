#include <stdio.h>
#include "gal.h"

int main(void){

    // gcc test.c -o test.exe lib/*.c -lm && ./test.exe < examples/input7

    setbuf(stdout, NULL);
    unsigned int rows, columns;
    int matrixRank;
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

    fraction_t RMatrix[rows][columns];
    fraction_t eigenvalues[rows];
    findEigenvalues(rows, matrix, eigenvalues);

    return(0);
}
