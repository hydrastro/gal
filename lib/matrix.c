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
    }printf("\n\n");
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

// performs the gaussian elimination algorithm on a given matrix and returns the times the rows were swapped
int gaussElimination(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns]){
    int currentRow, currentColumn, otherRow, rowSwappingTimes;
    fraction_t subtraction, factor;
    rowSwappingTimes = 0;
    copyMatrix(rows, columns, matrix, resultMatrix);
    // starts loop for each matrix's row
    for(currentRow = 0; currentRow < rows - 1; currentRow++){
        // starts a loop to compare the current row to the next ones, this first loop just orders the rows of the matrix
        for(otherRow = currentRow + 1; otherRow < rows; otherRow++){
            // calculates the difference between the the pivot of the current rows and the elements below the pivot
            subtraction = subtractFractions(fractionAbsoluteValue(resultMatrix[otherRow][currentRow]), fractionAbsoluteValue(resultMatrix[currentRow][currentRow]));
            // rows are swapped and zero(s) are placed down the pivot
            if(subtraction.numerator > 0 && subtraction.denominator > 0){
                swapRows(rows, columns, resultMatrix, currentRow, otherRow);
                rowSwappingTimes++;
            }
        }
        // starts a loop to perform the elimination
        for(otherRow = currentRow + 1; otherRow < rows; otherRow++){
            factor = divideFractions(resultMatrix[otherRow][currentRow], resultMatrix[currentRow][currentRow]);
            for(currentColumn = 0; currentColumn < columns; currentColumn++){
                // each element of each row below the pivot is replaced
                resultMatrix[otherRow][currentColumn] = subtractFractions(resultMatrix[otherRow][currentColumn], multiplyFractions(factor, resultMatrix[currentRow][currentColumn]));
            }
        }
    }

    return rowSwappingTimes;
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
    fraction_t tempMatrix[rows][columns];
    copyMatrix(rows, columns, matrix, tempMatrix);
    rank = 0;
    // check if matrix is in row echelon form, otherwise performs the gaussian elimination
    if(!isMatrixReduced(rows, columns, tempMatrix, false)){
        gaussElimination(rows, columns, matrix, tempMatrix);
    }
    // counting the pivots
    for(i = 0; i < rows; i++){
        emptyRow = true;
        for(j = 0; j < columns; j++){
            if(tempMatrix[i][j].numerator != 0){
                emptyRow = false;
            }
        }
        if(!emptyRow){
            rank++;
        }
    }

    return rank;
}

// checks if a given matrix is in row echelon form (reducedFrom is false), or in reduced row echelon form (reducedForm is true)
bool isMatrixReduced(int rows, int columns, fraction_t matrix[rows][columns], bool reducedRowEchelonForm){
    int i, j, previousPivotColumn, currentPivotColumn, difference;
    // looping every matrix row
    for(i = 1; i < rows; i++){
        previousPivotColumn = getPivotColumn(rows, columns, matrix, i - 1);
        currentPivotColumn = getPivotColumn(rows, columns, matrix, i);
        difference = currentPivotColumn - previousPivotColumn;
        // checking if the current pivot is placed below or before the previous one
        if(difference <= 0){

            return false;
        }
        // checking all the values below the pivot
        for(j = i + 1; i < rows; i++){
            if(matrix[i][j].numerator != 0){

                return false;
            }
        }
        if(reducedRowEchelonForm){
            // checking all the values upward the pivot	
            for(j = i -1; j >= 0; j--){
                if(matrix[j][i].numerator != 0){

                    return false;
                }
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
        if(matrix[row][column].numerator != 0){

            return column;
        }
    }

    return columns;
}

// performs the Gauss-Jordan elimination on a given matrix
int gaussJordanElimination(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns]){
    int i, j, k, pivotColumn, rowSwappingTimes;
    fraction_t factor, pivotValue, product;\
    rowSwappingTimes = 0;
    // check if matrix is in row echelon form, otherwise performs the gaussian elimination
    if(!isMatrixReduced(rows, columns, matrix, false)){
        rowSwappingTimes = gaussElimination(rows, columns, matrix, resultMatrix);
    }
    // looping every row from the bottom
    for(i = rows - 1; i >= 0; i--){
        pivotColumn = getPivotColumn(rows, columns, resultMatrix, i);
        pivotValue = resultMatrix[i][pivotColumn];
        // looping for every other value in the row
        for (j = pivotColumn; j < columns ; j++){
            // dividing each row by their pivot
            resultMatrix[i][j] = divideFractions(resultMatrix[i][j], pivotValue);
        }
        // the first column doesn't need to go in the substitution loop
        if(i != 0){
            // looping every other remaining row
            for(j = i - 1; j >= 0; j--){
                // it would have also been divided by matrix[i][pivotColumn] but it's 1
                factor = resultMatrix[j][pivotColumn];
                // looping every row term after the pivot
                for(k = pivotColumn; k < columns; k++){
                    // multiplying
                    product = multiplyFractions(resultMatrix[i][k], factor);
                    // subtracting
                    resultMatrix[j][k] = subtractFractions(resultMatrix[j][k], product);
                }
            }
        }
    }

    return rowSwappingTimes;
}

// calculates the determinant of a matrix
fraction_t getMatrixDeterminant(int rows, fraction_t matrix[rows][rows]){
    int i, rowSwappingTimes;
    fraction_t determinant, tempMatrix[rows][rows];
    rowSwappingTimes = 0;
    copyMatrix(rows, rows, matrix, tempMatrix);
    // check if matrix is in row echelon form, otherwise performs the gaussian elimination
    if(!isMatrixReduced(rows, rows, matrix, false)){
        rowSwappingTimes = gaussElimination(rows, rows, matrix, tempMatrix);
    }
    determinant = getFraction(1, 1);
    // multiplying the pivots
    for(i = 0; i < rows; i++){
        determinant = multiplyFractions(determinant, tempMatrix[i][i]);
    }
    // changing the sign due the rows swapping occured during the gaussian elimination
    if(rowSwappingTimes % 2 != 0){
        determinant = invertFractionSign(determinant);
    }

    return determinant;
}

// calculates the basis of the kernel of a given matrix
void getMatrixKernelBasis(int rows, int columns, int rank, fraction_t matrix[rows][columns], fraction_t basis[columns - rank][columns]){
    int i, j, k, previousPivotColumn, currentPivotColumn, difference, basisNumber;
    fraction_t tempMatrix[rows][columns];
    // checking if the matrix is in reduced row echelon form
    if(!isMatrixReduced(rows, columns, matrix, true)){
        gaussJordanElimination(rows, columns, matrix, tempMatrix);
    }
    // emptying the basis array
    for(i = 0; i < columns - rank; i++){
        for(j = 0; j < columns; j++){
            basis[i][j] = getFraction(0, 1);
        }
    }
    basisNumber = 0;
    // looping every matrix row
    for(i = 1; i <= rows; i++){
        previousPivotColumn = getPivotColumn(rows, columns, tempMatrix, i - 1);
        // setting the current pivot column
        if(isRowEmpty(rows, columns, tempMatrix, i)){
            currentPivotColumn = columns;
        } else {
            currentPivotColumn = getPivotColumn(rows, columns, tempMatrix, i);
        }
        difference = currentPivotColumn - previousPivotColumn;
        // checking if there are free parameters
        if(difference > 1){
            // looping for all the free parameters found
            for(j = previousPivotColumn + 1; j < currentPivotColumn; j++){
                // getting all the values of the parameter in the previous rows
                for(k = 0; k < i; k++){
                     basis[basisNumber][k] = invertFractionSign(tempMatrix[k][j]);
                }
                // setting the actual parameter value to 1
                basis[basisNumber][j] = getFraction(1, 1);
                basisNumber++;
            }
        }
    }
}

void getMatrixImageBasis(int rows, int columns, int rank, fraction_t matrix[rows][columns], fraction_t basis[rank][rows]){
    int i, j, pivotColumn, basisNumber;
    fraction_t tempMatrix[rows][columns];
    // checking if the matrix is in reduced row echelon form
    if(!isMatrixReduced(rows, columns, matrix, true)){
        gaussJordanElimination(rows, columns, matrix, tempMatrix);
    }
    // emptying the basis array
    for(i = 0; i < rank; i++){
        for(j = 0; j < rows; j++){
            basis[i][j] = getFraction(0, 1);
        }
    }
    basisNumber = 0;
    // looping the reduced matrix rows
    for(i = 0; i < rows; i++){
        // getting the pivot column
        pivotColumn = getPivotColumn(rows, columns, tempMatrix, i);
        // copying the corresponding matrix column to the basis array
        for(j = 0; j < rows; j++){
            basis[basisNumber][j] = matrix[j][pivotColumn];
        }
        basisNumber++;
    }
}

// transposes a matrix
void trasposeMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[columns][rows]){
    int i, j;
    // emtpying the result matrix
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            resultMatrix[i][j] = getFraction(0, 1);
        }
    }
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            resultMatrix[i][j] = matrix[j][i];
        }
    }
}

// adds two matrix
void addMatrix(int rows, int columns, fraction_t matrix1[rows][columns], fraction_t matrix2[rows][columns], fraction_t resultMatrix[rows][columns]){
    int i, j;
    // emtpying the result matrix
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            resultMatrix[i][j] = getFraction(0, 1);
        }
    }
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            resultMatrix[i][j] = addFractions(matrix1[i][j], matrix2[i][j]);
        }
    }
}

// multiplies two matrix
void multiplyMatrix(int rows, int columns, int resultColumns, fraction_t matrix1[rows][columns], fraction_t matrix2[columns][resultColumns], fraction_t resultMatrix[rows][resultColumns]){
    int i, j, k;
    fraction_t product;
    // emtpying the result matrix
    for(i = 0; i < rows; i++){
        for(j = 0; j < resultColumns; j++){
            resultMatrix[i][j] = getFraction(0, 1);
        }
    }
    for(i = 0; i < rows; i++){
        for(j = 0; j < resultColumns; j++){
            for(k = 0; k < columns; k++){
                product = multiplyFractions(matrix1[i][k], matrix2[k][j]);
                resultMatrix[i][j] = addFractions(resultMatrix[i][j], product);
            }
        }
    }
}

// multiplies a matrix by a scalar
void multiplyMatrixByScalar(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[columns][rows], fraction_t scalar){
    int i, j;
    // emtpying the result matrix
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            resultMatrix[i][j] = getFraction(0, 1);
        }
    }
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            resultMatrix[i][j] = multiplyFractions(matrix[i][j], scalar);
        }
    }
}

// check if a matrix row is filled with zeroes
bool isRowEmpty(int rows, int columns, fraction_t matrix[rows][columns], int row){
    int i;
    for(i = 0; i < columns; i++){
        if(matrix[row][i].numerator != 0){

            return false;
        }
    }

    return true;
}

// computes the inverse of a matrix
void getInverseMatrix(int rows, fraction_t matrix[rows][rows], fraction_t resultMatrix[rows][rows]){
    int i, j;
    fraction_t determinantReciprocal;
    determinantReciprocal = invertFraction(getMatrixDeterminant(rows, matrix));
    for(i = 0; i < rows; i++){
        for(j = 0; j < rows; j++){
            resultMatrix[j][i] = getMatrixMinor(rows, matrix, i, j);
            if((i + j) % 2 == 1){
                resultMatrix[j][i] = invertFractionSign(resultMatrix[j][i]);
            }
            resultMatrix[j][i] = multiplyFractions(resultMatrix[j][i], determinantReciprocal);
        }
    }
}

// calculates the minor of a matrix element
fraction_t getMatrixMinor(int rows, fraction_t matrix[rows][rows], int row, int column){
    fraction_t submatrix[rows - 1][rows - 1];
    getSubmatrix(rows, rows, matrix, row, column, submatrix);

    return getMatrixDeterminant(rows - 1, submatrix);
}

// gets the submatrix by eliminating a row and a column of the given one
// NOTE: the row numbering starts from 0
void getSubmatrix(int rows, int columns, fraction_t matrix[rows][columns], int row, int column, fraction_t resultMatrix[rows - 1][columns - 1]){
    int i, j, k, l;
    for(i = 0, j = 0; i < rows; i++, j++){
        if(i == row){
            i++;
        }
        for(k = 0, l = 0; k < columns; k++, l++){
            if(k == column){
                k++;
            }
            resultMatrix[j][l] = matrix[i][k];
        }
    }
}

// calculates the matrix's trace
fraction_t getMatrixTrace(int rows, fraction_t matrix[rows][rows]){
    int i;
    fraction_t trace;
    trace = getFraction(0, 1);
    for(i = 0; i < rows; i++){
        trace = addFractions(trace, matrix[i][i]);
    }

    return trace;
}

// calculates the matrix's power
void getMatrixPower(int rows, fraction_t matrix[rows][rows], int power, fraction_t resultMatrix[rows][rows]){
    if(power == 0){
        getIdentityMatrix(rows, resultMatrix);

        return;
    }
    if(power > 0){
        copyMatrix(rows, rows, matrix, resultMatrix);
    } else {
        getInverseMatrix(rows, matrix, resultMatrix);
        power = -power;
    }
    while(power > 0){
        multiplyMatrix(rows, rows, rows, matrix, resultMatrix, resultMatrix);
        power--;
    }
}

// given a size, gets the identity matrix
void getIdentityMatrix(int rows, fraction_t resultMatrix[rows][rows]){
    int i, j;
    for(i = 0; i < rows; i++){
        for(i = 0; i < rows; i++){
            if(i == j){
                resultMatrix[i][j] = getFraction(1, 1);
            } else {
                resultMatrix[i][j] = getFraction(0, 1);
            }
        }
    }
}

// adds a row to a given matrix
void addMatrixRow(int rows, int columns, fraction_t matrix[rows][columns], fraction_t row[1][columns], fraction_t resultMatrix[rows + 1][columns]){
    int i;printMatrix(1,columns,row);
    copyMatrix(rows, columns, matrix, resultMatrix);
    for(i = 0; i < columns; i++){
        resultMatrix[rows][i] = row[0][i];
    }
}

// adds a column to a given matrix
void addMatrixColumn(int rows, int columns, fraction_t matrix[rows][columns], fraction_t column[rows][1], fraction_t resultMatrix[rows][columns + 1]){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j <= columns; j++){
            if(j == columns){
                resultMatrix[i][j] = column[i][0];
            } else {
                resultMatrix[i][j] = matrix[i][j];
            }
        }
    }
}

// calculates the scalar product of two vectors
fraction_t vectorScalarProduct(int rows, fraction_t vector1[rows][1], fraction_t vector2[rows][1]){
    int i, j;
    fraction_t result, product;
    result = getFraction(0, 1);
    for(i = 0; i < rows; i++){
        result = addFractions(result, multiplyFractions(vector1[i][1], vector2[i][1]));
    }

    return result;
}

// TODO: these functions
// calculates the orthogoal projection of vector1 on vector2
void projectVector(int rows, fraction_t vector[rows][1], fraction_t matrix2[rows][1]){
// ( v2( ( v1 * v2 ) / ( || v2 || ) ^ 2 ) )

    fraction_t temp;
}

void getVectorNorm(){
// || v ||
// *returns the n-root of the sum of the square of the n-elements of the vector (= d(O, P))*
}

void grahmSchmidtOrthogonalization(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns]){
// (v1 - projection(v1, v2)), etc ...
}

// TODO: n root
// TODO: put basis in an array of vectors ( + vector definition ? )
