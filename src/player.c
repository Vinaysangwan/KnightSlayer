#include "player.h"

//****************************************************************************
//************************* Variables ****************************************
//****************************************************************************
SDL_Texture* player_texture = NULL;
const SDL_FRect sprite_position = {16,16,16,16};
const SDL_FRect player_position = {100,100,16,16};

//****************************************************************************
//************************* Cleanup Player ***********************************
//****************************************************************************
void cleanup_Player()
{

}

//****************************************************************************
//************************* Handle Event Player ******************************
//****************************************************************************
void handle_Event_Player(SDL_Event* event)
{

}

//****************************************************************************
//************************* Update Player ************************************
//****************************************************************************
void update_Player(float delta_time)
{

}

//****************************************************************************
//************************* Render Player ************************************
//****************************************************************************
void render_Player(SDL_Renderer* renderer)
{
    SDL_RenderTexture(renderer,player_texture,&sprite_position,&player_position);
}

//****************************************************************************
//************************* Init Player **************************************
//****************************************************************************
void init_Player(void *appstate)
{
    AppState* state = (AppState*)appstate;

    const char path[] = "./assets/Char_Sprites/char_spritesheet.png";
    player_texture = IMG_LoadTexture(state->renderer, path);

    // Making the texture pixelated(Better for pixel art)
    SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);

    Entity player = {
        .render = render_Player,
        .cleanup = cleanup_Player,
        .handle_Event = handle_Event_Player,
        .update = update_Player,
    };

    create_Entity(player);
}