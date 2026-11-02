#include "game.h"
#include "raylib.h"
#include "player.h"

void gameRun(struct Game *game)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "zero");
    SetTargetFPS(60);

    gameInit(game);

    while (!WindowShouldClose())
    {
        gameUpdate(game);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        gameDraw(game);

        EndDrawing();
    }

    CloseWindow();
}

void gameInit(struct Game *game)
{
    playerInit(&game->player);
}

void gameUpdate(struct Game *game)
{
    playerUpdate(&game->player);
}

void gameDraw(struct Game *game)
{
    playerDraw(&game->player);
}