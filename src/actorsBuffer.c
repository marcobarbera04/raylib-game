#include "actorsBuffer.h"

void initActorsBuffer(ActorsBuffer *actorsBuffer)
{
    actorsBuffer->actorsCounter = 0;
}

void insertActorInBuffer(Actor *actor, ActorsBuffer *actorsBuffer)
{
    if(actorsBuffer->actorsCounter >= MAX_ENTITIES)
    {
        printf("\n[BUFFER ERROR]: Actors buffer is full!");
        printf("[BUFFER ERROR]: Couldn't insert actor into buffer!");
        return;
    }
    actorsBuffer->buffer[actorsBuffer->actorsCounter] = actor;
    actorsBuffer->actorsCounter++;
}

Actor* getActorFromBuffer(ActorsBuffer *actorsBuffer, const char *name)
{
    for(int i = 0; i < actorsBuffer->actorsCounter; i++)
    {
        if(strcmp(actorsBuffer->buffer[i]->name, name) == 0)
        {
            Actor *actor = actorsBuffer->buffer[i];
            return actor;
        }
    }
    printf("\n[BUFFER ERROR]: Actor not found in the buffer");
    return NULL;
}