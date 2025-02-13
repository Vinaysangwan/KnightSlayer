#include "event.h"

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if(event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    else if(event->type == SDL_EVENT_KEY_DOWN)
    {
        if(event->key.key == SDLK_ESCAPE)
        {
            return SDL_APP_SUCCESS;
        }
    }

    for(int i = 0; i < entity_count; i++)
    {
        entities[i].handle_Event(event);
    }

    return SDL_APP_CONTINUE;
}