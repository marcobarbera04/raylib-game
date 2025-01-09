#include "actor.h"

void initActor(Actor* actor, float posX, float posY, float speed, Color color, ShapeType shapeType){
    actor->posX = posX;
    actor->posY = posY;
    
    actor->speed = speed;
    actor->color = color;
    actor->shapeType = shapeType;
}

void loadTriangleData(Actor *actor, int sideLength, Color color)
{
    // first vertex (top)
    Vector2 v1; 
    v1.x = actor->posX; 
    v1.y = actor->posY - sqrt(3.0f) / 3 * sideLength;

    // second vertex (bottom-left)
    Vector2 v2; 
    v2.x = actor->posX - sideLength / 2.0f; 
    v2.y = actor->posY + sqrt(3) / 6.0f * sideLength; 
    
    // third vertex (bottom right)
    Vector2 v3; 
    v3.x = actor->posX + sideLength / 2.0f; 
    v3.y = actor->posY + sqrt(3.0f) / 6.0f * sideLength;       

    actor->ShapeData.triangle.v1 = v1;
    actor->ShapeData.triangle.v2 = v2;
    actor->ShapeData.triangle.v3 = v3;

    actor->ShapeData.triangle.color = color;
}

void loadRectangleData(Actor *actor, float width, float height)
{
    int x = actor->posX - width/2;       // rectangle top-left corner position x
    int y = actor->posY - height/2;      // rectangle top-left corner position y

    actor->ShapeData.rectangle.x = x;
    actor->ShapeData.rectangle.y = y;
    actor->ShapeData.rectangle.width = width;
    actor->ShapeData.rectangle.height = height; 
}

void loadCircleData(Actor *actor, float radius, Color color)
{
    int x = actor->posX;
    int y = actor->posY;

    actor->ShapeData.circle.centerX = x;
    actor->ShapeData.circle.centerY = y;
    actor->ShapeData.circle.radius = radius;
    actor->ShapeData.circle.color = color;
}

void moveX(Actor *actor, float X)
{
    actor->posX += GetFrameTime() * X;
}

void moveY(Actor *actor, float Y)
{
    actor->posY += GetFrameTime() * Y;
}

void moveActor(Actor *actor)
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

    // normalize diagonal speed
    if(movementX != 0.0f && movementY != 0.0f)
    {
        movementX *= 0.7071f; // 1/sqrt(2) 
        movementY *= 0.7071f; // 1/sqrt(2)
    }

    moveX(actor, movementX);
    moveY(actor, movementY);
}