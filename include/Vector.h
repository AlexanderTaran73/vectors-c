#ifndef VECTOR_H
#define VECTOR_H

#include "TypeInfo.h"
#include "VectorErrors.h"

typedef struct {
    void **data;
    TypeInfo* typeInfo;   
    int dimension;
} Vector;


Vector* createVector(TypeInfo* typeInfo, void *data, int dimension, VectorErrors* operationResult);
void freeVector(Vector* v);
VectorErrors addVectors(const Vector* v1, const Vector* v2, Vector* result);
VectorErrors multiplyVectors(const Vector* v1, const Vector* v2, void* result);
VectorErrors printVector(const Vector* v);
VectorErrors absVector(const Vector* v, void* result);
VectorErrors rewriteVector(TypeInfo* new_typeInfo, Vector *v, int new_dimension, void *new_data);

#endif