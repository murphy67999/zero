#include "application.h"

#include "raylib.h"
#include "config.h"

#include "main_menu.h"
#include "endless.h"

static void application_init(struct Application *app);

void application_run(struct Application *app)
{
    application_init(app);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ZERO");

    struct MainMenu menu = {0};
    main_menu_init(&menu);

    struct Endless game = {0};
    endless_init(&game);

    SetTargetFPS(144);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        switch (app->current_state)
        {
        case MAIN_MENU:
            main_menu_run(&menu, &app->current_state);
            break;

        case ENDLESS:
            endless_run(&game);
            break;

        case DEATH:
            // death_run();
            break;
        }

        EndDrawing();
    }
}

static void application_init(struct Application *app)
{
    app->current_state = MAIN_MENU;
}