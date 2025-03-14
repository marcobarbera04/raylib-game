#ifndef ACTOR_H
#define ACTOR_H

#include <stdio.h>
#include <math.h>
#include "..\include\raylib.h"
#include "shape.h"

#define TRIANGLE_SIDE_LENGTH 50.0f
#define RECTANGLE_WIDTH 50.0f 
#define RECTANGLE_HEIGHT 50.0f
#define CIRCLE_RADIUS 25.0f

typedef enum
{
    PLAYER = 0,
    ENEMY = 1,
    SOLID = 2,
}ActorType;

typedef struct Actor
{
    const char *name;
    float posX;
    float posY;
    float speed;
    bool isCollidable;
    Color color;
    ActorType actorType;
    ShapeType shapeType;
    union
    {
        Triangle triangle;
        Rectangle rectangle;
        Circle circle;
    }ShapeData;
}Actor;

void initActor(Actor *actor, const char *name, float posX, float posY, float speed, bool isCollidable, Color color, ActorType actorType, ShapeType shapeType);
 
void updateTriangleData(Actor *actor, float sideLength);                    // Update the position of the shape
void updateRectangleData(Actor *actor, float width, float height);          // Update the position of the shape
void updateCircleData(Actor *actor, float radius);                          // Update the position of the shape

void updateShape(Actor *actor);                                             // Update shape data and shape collision all at once

void drawActor(Actor *actor);

void moveActorX(Actor *actor, float x);
void moveActorY(Actor *actor, float y);

#endif