#ifndef __MAPTYPES_H__
#define __MAPTYPES_H__

typedef struct {
    int a;
    int b;
} Key;

typedef struct {
    int c;
    int d;
} Value;

typedef struct {
    Key key __attribute__((noembed));
    Value value;
    int existent;
} Item;

typedef struct {
    Item *items;
    int capacity;
    int count;
} Map;

#endif // __MAPTYPES_H__
