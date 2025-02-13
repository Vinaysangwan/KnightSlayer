#pragma once
#include "common.h"

#define MAX_ENTITIES 100

typedef struct
{
    void(*render)(SDL_Renderer*);
    void(*update)(float);
    void(*handle_Event)(SDL_Event*);
    void(*cleanup)(void);
}Entity;

extern Entity entities[MAX_ENTITIES];
extern int entity_count;
void create_Entity(Entity entity);
void delete_Entity(int index);
void swap_Entities(int index1,int index2);