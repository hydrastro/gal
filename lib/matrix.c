#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"


// given the number of rows and columns, it reads a matrix, element by element as a fraction type
void readMatrix(int rows, int columns, fraction_t matrix[rows][columns]){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            printf("Matrix(%d,%d): ", i + 1, j + 1);
            matrix[i][j] = readFraction();
        }
    }
}

// prints a matrix
void printMatrix(int rows, int columns, fraction_t matrix[rows][columns]){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            printFraction(matrix[i][j]);
            printf("\t");
        }
        printf("\n");
    }
}

// copies a bi-dimensional array into another variable
void copyMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t copyMatrix[rows][columns]){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            copyMatrix[i][j] = matrix[i][j];
        }
    }
}

// performs the gaussian elimination algorithm on a given matrix
void gaussElimination(int rows, int columns, fraction_t matrix[rows][columns]){
    int currentRow, currentColumn, otherRow;
    fraction_t subtraction, factor;
    // starts loop for each matrix's row
    for(currentRow = 0; currentRow < rows - 1; currentRow++){
        // starts a loop to compare the current row to the next ones, this first loop just orders the rows of the matrix
        for(otherRow = currentRow + 1; otherRow < rows; otherRow++){
            // calculates the difference between the the pivot of the current rows and the elements below the pivot
            subtraction = subtractFractions(fractionAbsoluteValue(matrix[otherRow][currentRow]), fractionAbsoluteValue(matrix[currentRow][currentRow]));
            // rows are swapped and zero(s) are placed down the pivot
            if(subtraction.numerator > 0 && subtraction.denominator > 0){
                swapRows(rows, columns, matrix, currentRow, otherRow);
            }
        }
        // starts a loop to perform the elimination
        for(otherRow = currentRow + 1; otherRow < rows; otherRow++){
            factor = divideFractions(matrix[otherRow][currentRow], matrix[currentRow][currentRow]);
            for(currentColumn = 0; currentColumn < columns; currentColumn++){
                // each element of each row below the pivot is replaced
                matrix[otherRow][currentColumn] = subtractFractions(matrix[otherRow][currentColumn], multiplyFractions(factor, matrix[currentRow][currentColumn]));
            }
        }
    }
}

// swap to rows of bi-dimensional array
void swapRows(int rows, int columns, fraction_t matrix[rows][columns], int row1, int row2){
    int j;
    fraction_t temp;
    for(j = 0; j < columns; j++){
        temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}

// calculates the rank of a matrix
int getMatrixRank(int rows, int columns, fraction_t matrix[rows][columns]){
    int rank, i, j;
    bool emptyRow;
    rank = 0;
    if(!isMatrixReduced(rows, columns, matrix)){
        gaussElimination(rows, columns, matrix);
    }
    for(i = 0; i < rows; i++){
        emptyRow = true;
        for(j = 0; j < columns; j++){
            if(matrix[i][j].numerator != 0){
                emptyRow = false;
            }
        }
        if(!emptyRow){
            rank++;
        }
    }

    return rank;
}

// checks if the matrix is upper triangular
bool isMatrixReduced(int rows, int columns, fraction_t matrix[rows][columns]){
    int i, j;
    for(i = 0; i < columns; i++){
        for(j = i + 1; j < rows; j++){
            if(matrix[j][i].numerator != 0){

                return false;
            }
        }
    }

    return true;
}

// given a row, returns the pivot column
int getPivotColumn(int rows, int columns, fraction_t matrix[rows][columns], int row){
    int column;
    if(row == rows){

        return columns;
    }
    for(column = 0; column < columns; column++){
        if(matrix[row][column].numerator != 0) {

            return column;
        }
    }

    return 0;
}

void gaussJordanElimination(int rows, int columns, fraction_t matrix[rows][columns]){
    int i, j, k, pivotColumn;
    fraction_t factor, pivotValue;
    if(!isMatrixReduced(rows, columns, matrix)){
        gaussElimination(rows, columns, matrix);
    }
    // looping every row from the bottom
    for(i = rows - 1; i >= 0; i--) {
        pivotColumn = getPivotColumn(rows, columns, matrix, i);
        pivotValue = matrix[i][pivotColumn];
        // looping for every other value in the row
        for (j = pivotColumn; j < columns ; j++) {
            // dividing each row by their pivot
            matrix[i][j] = divideFractions(matrix[i][j], pivotValue);
        }
        // the first column doesn't need to go in the substitution loop
        if(i != 0){
            // looping every other remaining row
            for(j = i - 1; j >= 0; j--){
                // it would have also been divided by matrix[i][pivotColumn] but it's 1
                factor = matrix[j][pivotColumn];
                // looping every row term after the pivot
                for(k = pivotColumn; k < columns; k++){
                    // subtracting
                    matrix[j][k] = subtractFractions(matrix[j][k], multiplyFractions(matrix[i][k], factor));
                }
            }
        }
    }
}

// calculates the determinant of a matrix
fraction_t getDeterminant(int rows, int columns, fraction_t matrix[rows][columns]){
    int i, determinant;
    if(rows != columns){

        return 0;
    }
    if(!isMatrixReduced(rows, columns, matrix)){
        gaussElimination(rows, columns, matrix);
    }
    determinant = getFraction(1, 1);
    for(i = 0; i < columns; i++){
        determinant = multiplyFractions(determinant, matrix[i][i]);
    }

    return determinant;
}

void getInverseMatrix(int rows, int columns, fraction_t matrix[rows][columns]){}
