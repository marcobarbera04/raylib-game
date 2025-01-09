#include "drawActor.h"

void drawActor(Actor *actor)
{
    switch(actor->shapeType)
    {
        case TRIANGLE:
            loadTriangleData(actor, 100, actor->color);         // load triangle data (v1, v2, v3, color)
            DrawTriangle(actor->ShapeData.triangle.v1, actor->ShapeData.triangle.v2, actor->ShapeData.triangle.v3, actor->ShapeData.triangle.color);
            DrawCircle(actor->posX, actor->posY, 10, WHITE);    // draw circle in the actor location (debug)
            break;
        case RECTANGLE:
            loadRectangleData(actor, 50, 50);
            DrawRectangle(actor->ShapeData.rectangle.x, actor->ShapeData.rectangle.y, actor->ShapeData.rectangle.width, actor->ShapeData.rectangle.height, actor->color);
            DrawCircle(actor->posX, actor->posY, 5, WHITE);     // draw circle in the actor location (debug)
            break;
        case CIRCLE:
            loadCircleData(actor, 25, actor->color);
            DrawCircle(actor->ShapeData.circle.centerX, actor->ShapeData.circle.centerY, actor->ShapeData.circle.radius, actor->ShapeData.circle.color);
            DrawCircle(actor->posX, actor->posY, 5, WHITE);     // draw circle in the actor location (debug)
            break;
        default:
            printf("\n[ERROR] unable to properly draw actor shape\n");
            const char *errorText = "ERROR";
            int fontSize = 50;
            int errorTextPosX = actor->posX - (MeasureText(errorText, fontSize)/2);
            int errorTextPosY = actor->posY - (fontSize/2);
            DrawText(errorText, errorTextPosX, errorTextPosY, 50, RED);
            break;
    }
}
