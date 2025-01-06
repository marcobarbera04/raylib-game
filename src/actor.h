#ifndef ACTOR_H
#define ACTOR_H

#include "..\include\raylib.h"

struct Actor
{
    float posX;
    float posY;
    float sizeX;
    float sizeY;

    float speed;
    Color color;
};

void initActor(struct Actor *actor, float posX, float posY, float sizeX, float sizeY, float speed, Color color);

void moveX(struct Actor *actor, float X);
void moveY(struct Actor *actor, float Y);

void moveActor(struct Actor *actor);

#endif 