#include "game.h"

double TimeElapsed = 0;

void run()
{
    Config config = {0};  
    loadConfiguration(&config);         // Load configuration value from config.txt

    Actor player = {0};
    initActor(&player, "Player",config.screenWidth/2, config.screenHeight/2, 500.0f, true, ORANGE, PLAYER, CIRCLE);

    Actor enemy = {0};
    initActor(&enemy, "Enemy", 700.0f, 700.0f, 500, true, RED, ENEMY, RECTANGLE);

    Actor foo = {0};
    initActor(&foo, "Foo", 500.0f, 700.0f, 500, true, RED, SOLID, RECTANGLE);

    ActorsBuffer actorsBuffer = {0};
    initActorsBuffer(&actorsBuffer);

    insertActorInBuffer(&player, &actorsBuffer);
    insertActorInBuffer(&enemy, &actorsBuffer);
    insertActorInBuffer(&foo, &actorsBuffer);

    //Camera2D camera = {0};
    //initCamera2D(&camera, &player, config);
 
    InitWindow(config.screenWidth, config.screenHeight, "Game");
    SetTargetFPS(60);
    while(WindowShouldClose() == false)
    {
        TimeElapsed = GetTime();
        
        updatePlayerPosition(&player);
        resolveCollisionInBuffer(&player, actorsBuffer);

        //updateCameraTarget(&camera, player);

        BeginDrawing();
        ClearBackground(BLUE);

        //BeginMode2D(camera);

        for(int i = 0; i < actorsBuffer.actorsCounter; i++)
        {
            drawActor(actorsBuffer.buffer[i]);
        }
        //EndMode2D();                
        EndDrawing();
    }
    CloseWindow();
}          