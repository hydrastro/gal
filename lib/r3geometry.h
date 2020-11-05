#ifndef R3GEOMETRY_H
#define R3GEOMETRY_H

// defining new types
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

#endif //R3GEOMETRY_H
