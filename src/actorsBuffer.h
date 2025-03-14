#ifndef ACTORS_BUFFER_H
#define ACTORS_BUFFER_H

#include <string.h>
#include <stdio.h>
#include "actor.h"

#define MAX_ENTITIES 100                // Max size of the buffer

typedef struct ActorsBuffer
{
    Actor *buffer[MAX_ENTITIES];        // Buffer of pointers to Actor structs
    unsigned int actorsCounter;
}ActorsBuffer;

void initActorsBuffer(ActorsBuffer *actorsBuffer);                          // Initialize buffer by assigning 0 to the actorCounter variable
void insertActorInBuffer(Actor *actor, ActorsBuffer *actorsBuffer);         // Insert an actor into the buffer

Actor* getActorFromBuffer(ActorsBuffer *actorsBuffer, const char *name);    // Get the actor from a buffer by reference

#endif