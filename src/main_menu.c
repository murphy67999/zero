#include "main_menu.h"

#include "config.h"
#include "raygui.h"

static void update();
static void draw(const struct MainMenu *menu, enum AppState *current_state);

void main_menu_init(struct MainMenu *menu)
{
    menu->background = LoadTexture("assets/background.png");
    menu->tint = ColorAlpha(WHITE, 0.05f);
}

void main_menu_run(struct MainMenu *menu, enum AppState *current_state)
{
    update();
    draw(menu, current_state);
}

static void update()
{
}

static void draw(const struct MainMenu *menu, enum AppState *current_state)
{
    ClearBackground(BLACK);
    DrawTexture(menu->background, 0, 0, menu->tint);

    int textWidth = MeasureText("ZERO", 100);
    DrawText("ZERO", SCREEN_CENTER_X - textWidth / 2, WINDOW_HEIGHT / 5, 100, RAYWHITE);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

    int buttonWidth = 150;
    int buttonHeight = 50;
    if (GuiButton((Rectangle){SCREEN_CENTER_X - buttonWidth / 2, SCREEN_CENTER_Y, buttonWidth, buttonHeight}, "Endless"))
    {
        *current_state = ENDLESS;
    }
}