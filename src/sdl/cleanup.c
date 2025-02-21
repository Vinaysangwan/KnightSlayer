#include "cleanup.h"

void SDL_AppQuit(void *appstate,SDL_AppResult result)
{
    AppState* state = (AppState*)appstate;

    for(int i=0; i < entity_count; i++)
    {
        entities[i].cleanup();
    }

    SDL_DestroyRenderer(state->renderer);
    state->renderer = NULL;
    SDL_DestroyWindow(state->window);
    state->window = NULL;

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}