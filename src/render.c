#include "render.h"

void  render(void *appstate)
{
    AppState* state = (AppState*)appstate;

    SDL_SetRenderDrawColor(state->renderer,0,0,0,255);

    SDL_RenderClear(state->renderer);

    for(int i = 0; i < entity_count; i++)
    {
        entities[i].render(state->renderer);
    }

    SDL_RenderPresent(state->renderer);
}