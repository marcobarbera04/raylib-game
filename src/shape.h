#ifndef SHAPE_C
#define SHAPE_C

#include "..\include\raylib.h"

typedef enum
{
    TRIANGLE = 0,
    RECTANGLE = 1,
    CIRCLE = 2,
}ShapeType;

typedef struct Triangle    
{
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
}Triangle;

typedef struct Circle       
{
    float centerX;
    float centerY;
    float radius;
}Circle;

#endif