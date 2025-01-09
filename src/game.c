#include "game.h"

void run()
{
    struct Config config;           // load configuration value from config.txt
    loadConfiguration(&config);

    struct Actor player;
    initActor(&player, config.screenWidth/2, config.screenHeight/2, 1000, ORANGE, CIRCLE);

    printf("res: %dx%d\n", config.screenWidth, config.screenHeight);        // print the res selected (debug)

    InitWindow(config.screenWidth, config.screenHeight, "Game");
    SetTargetFPS(60);
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLUE);

        // player drawing and movement
        drawActor(&player);
        moveActor(&player);

        EndDrawing();
    }
    CloseWindow();
}          