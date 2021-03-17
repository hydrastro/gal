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

    // TODO: put all of this code outside of the main method
    // displaying the input matrix
    printf("\nStarting matrix:\n");
    printMatrix(rows, columns, matrix);

    // performing and displaying the row echelon form
    gaussElimination(rows, columns, matrix, upperTriangularMatrix);
    printf("\nRow echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    // getting and displaying the matrix rank
    matrixRank = getMatrixRank(rows, columns, matrix);
    printf("\nMatrix rank: %d\n", matrixRank);

    // performing and displaying the reduced row echelon form
    gaussJordanElimination(rows, columns, matrix, upperTriangularMatrix);
    printf("\nReduced row echelon form of the matrix:\n");
    printMatrix(rows, columns, upperTriangularMatrix);

    // getting the marix kernel basis
    fraction_t kernelBasis[columns - matrixRank][columns];
    getMatrixKernelBasis(rows, columns, matrixRank, matrix, kernelBasis);
    printf("\nMatrix kernel basis (by row, transposed):\n");
    printMatrix(columns - matrixRank, columns, kernelBasis);
    printf("\n");

    // getting the matrix image basis
    fraction_t imageBasis[matrixRank][rows];
    getMatrixImageBasis(rows, columns, matrixRank, matrix, imageBasis);
    printf("\nMatrix image basis (by row, transposed):\n");
    printMatrix(matrixRank, rows, imageBasis);
    printf("\n");

    if(rows != columns){

        return(0);
    }

    // getting the matrix determinant
    determinant = getMatrixDeterminant(rows, matrix);
    printf("\nMatrix determinant: ");
    printFraction(determinant);
    printf("\n");

    // calculates the inverse
    // TODO: check that the determinant is not zero
    fraction_t inverse[rows][columns];
    getInverseMatrix(rows, matrix, inverse);
    printf("\nInverse matrix:\n");
    printMatrix(rows, columns, inverse);
    printf("\n");

    // classifying its type if it's a conic or a quadric
    switch(rows){
        case 4:
           // printQuadricType(matrix);
           break;
        case 3:
           printConicType(matrix);
           break;
    }

    return(0);
}
