#include "player.h"

//****************************************************************************
//************************* Variables ****************************************
//****************************************************************************
SDL_Texture* player_texture = NULL;
SDL_FRect sprite_position = {128,16,16,16};
const int ispeed = 200;
SDL_FRect player_position = {0,0,32,32};
float fps = 0;
char direction = 's';

//****************************************************************************
//************************* Play Player Animation ****************************
//****************************************************************************
void play_Player_Animation(int starting_position_x,int starting_position_y)
{
    if (fps/60 >= 3)
    {
        fps = 0;
        sprite_position.y = starting_position_y;

        if(sprite_position.x >= starting_position_x + 16 * 5) {
            sprite_position.x = starting_position_x;
        } else {
            sprite_position.x += 16;
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
    int velocity[] = {0,0};

    if(keyboard_state[SDL_SCANCODE_W])
    {
        velocity[1] -= ispeed * delta_time;
        direction = 'w';
    }
    if(keyboard_state[SDL_SCANCODE_S])
    {
        velocity[1] += ispeed * delta_time;
        direction = 's';
    }
    if(keyboard_state[SDL_SCANCODE_A])
    {
        velocity[0] -= ispeed * delta_time;
        direction = 'a';
    }
    if(keyboard_state[SDL_SCANCODE_D])
    {
        velocity[0] += ispeed * delta_time;
        direction = 'd';
    }

    fps++;

    // When the player is Idle
    if(velocity[0] == 0 && velocity[1] == 0){
        if(direction == 'w'){
            play_Player_Animation(128,64);
        } else if(direction == 's'){
            play_Player_Animation(128,16);
        } else if(direction == 'a'){
            play_Player_Animation(128,32);
        } else if(direction == 'd'){
            play_Player_Animation(128,48);
        }
    } 
    
    // When the player is in motion
    else {
        if(direction == 'w'){
            play_Player_Animation(16,64);
        } else if(direction == 's'){
            play_Player_Animation(16,16);
        } else if(direction == 'a'){
            play_Player_Animation(16,32);
        } else if(direction == 'd'){
            play_Player_Animation(16,48);
        }
    }

    player_position.x += velocity[0];
    player_position.y += velocity[1];
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