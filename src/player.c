#include "player.h"

//****************************************************************************
//************************* Variables ****************************************
//****************************************************************************
#define PLAYER_SPEED 200
#define SPRITE_SIZE 16
#define IDLE_ANIMATION_START_X 128
#define RUN_ANIMATION_START_X 16
#define FRAME_DELAY 2
#define SCALE 1

SDL_Texture* player_texture = NULL;
SDL_FRect sprite_position = {IDLE_ANIMATION_START_X,16,SPRITE_SIZE,SPRITE_SIZE};
SDL_FRect player_position = {0,0,SCALE * SPRITE_SIZE, SCALE * SPRITE_SIZE};
float frame_counter = 0;
char direction = 's'; // Direction of the player Movement

//****************************************************************************
//************************* Play Player Animation ****************************
//****************************************************************************
void play_Player_Animation(int starting_position_x,int starting_position_y)
{
    if (frame_counter/60 >= FRAME_DELAY)
    {
        frame_counter = 0;
        sprite_position.y = starting_position_y;

        if(sprite_position.x >= starting_position_x + SPRITE_SIZE * 5) {
            sprite_position.x = starting_position_x;
        } else {
            sprite_position.x += SPRITE_SIZE;
        }
    }
}

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
    const _Bool* keyboard_state = SDL_GetKeyboardState(NULL);
    float velocity_x = 0 , velocity_y = 0;

    if(keyboard_state[SDL_SCANCODE_W])
    {
        velocity_y -= PLAYER_SPEED * delta_time;
        direction = 'w';
    }
    if(keyboard_state[SDL_SCANCODE_S])
    {
        velocity_y += PLAYER_SPEED * delta_time;
        direction = 's';
    }
    if(keyboard_state[SDL_SCANCODE_A])
    {
        velocity_x -= PLAYER_SPEED * delta_time;
        direction = 'a';
    }
    if(keyboard_state[SDL_SCANCODE_D])
    {
        velocity_x += PLAYER_SPEED * delta_time;
        direction = 'd';
    }

    // Normalizing the velocity
    if(velocity_x != 0 && velocity_y != 0)
    {
        velocity_x *= 0.7071f; 
        velocity_y *= 0.7071f; 
    }

    frame_counter++;

    // The Animation x coordinate
    int animation_start_x = (velocity_x == 0 && velocity_y == 0) ? IDLE_ANIMATION_START_X : RUN_ANIMATION_START_X;
    // The animation y coordinate
    int animation_start_y = 0;

    switch (direction) {
        case 'w': animation_start_y = 64;break;
        case 's': animation_start_y = 16;break;
        case 'a': animation_start_y = 32;break;
        case 'd': animation_start_y = 48;break;
    }

    // Playing the animation
    play_Player_Animation(animation_start_x,animation_start_y);
    
    player_position.x += velocity_x;
    player_position.y += velocity_y;
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
    if(!SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST))
    {
        SDL_Log("Error setting texture scale mode: %s",SDL_GetError());
    }

    Entity player = {
        .render = render_Player,
        .cleanup = cleanup_Player,
        .handle_Event = handle_Event_Player,
        .update = update_Player,
    };

    create_Entity(player);
}