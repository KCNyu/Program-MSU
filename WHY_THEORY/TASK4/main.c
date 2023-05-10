#include "map.h"
#include <stdio.h>
#include <stdarg.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

void check(char *test_name, int expected, int obtained, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    if (obtained != expected)
    {
        printf(ANSI_COLOR_RED "Test failed: %s\n", test_name);
        printf("Obtained: %d, Expected: %d\n", obtained, expected);
        printf(ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_GREEN "Test passed: %s\n" ANSI_COLOR_RESET, test_name);
        vprintf(format, args);
    }

    va_end(args);
}

int main()
{
    // Initialize a map with negative capacity
    Map neg_map;
    int result = initializeMap(&neg_map, -1);
    check("Initialization with negative capacity", -1, result, "Map initialized with capacity: %d\n", -1);
    // Initialize a map
    Map map;
    result = initializeMap(&map, 2);
    check("Initialization", 0, result, "Map initialized with capacity: %d\n", 10);

    // Test adding elements
    Key key1 = {1, 2};
    Value value1 = {3, 4};
    result = addElement(&map, &key1, &value1);
    check("Adding element1", 1, result, "Element added with key: %d,%d and value: %d,%d\n", key1.a, key1.b, value1.c, value1.d);

    Key key2 = {5, 6};
    Value value2 = {7, 8};
    result = addElement(&map, &key2, &value2);
    check("Adding element2", 1, result, "Element added with key: %d,%d and value: %d,%d\n", key2.a, key2.b, value2.c, value2.d);

    // Test getting an element
    Value retrieved_value;
    result = getElement(&map, &key1, &retrieved_value);
    check("Getting element1", 1, result, "Retrieved value: %d,%d\n", retrieved_value.c, retrieved_value.d);

    result = getElement(&map, &key2, &retrieved_value);
    check("Getting element2", 1, result, "Retrieved value: %d,%d\n", retrieved_value.c, retrieved_value.d);

    // Test removing an element and getting it
    Value removed_value;
    result = removeElement(&map, &key1, &removed_value);
    check("Removing element1", 1, result, "Element removed with key: %d,%d and value: %d,%d\n", key1.a, key1.b, removed_value.c, removed_value.d);
    
    // Test removing a non-existent element
    Key non_key = {0, 0};
    result = removeElement(&map, &non_key, &removed_value);
    check("Removing non-existent element1", 0, result, "No element removed\n");

    result = getElement(&map, &key1, &retrieved_value);
    check("Getting removed element1", 0, result, "No value retrieved\n");

    result = getElement(&map, &key2, &retrieved_value);
    check("Getting remaining element2", 1, result, "Retrieved value: %d,%d\n", retrieved_value.c, retrieved_value.d);

    // Test adding element after removal
    Key key3 = {9, 10};
    Value value3 = {11, 12};
    result = addElement(&map, &key3, &value3);
    check("Adding element3", 1, result, "Element added with key: %d,%d and value: %d,%d\n", key3.a, key3.b, value3.c, value3.d);

    result = getElement(&map, &key3, &retrieved_value);
    check("Getting added element3", 1, result, "Retrieved value: %d,%d\n", retrieved_value.c, retrieved_value.d);

    // Test cannot add element due to full map
    Key key4 = {13, 14};
    Value value4 = {15, 16};
    result = addElement(&map, &key4, &value4);
    check("Adding element4", 0, result, "No element added\n");

    // Finalize the map
    finalizeMap(&map);
    printf(ANSI_COLOR_GREEN "Map finalized\n" ANSI_COLOR_RESET);

    return 0;
}
