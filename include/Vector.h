#ifndef VECTOR_H
#define VECTOR_H

#include "TypeInfo.h"
#include "VectorError.h"

typedef struct {
    void **data;
    TypeInfo* typeInfo;   
    int dimension;
} Vector;


Vector* createVector(TypeInfo* typeInfo, void *data, int dimension, VectorError* operationResult);

void freeVector(Vector* v);

VectorError additionVectors(const Vector* v1, const Vector* v2, Vector* result);

VectorError multiplyVectors(const Vector* v1, const Vector* v2, void* result);

VectorError printVector(const Vector* v);

VectorError changeVector(TypeInfo* newTypeInfo, Vector *v, int newDimension, void *newData);

#endif