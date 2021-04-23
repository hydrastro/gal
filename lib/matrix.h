#ifndef GAL_MATRIX_H
#define GAL_MATRIX_H
#include <stdbool.h>
#include "fraction.h"

void readMatrix(int rows, int columns, fraction_t matrix[rows][columns]);
void printMatrix(int rows, int columns, fraction_t matrix[rows][columns]);
void copyMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t copyMatrix[rows][columns]);
int gaussElimination(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns]);
void swapRows(int rows, int columns, fraction_t matrix[rows][columns], int row1, int row2);
int getMatrixRank(int rows, int columns, fraction_t matrix[rows][columns]);
bool isMatrixReduced(int rows, int columns, fraction_t matrix[rows][columns], bool reducedRowEchelonForm);
int getPivotColumn(int rows, int columns, fraction_t matrix[rows][columns], int row);
int gaussJordanElimination(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns]);
fraction_t getMatrixDeterminant(int rows, fraction_t matrix[rows][rows]);
void getMatrixKernelBasis(int rows, int columns, int rank, fraction_t matrix[rows][columns], fraction_t bases[columns - rank][columns]);
void getMatrixImageBasis(int rows, int columns, int rank, fraction_t matrix[rows][columns], fraction_t basis[rank][rows]);
void transposeMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[columns][rows]);
void sumMatrix(int rows, int columns, fraction_t matrix1[rows][columns], fraction_t matrix2[rows][columns], fraction_t resultMatrix[rows][columns]);
void subtractMatrix(int rows, int columns, fraction_t matrix1[rows][columns], fraction_t matrix2[rows][columns], fraction_t resultMatrix[rows][columns]);
void multiplyMatrix(int rows, int columns, int resultColumns, fraction_t matrix1[rows][columns], fraction_t matrix2[columns][resultColumns], fraction_t resultMatrix[rows][resultColumns]);
void multiplyMatrixByScalar(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns], fraction_t scalar);
void divideMatrixByScalar(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns], fraction_t scalar);
bool isRowEmpty(int rows, int columns, fraction_t matrix[rows][columns], int row);
void invertMatrix(int rows, fraction_t matrix[rows][rows], fraction_t resultMatrix[rows][rows]);
fraction_t getMatrixMinor(int rows, fraction_t matrix[rows][rows], int row, int column);
void getSubmatrix(int rows, int columns, fraction_t matrix[rows][columns], int row, int column, fraction_t resultMatrix[rows - 1][columns - 1]);
fraction_t getMatrixTrace(int rows, fraction_t matrix[rows][rows]);
void getMatrixPower(int rows, fraction_t matrix[rows][rows], int power, fraction_t resultMatrix[rows][rows]);
void getIdentityMatrix(int rows, fraction_t resultMatrix[rows][rows]);
void addMatrixRow(int rows, int columns, fraction_t matrix[rows][columns], fraction_t row[1][columns], fraction_t resultMatrix[rows + 1][columns]);
void addMatrixColumn(int rows, int columns, fraction_t matrix[rows][columns], fraction_t column[rows][1], fraction_t resultMatrix[rows][columns + 1]);
fraction_t vectorScalarProduct(int rows, fraction_t vector1[rows][1], fraction_t vector2[rows][1]);
void projectVector(int rows, fraction_t vector1[rows][1], fraction_t vector2[rows][1], fraction_t resultVector[rows][1]);
fraction_t getVectorNorm(int rows, fraction_t vector[rows][1]);
void grahmSchmidtOrthogonalization(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns]);
void moorePenrosePseudoinverse(int rows, fraction_t matrix[rows][rows], fraction_t resultMatrix[rows][rows]);
void orthonormalizeMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[rows][columns]);
void findEigenvalues(int rows, fraction_t matrix[rows][rows], fraction_t eigenvalues[rows][1]);
bool matrixEquals(int rows, int columns, fraction_t matrix1[rows][columns], fraction_t matrix2[rows][columns]);
bool matrixApproximatelyEquals(int rows, int columns, fraction_t matrix1[rows][columns], fraction_t matrix2[rows][columns], int precision);
bool isMatrixSymmetric(int rows, int columns, fraction_t matrix[rows][rows]);
void composeMatrices(int rows, int firstMatrixColumns, int secondMatrixColumns, fraction_t firstMatrix[rows][firstMatrixColumns], fraction_t secondMatrix[rows][secondMatrixColumns], fraction_t resultMatrix[rows][firstMatrixColumns + secondMatrixColumns]);
void composeMatricesVertically(int firstMatrixRows, int secondMatrixRows, int columns, fraction_t firstMatrix[firstMatrixRows][columns], fraction_t secondMatrix[secondMatrixRows][columns], fraction_t resultMatrix[firstMatrixRows + secondMatrixRows][columns]);

#endif /* GAL_MATRIX_H */
