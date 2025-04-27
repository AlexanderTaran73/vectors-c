#ifndef VECTOR_LIST_H
#define VECTOR_LIST_H

#include "Vector.h"

typedef struct {
    Vector** items;
    unsigned int size;
    unsigned int capacity;
} VectorList;

VectorList* createVectorList();

void pushVectorToList(VectorList* list, Vector* vector);

void removeVectorFromList(VectorList* list, unsigned int index);

#endif