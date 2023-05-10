#include <stdlib.h>
#include <string.h>
#include "map.h"

int initializeMap(Map *map, int size)
{
    if (size < 0)
    {
        return -1;
    }
    map->items = (Item *)malloc(size * sizeof(Item));
    if (map->items == NULL)
    {
        return -1;
    }
    map->capacity = size;
    map->count = 0;
    for (int i = 0; i < size; i++)
    {
        map->items[i].existent = 0;
    }
    return 0;
}

void finalizeMap(Map *map)
{
    free(map->items);
    map->items = NULL;
    map->capacity = 0;
    map->count = 0;
}

int addElement(Map *map, Key *key, Value *value)
{
    if (map->count == map->capacity)
    {
        return 0;
    }
    map->items[map->count].key = *key;
    map->items[map->count].value = *value;
    map->items[map->count].existent = 1;
    map->count += 1;
    return 1;
}

int removeElement(Map *map, Key *key, Value *value)
{
    for (int i = 0; i < map->count; i++)
    {
        if (map->items[i].key.a == key->a && map->items[i].key.b == key->b)
        {
            if (value != NULL)
            {
                *value = map->items[i].value;
            }
            memmove(&map->items[i], &map->items[i + 1], (map->count - i - 1) * sizeof(Item));
            map->count -= 1;
            return 1;
        }
    }
    return 0;
}

int getElement(Map *map, Key *key, Value *value)
{
    for (int i = 0; i < map->count; i++)
    {
        if (map->items[i].key.a == key->a && map->items[i].key.b == key->b)
        {
            if (value != NULL)
            {
                *value = map->items[i].value;
            }
            return 1;
        }
    }
    return 0;
}
