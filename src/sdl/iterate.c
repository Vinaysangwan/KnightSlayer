#include "iterate.h"

SDL_AppResult SDL_AppIterate(void *appstate)
{
    update(appstate);
    render(appstate);

    return SDL_APP_CONTINUE;
}