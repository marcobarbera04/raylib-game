#include "game.h"

void run()
{
    struct Config config;
    loadConfiguration(&config);

    struct Actor player;
    initActor(&player, 540, 540, 50, 50, 1000, ORANGE);

    printf("res: %dx%d\n", config.screenWidth, config.screenHeight);
    InitWindow(config.screenWidth, config.screenHeight, "Game");
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