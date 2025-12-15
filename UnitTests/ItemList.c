#include "ItemList.h"
// Initialize
void initItemList(ItemList *list) {
    list->size = 0;
    list->capacity = 4; // start small
    list->items = malloc(list->capacity * sizeof(Item));
}

// Add a new item
void addItem(ItemList *list, const char *name, uint8_t flag) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->items = realloc(list->items, list->capacity * sizeof(Item));
    }
    list->items[list->size].name = strdup(name); // allocate string
    list->items[list->size].flag = flag;
    list->size++;
}

// Free memory
void freeItemList(ItemList *list) {
    for (size_t i = 0; i < list->size; i++) {
        free(list->items[i].name);
    }
    free(list->items);
}