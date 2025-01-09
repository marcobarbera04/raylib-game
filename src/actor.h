#ifndef ACTOR_H
#define ACTOR_H

#include "math.h"
#include "..\include\raylib.h"
#include "shape.h"

typedef struct Actor
{
    float posX;
    float posY;
    float speed;
    Color color;
    ShapeType shapeType;
    union
    {
        Triangle triangle;
        Rectangle rectangle;
        Circle circle;
    }ShapeData;
}Actor;

void initActor(Actor *actor, float posX, float posY, float speed, Color color, ShapeType shapeType);

// load shape data depending on wich shape the actor has assigned
void loadTriangleData(Actor *actor, int sideLength, Color color);
void loadRectangleData(Actor *actor, float width, float height);
void loadCircleData(Actor *actor, float radius, Color color);

void moveX(Actor *actor, float X);
void moveY(Actor *actor, float Y);

void moveActor(Actor *actor);

#endif