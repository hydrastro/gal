#ifndef GAL_R3GEOMETRY_H
#define GAL_R3GEOMETRY_H
#include "fraction.h"

/* defining new types */
typedef struct Point_t{
    fraction_t x;
    fraction_t y;
    fraction_t z;
} Point_t;

typedef struct Vector_t{
    fraction_t x;
    fraction_t y;
    fraction_t z;
} Vector_t;

typedef struct Plane_t{
    fraction_t x;
    fraction_t y;
    fraction_t z;
    fraction_t d;
} Plane_t;

typedef struct lineParametricForm_t{
    Point_t applicationPoint;
    Vector_t directionVector;
} lineParametricForm_t;

typedef struct lineCartesianForm_t{
    Plane_t firstPlane;
    Plane_t secondPlane;
} lineCartesianForm_t;

Plane_t readPlane();
void printPlane(Plane_t plane);
lineParametricForm_t readLineParametricForm();
void printLineParametricForm(lineParametricForm_t line);
lineCartesianForm_t readLineCartesianForm();
void printLineCartesianForm(lineCartesianForm_t line);
Point_t readPoint();
void printPoint(Point_t point);
Vector_t readVector();
void printVector(Vector_t vector);
lineParametricForm_t lineCartesianToParametricForm(lineCartesianForm_t line);
lineCartesianForm_t lineParametricToCartesianForm(lineParametricForm_t line);
fraction_t getLinearInvariant(int rows, fraction_t matrix[rows][rows]);
fraction_t getQuadraticInvariant(int rows, fraction_t matrix[rows][rows]);
fraction_t getCubicInvariant(int rows, fraction_t matrix[rows][rows]);
fraction_t getQuarticInvariant(int rows, fraction_t matrix[rows][rows]);
void printConicType(fraction_t matrix[3][3]);
void printQuadricType(fraction_t matrix[4][4]);

#endif /* GAL_R3GEOMETRY_H */
