#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *name;
    uint8_t flag;
} Item;

typedef struct {
    Item *items;
    size_t size;
    size_t capacity;
} ItemList;

// Initialize
void initItemList(ItemList *list);

// Add a new item
void addItem(ItemList *list, const char *name, uint8_t flag);

// Free memory
void freeItemList(ItemList *list);