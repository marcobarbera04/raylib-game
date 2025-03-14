#include "actor.h"

extern double TimeElapsed;

void initActor(Actor *actor, const char *name, float posX, float posY, float speed, bool isCollidable, Color color, ActorType actorType, ShapeType shapeType){
    actor->name = name;
    actor->posX = posX;
    actor->posY = posY;
    actor->speed = speed;
    actor->isCollidable = isCollidable;
    actor->color = color;
    actor->actorType = actorType;
    actor->shapeType = shapeType;
    if(shapeType == RECTANGLE)
    {
        actor->ShapeData.rectangle = (Rectangle){0};
    }
    else if(shapeType == CIRCLE)
    {
        actor->ShapeData.circle = (Circle){0};
    }
    else if(shapeType == TRIANGLE)
    {
        actor->ShapeData.triangle = (Triangle){0};
        actor->isCollidable = false;        // Set collision false if the actor is a triangle because triangle collision are non implemented intentionally
    }
}

void updateTriangleData(Actor *actor, float sideLength)
{
    // First vertex (top)
    Vector2 v1; 
    v1.x = actor->posX; 
    v1.y = actor->posY - sqrt(3.0f) / 3 * sideLength;

    // Second vertex (bottom-left)
    Vector2 v2; 
    v2.x = actor->posX - sideLength / 2.0f; 
    v2.y = actor->posY + sqrt(3) / 6.0f * sideLength; 
    
    // Third vertex (bottom right)
    Vector2 v3; 
    v3.x = actor->posX + sideLength / 2.0f; 
    v3.y = actor->posY + sqrt(3.0f) / 6.0f * sideLength;       

    actor->ShapeData.triangle.v1 = v1;
    actor->ShapeData.triangle.v2 = v2;
    actor->ShapeData.triangle.v3 = v3;
}

void updateRectangleData(Actor *actor, float width, float height)
{
    float x = actor->posX;
    float y = actor->posY;

    actor->ShapeData.rectangle.x = x;
    actor->ShapeData.rectangle.y = y;

    actor->ShapeData.rectangle.width = width;
    actor->ShapeData.rectangle.height = height; 
}

void updateCircleData(Actor *actor, float radius)
{
    float x = actor->posX;
    float y = actor->posY;

    actor->ShapeData.circle.centerX = x;
    actor->ShapeData.circle.centerY = y;

    actor->ShapeData.circle.radius = radius;
}

void updateShape(Actor *actor)
{
    switch(actor->shapeType)
    {
        case TRIANGLE:
            updateTriangleData(actor, TRIANGLE_SIDE_LENGTH);                    // Update triangle data (v1, v2, v3, color)
            break;
        case RECTANGLE:
            updateRectangleData(actor, RECTANGLE_WIDTH, RECTANGLE_HEIGHT);      // Update rectangle data (x, y, width, heigth)
            break;
        case CIRCLE:
            updateCircleData(actor, CIRCLE_RADIUS);                             // Update circle data (centerX, centerY, radius, color)
            break;
        default:
            printf("\n[ERROR]: Actor: %s shape did not get updated", actor->name);
            break;
    }
}

void drawActor(Actor *actor)
{
    switch(actor->shapeType)
    {
        case TRIANGLE:
            updateShape(actor);       
            DrawTriangle(actor->ShapeData.triangle.v1, actor->ShapeData.triangle.v2, actor->ShapeData.triangle.v3, actor->color);
            break;
        case RECTANGLE:
            Vector2 rectangleOrigin = (Vector2){RECTANGLE_WIDTH / 2, RECTANGLE_HEIGHT / 2};       // Calculate the rectangle orign on the center
            updateShape(actor);
            DrawRectanglePro(actor->ShapeData.rectangle, rectangleOrigin, 0.0f, actor->color);
            break;
        case CIRCLE:
            updateShape(actor);        
            Vector2 circleCenter = (Vector2){actor->ShapeData.circle.centerX, actor->ShapeData.circle.centerY};
            DrawCircleV(circleCenter, actor->ShapeData.circle.radius, actor->color);
            break;
        default:
            printf("\n[ERROR] unable to properly draw actor shape\n");
            const char *text = "ERROR";
            float fontSize = 50.0;
            float spacing = 5.0f;

            Vector2 textPosition = {actor->posX, actor->posY};
            Vector2 textMeasure = MeasureTextEx(GetFontDefault(), text, fontSize, spacing);
            Vector2 textOrigin = {textMeasure.x/2, textMeasure.y/2};

            // Interval the color changing every n seconds
            double intervalInSeconds = 0.2; 
            Color errorColor = ((int)(TimeElapsed / intervalInSeconds) % 2 == 0) ? RED : (Color){130, 23, 29, 255};

            DrawTextPro(GetFontDefault(), text, textPosition, textOrigin, 0.0f, fontSize, spacing, errorColor);
            break;
    }
}

void moveActorX(Actor *actor, float x)
{
    float newPosX = actor->posX + (float)(x * GetFrameTime());
    actor->posX = newPosX;
}

void moveActorY(Actor *actor, float y)
{
    float newPosY = actor->posY + (float)(y * GetFrameTime());
    actor->posY = newPosY;
}