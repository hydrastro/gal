#ifndef MATRIX_H
#define MATRIX_H
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
void getMatrixBases(int rows, int columns, int rank, fraction_t matrix[rows][columns], fraction_t bases[columns - 1 - rank][columns - 1]);
void trasposeMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[columns][rows]);
void sumMatrix(int rows, int columns, fraction_t matrix1[rows][columns], fraction_t matrix2[rows][columns], fraction_t resultMatrix[rows][columns]);
void multiplyMatrix(int rows, int columns, int resultColumns, fraction_t matrix1[rows][columns], fraction_t matrix2[columns][resultColumns], fraction_t resultMatrix[rows][resultColumns]);
void multiplyMatrixByScalar(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[columns][rows], fraction_t scalar);
bool isRowEmpty(int rows, int columns, fraction_t matrix[rows][columns], int row);

void getInverseMatrix(int rows, fraction_t matrix[rows][rows], fraction_t resultMatrix[rows][rows]);
fraction_t getMatrixMinor(int rows, fraction_t matrix[rows][rows], int row, int column);
void getSubmatrix(int rows, int columns, fraction_t matrix[rows][columns], int row, int column, fraction_t resultMatrix[rows - 1][columns - 1]);

fraction_t getMatrixTrace(int rows, fraction_t matrix[rows][rows]);
void getMatrixPower(int rows, fraction_t matrix[rows][rows], int power, fraction_t resultMatrix[rows][rows]);
void getIdentityMatrix(int rows, fraction_t resultMatrix[rows][rows]);
#endif //MATRIX_H
