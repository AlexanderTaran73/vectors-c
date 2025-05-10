#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VectorList.h"
#include <math.h>

VectorList* createVectorList() {
    VectorList* list = malloc(sizeof(VectorList));
    list->size = 0;
    list->capacity = 16;
    list->items = malloc(sizeof(Vector*) * list->capacity);
    return list;
}

void pushVectorToList(VectorList* list, Vector* vector) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(Vector*) * list->capacity);
    }
    list->items[list->size++] = vector;
}

void removeVectorFromList(VectorList* list, unsigned int index) {
    if (index >= list->size) return;
    freeVector(list->items[index]);
    for (unsigned int i = index; i < list->size - 1; i++) {
        list->items[i] = list->items[i + 1];
    }
    list->size--;
}