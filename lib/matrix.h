#ifndef MATRIX_H
#define MATRIX_H
#include <stdbool.h>
#include "fraction.h"

void readMatrix(int rows, int columns, fraction_t matrix[rows][columns]);
void printMatrix(int rows, int columns, fraction_t matrix[rows][columns]);
void copyMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t copyMatrix[rows][columns]);
void gaussElimination(int rows, int columns, fraction_t matrix[rows][columns], int rowSwappingTimes);
void swapRows(int rows, int columns, fraction_t matrix[rows][columns], int row1, int row2);
int getMatrixRank(int rows, int columns, fraction_t matrix[rows][columns]);
bool isMatrixReduced(int rows, int columns, fraction_t matrix[rows][columns], bool reducedRowEchelonForm);
int getPivotColumn(int rows, int columns, fraction_t matrix[rows][columns], int row);
void gaussJordanElimination(int rows, int columns, fraction_t matrix[rows][columns]);
fraction_t getDeterminant(int rows, int columns, fraction_t matrix[rows][columns]);
void getMatrixBases(int rows, int columns, int rank, fraction_t matrix[rows][columns], fraction_t bases[columns - 1 - rank][columns - 1]);
void trasposeMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[columns][rows]);
void sumMatrix(int rows, int columns, fraction_t matrix1[rows][columns], fraction_t matrix2[rows][columns], fraction_t resultMatrix[rows][columns]);
void muliplyMatrix(int rows, int columns, int resultColumns, fraction_t matrix1[rows][columns], fraction_t matrix2[columns][resultColumns], fraction_t resultMatrix[rows][resultColumns]);
void multiplyMatrixByScalar(int rows, int columns, fraction_t matrix[rows][columns], fraction_t resultMatrix[columns][rows], fraction_t scalar);
bool isRowEmpty(int rows, int columns, fraction_t matrix[rows][columns], int row);

void getInverseMatrix(int rows, int columns, fraction_t matrix[rows][columns]);

#endif //MATRIX_H
