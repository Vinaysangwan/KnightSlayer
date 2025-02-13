#include "update.h"

void update(void *appstate)
{
    AppState *state = (AppState *)appstate;

    // Calculating Delta Time
    state->last_tick = state->current_tick;
    state->current_tick = SDL_GetTicks();
    state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;

    for (int i = 0; i < entity_count; i++)
    {
        entities[i].update(state->delta_time);
    }
}