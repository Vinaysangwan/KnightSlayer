#include "rect.h"

SDL_FRect rect;

void cleanup_Rect()
{

}

void handle_Event_Rect(SDL_Event *event)
{

}

void update_Rect()
{

}

void render_Rect(void *appstate)
{
    AppState *state = (AppState *)appstate;

    SDL_SetRenderDrawColor(state->renderer,255,0,0,255);
}

void init_Rect(void *appstate)
{
    AppState *state = (AppState *)appstate;

    rect.x = 50;
    rect.y = 50;
    rect.w = 100;
    rect.h = 100;
    
    if(!SDL_SetRenderDrawColor(state->renderer,255,0,0,255))
    {
        SDL_Log("Error setting draw color: %s",SDL_GetError());
    }

    Entity rect = {
        .render = render_Rect,
        .update = update_Rect,
        .handle_Event = handle_Event_Rect,
        .cleanup = cleanup_Rect,
    };
}