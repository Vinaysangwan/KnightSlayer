#include "init.h"

SDL_AppResult SDL_AppInit(void **appstate,int argc,char **argv)
{
    AppState* state = (AppState*)SDL_malloc(sizeof(AppState));
    *appstate = state;

    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error initializing SDL: %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->window = SDL_CreateWindow("Knight Slayer",900,600,0);
    if(!state->window)
    {
        SDL_Log("Error creating window: %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->renderer = SDL_CreateRenderer(state->window,NULL);
    if(!state->renderer)
    {
        SDL_Log("Error creating renderer: %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

    init_Rect(appstate);

    return SDL_APP_CONTINUE;
}