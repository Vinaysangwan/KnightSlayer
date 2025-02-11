#include "update.h"

void update(void *appstate)
{
    AppState *state = (AppState *)appstate;

    for (int i = 0; i < entity_count; i++)
    {
        entities[i].update();
    }
}