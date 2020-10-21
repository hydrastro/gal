#ifndef MATRIX_H
#define MATRIX_H
#include <stdbool.h>
#include "fraction_t.h"

void readMatrix(int rows, int columns, fraction_t matrix[rows][columns]);
void printMatrix(int rows, int columns, fraction_t matrix[rows][columns]);
void copyMatrix(int rows, int columns, fraction_t matrix[rows][columns], fraction_t copyMatrix[rows][columns]);
void gaussElimination(int rows, int columns, fraction_t matrix[rows][columns]);
void swapRows(int rows, int columns, fraction_t matrix[rows][columns], int row1, int row2);
int getMatrixRank(int rows, int columns, fraction_t matrix[rows][columns]);
bool isMatrixReduced(int rows, int columns, fraction_t matrix[rows][columns]);
int getPivotColumn(int rows, int columns, fraction_t matrix[rows][columns], int row);
void gaussJordanElimination(int rows, int columns, fraction_t matrix[rows][columns]);
fraction_t getDeterminant(int rows, int columns, fraction_t matrix[rows][columns]);

void getInverseMatrix(int rows, int columns, fraction_t matrix[rows][columns]);

#endif //MATRIX_H
