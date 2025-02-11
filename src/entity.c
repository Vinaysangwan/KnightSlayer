#include "entity.h"

Entity entities[MAX_ENTITIES];
int entity_count = 0;

void create_Entity(Entity entity)
{
    if(entity_count < MAX_ENTITIES)
    {
        entities[entity_count] = entity;
        entity_count++;
    }
    else
    {
        SDL_Log("Error: Maximum number of entities reached.");
    }
}

void delete_Entity(int index)
{
    if(index < entity_count && index >= 0)
    {
        entities[index].cleanup();
        for(int i = index; i < entity_count - 1; i++)
        {
            entities[i] = entities[i + 1];
        }
        entity_count--;
    }
    else
    {
        SDL_Log("Error: Entity index out of bounds.");
    }
}

void swap_Entities(int index1,int index2)
{
    if(index1 < entity_count && index1 >= 0 && index2 >= 0 && index2 < entity_count)
    {
        Entity temp = entities[index1];
        entities[index1] = entities[index2];
        entities[index2] = temp;
    }
    else
    {
        SDL_Log("Error: Entity index out of bounds.");
    }
}