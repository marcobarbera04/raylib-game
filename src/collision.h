#ifndef COLLISION_H
#define COLLISION_H

#include "..\include\raylib.h"
#include "actor.h"
#include "actorsBuffer.h"

bool checkActorsCollision(Actor actor1, Actor actor2);                      // Check if two actors does collide

bool checkAnyCollisionInActorsBuffer(ActorsBuffer actorsBuffer);            // Check in the actorsBuffer if any collision is happening

bool checkActorsCollisionInBuffer(Actor *actor, ActorsBuffer actorsBuffer); // Check if the actor collide with any other actor in the buffer

void resolveCollision(Actor *actor1, Actor *actor2);                        // Resolve collision between two specific actors

void resolveCollisionInBuffer(Actor *actor, ActorsBuffer actorsBuffer);     // Resolve collision between a specific actor and any actor in buffer

#endif