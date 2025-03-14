#include "player.h"

void updatePlayerPosition(Actor *actor)
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

    // Normalize diagonal speed
    if(movementX != 0.0f && movementY != 0.0f)
    {
        movementX *= 0.7071f; // 1/sqrt(2) 
        movementY *= 0.7071f; // 1/sqrt(2)
    }
    moveActorX(actor, movementX);
    moveActorY(actor, movementY);
}

void initCamera2D(Camera2D *camera, Actor *actor, Config config)
{
    camera->target = (Vector2){actor->posX, actor->posY};
    camera->offset = (Vector2){config.screenWidth/2, config.screenHeight/2};
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}

void updateCameraTarget(Camera2D *camera, Actor actor)
{
    camera->target = (Vector2){actor.posX, actor.posY};
}