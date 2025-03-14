#include "collision.h"

bool checkActorsCollision(Actor actor1, Actor actor2)
{
    if(!actor1.isCollidable || !actor2.isCollidable)    // One of the two actors or both of them are not collidable
    {
        printf("\n[Actor: %s and Actor: %s can't collide]", actor1.name, actor2.name);
        return false;    
    }
    else if(actor1.shapeType == RECTANGLE && actor2.shapeType == RECTANGLE) 
    {
        return CheckCollisionRecs(actor1.ShapeData.rectangle, actor2.ShapeData.rectangle);
    }
    else if(actor1.shapeType == RECTANGLE && actor2.shapeType == CIRCLE)        // Rectangle colliding with circle
    {
        Vector2 actor2CircleCenter = (Vector2){actor2.ShapeData.circle.centerX, actor2.ShapeData.circle.centerY};       
        float actor2CircleRadius = actor2.ShapeData.circle.radius;

        // Convert the rectangle values from DrawRectanglePro() coordinate system (origin at the center)
        // to the CheckCollisionCircleRec() coordinate system (the origin is the top left corner)
        float actor1PosX = actor1.ShapeData.rectangle.x - actor1.ShapeData.rectangle.width/2;
        float actor1PosY = actor1.ShapeData.rectangle.y - actor1.ShapeData.rectangle.width/2;
        float actor1Width = actor1.ShapeData.rectangle.width;
        float actor1Height = actor1.ShapeData.rectangle.height;
        Rectangle actor1Rectangle = {actor1PosX, actor1PosY, actor1Width, actor1Height};

        return CheckCollisionCircleRec(actor2CircleCenter, actor2CircleRadius, actor1Rectangle);
    }
    else if(actor1.shapeType == CIRCLE && actor2.shapeType == RECTANGLE)        // Circle colliding with rectangle
    {
        Vector2 actor1CircleCenter = (Vector2){actor1.ShapeData.circle.centerX, actor1.ShapeData.circle.centerY};
        float actor1CircleRadius = actor1.ShapeData.circle.radius;

        // Convert the rectangle values from DrawRectanglePro() coordinate system (origin at the center)
        // to the CheckCollisionCircleRec() coordinate system (the origin is the top left corner)
        float actor2PosX = actor2.ShapeData.rectangle.x - actor2.ShapeData.rectangle.width / 2;
        float actor2PosY = actor2.ShapeData.rectangle.y - actor2.ShapeData.rectangle.height / 2;
        float actor2Width = actor2.ShapeData.rectangle.width;
        float actor2Height = actor2.ShapeData.rectangle.height;
        Rectangle actor2Rectangle = {actor2PosX, actor2PosY, actor2Width, actor2Height};

        return CheckCollisionCircleRec(actor1CircleCenter, actor1CircleRadius, actor2Rectangle);
    }
    else if(actor1.shapeType == CIRCLE && actor2.shapeType == CIRCLE)       // Circle colliding with circle
    {
        Vector2 actor1Collision = (Vector2){actor1.ShapeData.circle.centerX, actor1.ShapeData.circle.centerY};
        float actor1Radius = actor1.ShapeData.circle.radius;
                    
        Vector2 actor2Collision = (Vector2){actor2.ShapeData.circle.centerX, actor2.ShapeData.circle.centerY};
        float radius = actor2.ShapeData.circle.radius;

        return CheckCollisionCircles(actor1Collision, actor1Radius, actor2Collision, radius);
    }

    return false;
}

bool checkAnyCollisionInActorsBuffer(ActorsBuffer actorsBuffer)
{
    bool collision = false;
    for(int i = 0; i < actorsBuffer.actorsCounter; i++)
    {
        Actor actor1 = *actorsBuffer.buffer[i];
        for(int j = i+1; j < actorsBuffer.actorsCounter; j++)
        {
            Actor actor2 = *actorsBuffer.buffer[j];
            collision = checkActorsCollision(actor1, actor2);
            if(collision)
            {
                return collision;
            }
        }
    }
    return false;
}

bool checkActorsCollisionInBuffer(Actor *actor, ActorsBuffer actorsBuffer)
{
    const char *actor1Name = actor->name;
    for(int i = 0; i < actorsBuffer.actorsCounter; i++)
    {
        const char *actor2Name = actorsBuffer.buffer[i]->name;
        int nameComparison = strcmp(actor1Name, actor2Name);
        if(nameComparison != 0 && checkActorsCollision(*actor, *actorsBuffer.buffer[i]))
        {
            return true;
        }
    }
    return false;
}

void resolveCollision(Actor *actor1, Actor *actor2)
{
    if(!checkActorsCollision(*actor1, *actor2))
    {
        return;     // No collision detected no need to resolve
    }
    if(actor1->shapeType == RECTANGLE && actor2->shapeType == RECTANGLE)
    {
        Rectangle rec1 = actor1->ShapeData.rectangle;
        Rectangle rec2 = actor2->ShapeData.rectangle;

        float overlapX = (rec1.width / 2 + rec2.width / 2) - fabs(rec1.x - rec2.x);
        float overlapY = (rec1.height / 2 + rec2.height / 2) - fabs(rec1.y - rec2.y);

        if(overlapX < overlapY)
        {
            if(rec1.x < rec2.x)
            {
                actor1->posX -= overlapX;
            }
            else
            {
                actor1->posX += overlapX;
            }      
        }
        else
        {
            if (rec1.y < rec2.y)
            {
                actor1->posY -= overlapY;
            }
            else
            {
                actor1->posY += overlapY;
            }
        }

        actor1->ShapeData.rectangle.x = actor1->posX;
        actor1->ShapeData.rectangle.y = actor1->posY;
    }
    else if(actor1->shapeType == CIRCLE && actor2->shapeType == CIRCLE)
    {
        Circle circle1 = actor1->ShapeData.circle;
        Circle circle2 = actor2->ShapeData.circle;

        float dx = circle2.centerX - circle1.centerX;
        float dy = circle2.centerY - circle1.centerY;
        float distance = sqrt(dx * dx + dy * dy);
        float overlap = (circle1.radius + circle2.radius) - distance;

        if(overlap > 0)
        {
            float halfOverlap = overlap / 2;

            // Normalize the direction vector
            float normX = dx / distance;
            float normY = dy / distance;

            // Move the circles apart
            actor1->posX -= normX * halfOverlap;
            actor1->posY -= normY * halfOverlap;

            actor1->ShapeData.circle.centerX = actor1->posX;
            actor1->ShapeData.circle.centerY = actor1->posY;
        }
    }
    else if(actor1->shapeType == RECTANGLE && actor2->shapeType == CIRCLE)
    {
        Rectangle rectangle = actor1->ShapeData.rectangle;
        Circle circle = actor2->ShapeData.circle;

        // Find the closest point on the rectangle to the circle
        float closestX = fmax(rectangle.x - rectangle.width / 2, fmin(circle.centerX, rectangle.x + rectangle.width / 2));
        float closestY = fmax(rectangle.y - rectangle.height / 2, fmin(circle.centerY, rectangle.y + rectangle.height / 2));

        // Calculate the distance between the circle's center and this closest point
        float dx = circle.centerX - closestX;
        float dy = circle.centerY - closestY;
        float distance = sqrt(dx * dx + dy * dy);

        // Check if there is a collision
        if(distance < circle.radius)
        {
            // Calculate the overlap 
            float overlap = circle.radius - distance;
            
            // Normalize the direction vector
            float normX = dx / distance;
            float normY = dy / distance;

            // Move the circle out of the rectangle
            actor1->posX -= normX * overlap;
            actor1->posY -= normY * overlap;

            actor1->ShapeData.rectangle.x = actor1->posX;
            actor1->ShapeData.rectangle.y = actor1->posY;
        }
    }
    else if(actor1->shapeType == CIRCLE && actor2->shapeType == RECTANGLE)
    {
        Circle circle = actor1->ShapeData.circle;
        Rectangle rectangle = actor2->ShapeData.rectangle;

        // Find the closest point on the rectangle to the circle
        float closestX = fmax(rectangle.x - rectangle.width / 2, fmin(circle.centerX, rectangle.x + rectangle.width / 2));
        float closestY = fmax(rectangle.y - rectangle.height / 2, fmin(circle.centerY, rectangle.y + rectangle.height / 2));

        // Calculate the distance between the circle's center and this closest point
        float dx = circle.centerX - closestX;
        float dy = circle.centerY - closestY;
        float distance = sqrt(dx * dx + dy * dy);

        // Check if there is a collision
        if(distance < circle.radius)
        {
            // Calculate the overlap 
            float overlap = circle.radius - distance;
            
            // Normalize the direction vector
            float normX = dx / distance;
            float normY = dy / distance;

            // Move the circle out of the rectangle
            actor1->posX += normX * overlap;
            actor1->posY += normY * overlap;

            actor1->ShapeData.circle.centerX = actor1->posX;
            actor1->ShapeData.circle.centerY = actor1->posY;
        }
    }
}

void resolveCollisionInBuffer(Actor *actor, ActorsBuffer actorsBuffer)
{
    const char *actor1Name = actor->name;
    for(int i = 0; i < actorsBuffer.actorsCounter; i++)
    {
        const char *actor2Name = actorsBuffer.buffer[i]->name;
        int nameComparison = strcmp(actor1Name, actor2Name);
        if(nameComparison != 0)
        {
            resolveCollision(actor, actorsBuffer.buffer[i]);
        }
    }
}