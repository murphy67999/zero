#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "raylib.h"
#include "app_state.h"

struct MainMenu
{
    // background
    Texture2D background;
    Color tint;
};

void main_menu_init(struct MainMenu *menu);
void main_menu_run(struct MainMenu *menu, enum AppState *current_state);

#endif