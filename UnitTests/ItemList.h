#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *name;
    bool flag;
} Item;

typedef struct {
    Item *items;
    size_t size;
    size_t capacity;
} ItemList;

// Initialize
void initItemList(ItemList *list);

// Add a new item
void addItem(ItemList *list, const char *name, bool flag);

// Free memory
void freeItemList(ItemList *list);