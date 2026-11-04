#ifndef APPLICATION_H
#define APPLICATION_H

#include "app_state.h"

struct Application
{
    enum AppState current_state;
};

void application_run(struct Application *app);

#endif