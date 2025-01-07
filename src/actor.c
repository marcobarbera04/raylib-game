#include "actor.h"

void initActor(struct Actor* actor, float posX, float posY, float sizeX, float sizeY, float speed, Color color){
    actor->posX = posX;
    actor->posY = posY;
    actor->sizeX = sizeX;
    actor->sizeY = sizeY;
    
    actor->speed = speed;
    actor->color = color;
}

void moveX(struct Actor *actor, float X)
{
    actor->posX += GetFrameTime() * X;
}

void moveY(struct Actor *actor, float Y)
{
    actor->posY += GetFrameTime() * Y;
}

void moveActor(struct Actor *actor)
{
    float moveSpeed = actor->speed;
    float movementX = 0.0f;
    float movementY = 0.0;

    if(IsKeyDown(KEY_RIGHT))
    {
        movementX += moveSpeed;
    }
    if(IsKeyDown(KEY_LEFT))
    {
        movementX -= moveSpeed;
    }
    if(IsKeyDown(KEY_UP))
    {
        movementY -= moveSpeed;
    }
    if(IsKeyDown(KEY_DOWN))
    {
        movementY += moveSpeed;
    }

    //Normalize diagonal speed
    if(movementX != 0.0f && movementY != 0.0f)
    {
        movementX *= 0.7071f; // 1/sqrt(2) 
        movementY *= 0.7071f; // 1/sqrt(2)
    }

    moveX(actor, movementX);
    moveY(actor, movementY);
}