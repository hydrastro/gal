#ifndef GAL_R3GEOMETRY_H
#define GAL_R3GEOMETRY_H
#include "fraction.h"

/* defining new types */
typedef struct point_t{
    fraction_t x;
    fraction_t y;
    fraction_t z;
} point_t;

typedef struct plane_t{
    fraction_t x;
    fraction_t y;
    fraction_t z;
    fraction_t d;
} plane_t;

typedef struct lineParametricForm_t{
    point_t applicationPoint;
    fraction_t directionVector[3][1];
} lineParametricForm_t;

typedef struct lineCartesianForm_t{
    plane_t firstPlane;
    plane_t secondPlane;
} lineCartesianForm_t;

typedef struct line_t{
    lineParametricForm_t parametricForm;
    lineCartesianForm_t cartesianForm;
} line_t;

plane_t readPlane();
void printPlane(plane_t plane);
lineParametricForm_t readLineParametricForm();
void printLineParametricForm(lineParametricForm_t line);
lineCartesianForm_t readLineCartesianForm();
void printLineCartesianForm(lineCartesianForm_t line);
line_t readLine();
void printLine(line_t line);
point_t readPoint();
void printPoint(point_t point);
void readVector(fraction_t vector[3][1]);
void printVector(fraction_t vector[3][1]);
lineParametricForm_t lineCartesianToParametricForm(lineCartesianForm_t line);
lineCartesianForm_t lineParametricToCartesianForm(lineParametricForm_t line);
void getPlaneMatrix(plane_t plane, fraction_t matrix[1][4]);
plane_t getPlaneFromMatrix(fraction_t matrix[1][4]);
void getPointMatrix(point_t point, fraction_t matrix[3][1]);
void getCartesianLineMatrix(lineCartesianForm_t line, fraction_t matrix[2][4]);
int getLinesReciprocalPosition(line_t firstLine, line_t secondLine);
point_t getLinesIntersectionPoint(line_t firstLine, line_t secondLine);
plane_t getLinesSharedPlane(line_t firstLine, line_t secondLine);
void printLinesReciprocalPosition(line_t firstLine, line_t secondLine);
plane_t getPlaneGivenTwoDirectionVectors(fraction_t v[3][1], fraction_t w[3][1], point_t point);
plane_t getPlaneGivenThreePoints(point_t a, point_t b, point_t c);
point_t getLineAndPlaneIntersectionPoint(line_t line, plane_t plane);
fraction_t getLinearInvariant(int rows, fraction_t matrix[rows][rows]);
fraction_t getQuadraticInvariant(int rows, fraction_t matrix[rows][rows]);
fraction_t getCubicInvariant(int rows, fraction_t matrix[rows][rows]);
fraction_t getQuarticInvariant(int rows, fraction_t matrix[rows][rows]);
void printConicType(fraction_t matrix[3][3]);
void printQuadricType(fraction_t matrix[4][4]);

#endif /* GAL_R3GEOMETRY_H */
