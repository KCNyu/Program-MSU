#ifndef __MAP_H__
#define __MAP_H__

#include "maptypes.h"

int initializeMap(Map *map, int size);

void finalizeMap(Map *map);

int addElement(Map *map, Key *key, Value *value);

int removeElement(Map *map, Key *key, Value *value);

int getElement(Map *map, Key *key, Value *value);

#endif // __MAP_H__
