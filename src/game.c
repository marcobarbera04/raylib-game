#include "game.h"
#include "actor.h"

const int screenWidth = 1080;
const int screenHeight = 1080;

void run()
{
    struct Actor player;
    initActor(&player, 540, 540, 50, 50, 1000, ORANGE);

    const int screenWidth = 1080;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Game");
    SetTargetFPS(60);
    while(WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(BLUE);
        moveActor(&player);
        DrawRectangle(player.posX, player.posY, player.sizeX, player.sizeY, player.color);

        EndDrawing();
    }
    CloseWindow();
}          