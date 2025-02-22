#include "player.h"

//****************************************************************************
//************************* Constants ****************************************
//****************************************************************************
#define PLAYER_SPEED 200
#define SPRITE_SIZE 16
#define IDLE_ANIMATION_START_X 128
#define RUN_ANIMATION_START_X 16
#define FRAME_DELAY 3
#define SCALE 3

//****************************************************************************
//************************* Variables ****************************************
//****************************************************************************
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
}PlayerDirection;

PlayerDirection direction = DOWN;

SDL_Texture* player_texture = NULL;
SDL_FRect sprite_position = {IDLE_ANIMATION_START_X,16,SPRITE_SIZE,SPRITE_SIZE};
SDL_FRect player_position = {0,0,SCALE * SPRITE_SIZE, SCALE * SPRITE_SIZE};
float frame_counter = 0;

//****************************************************************************
//************************* Play Player Animation ****************************
//****************************************************************************
void play_Player_Animation(float delta_time,int starting_position_x,int starting_position_y)
{
    frame_counter += delta_time;

    if (frame_counter >= FRAME_DELAY / 60.0f)
    {
        frame_counter = 0;
        sprite_position.y = starting_position_y;

        if(sprite_position.x >= starting_position_x + SPRITE_SIZE * 5) {
            sprite_position.x = starting_position_x;
            return;
        } else {
            sprite_position.x += SPRITE_SIZE;
            return;
        }
    }
}

//****************************************************************************
//************************* Cleanup Player ***********************************
//****************************************************************************
void cleanup_Player()
{
    if(player_texture)
    {
        SDL_DestroyTexture(player_texture);
        player_texture = NULL;
    }
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
    float velocity_x = 0.f , velocity_y = 0.f;

    if(keyboard_state[SDL_SCANCODE_W])
    {
        velocity_y -= PLAYER_SPEED * delta_time;
        direction = UP;
    }
    if(keyboard_state[SDL_SCANCODE_S])
    {
        velocity_y += PLAYER_SPEED * delta_time;
        direction = DOWN;
    }
    if(keyboard_state[SDL_SCANCODE_A])
    {
        velocity_x -= PLAYER_SPEED * delta_time;
        direction = LEFT;
    }
    if(keyboard_state[SDL_SCANCODE_D])
    {
        velocity_x += PLAYER_SPEED * delta_time;
        direction = RIGHT;
    }

    // Normalizing the velocity
    if(velocity_x != 0 && velocity_y != 0)
    {
        velocity_x *= 0.7071f; 
        velocity_y *= 0.7071f; 
    }

    // The Animation x coordinate
    int animation_start_x = (velocity_x == 0 && velocity_y == 0) ? IDLE_ANIMATION_START_X : RUN_ANIMATION_START_X;
    // The animation y coordinate
    int animation_start_y = 0;

    switch (direction) {
        case UP: animation_start_y = 64;break;
        case DOWN: animation_start_y = 16;break;
        case LEFT: animation_start_y = 32;break;
        case RIGHT: animation_start_y = 48;break;
    }

    // Playing the animation
    play_Player_Animation(delta_time,animation_start_x,animation_start_y);
    
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
    if(!player_texture)
    {
        SDL_Log("Error loading player texture: %s",SDL_GetError());
    }

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