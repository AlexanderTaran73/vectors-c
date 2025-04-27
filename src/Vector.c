#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector* createVector(TypeInfo* typeInfo, void *data, int dimension, VectorError* operationResult){
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    if (vector == NULL) {
        *operationResult = VECTOR_ERR_MEMORY_ALLOCATION;
        return NULL;
    }

    vector->typeInfo = typeInfo;
    vector->dimension = dimension;
    vector->data = malloc(typeInfo->size * vector->dimension);
    if (vector->data == NULL) {
        *operationResult = VECTOR_ERR_MEMORY_ALLOCATION;
        free(vector);
        return NULL;
    }
    
    if (data != NULL) {
        memcpy(vector->data, data, typeInfo->size * vector->dimension);
    }

    *operationResult = VECTOR_OK;
    return vector;
}

void freeVector(Vector* v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

VectorError additionVectors(const Vector* v1, const Vector* v2, Vector* result) {
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_ERR_NOT_INITIALIZED;
    if (v1->typeInfo != v2->typeInfo || v1->typeInfo != result->typeInfo) return VECTOR_ERR_TYPE_MISMATCH;
    if (v1->dimension != v2->dimension) return VECTOR_ERR_DIMENSION_MISMATCH;
    if (v1->typeInfo->add == NULL) return VECTOR_ERR_OPERATION_NOT_SUPPORTED;

    for (int i = 0; i < v1->dimension; i++) {
        v1->typeInfo->add(
            (char*)v1->data + i * v1->typeInfo->size,
            (char*)v2->data + i * v1->typeInfo->size,
            (char*)result->data + i * v1->typeInfo->size
        );
    }

    return VECTOR_OK;
}

VectorError multiplyVectors(const Vector* v1, const Vector* v2, void* result) {
    if (v1 == NULL || v2 == NULL || result == NULL) return VECTOR_ERR_NOT_INITIALIZED;
    if (v1->typeInfo != v2->typeInfo) return VECTOR_ERR_TYPE_MISMATCH;
    if (v1->dimension != v2->dimension) return VECTOR_ERR_DIMENSION_MISMATCH;
    if (v1->typeInfo->multiply == NULL) return VECTOR_ERR_OPERATION_NOT_SUPPORTED;
    
    memset(result, 0, v1->typeInfo->size);
    for(int i=0; i < v1->dimension; i++){
        void* arg1 = (char*)v1->data + i * v1->typeInfo->size;
        void* arg2 = (char*)v2->data + i * v2->typeInfo->size;
        void* temp_result = malloc(v1->typeInfo->size);
        if (temp_result == NULL) return VECTOR_ERR_MEMORY_ALLOCATION; 
        v1->typeInfo->multiply(arg1, arg2, temp_result);  
        v1->typeInfo->add(result, temp_result, result);
        free(temp_result); 
    }

    return VECTOR_OK;
}

VectorError printVector(const Vector* vector) {
    if (vector == NULL) return VECTOR_ERR_NOT_INITIALIZED;
    if (vector->typeInfo->print == NULL) return VECTOR_ERR_OPERATION_NOT_SUPPORTED;

    printf("Vector: (");
    for (int i = 0; i < vector->dimension; i++) {
        vector->typeInfo->print((char*)vector->data + i * vector->typeInfo->size);
        if (i < vector->dimension - 1) {
            printf(", ");
        }
    }
    printf(")");

    return VECTOR_OK;
}

VectorError changeVector(TypeInfo* newTypeInfo, Vector *v, int newDimension, void *newData){
    if (v == NULL || newData == NULL) return VECTOR_ERR_NOT_INITIALIZED;

    free(v->data);
    v->typeInfo = newTypeInfo;
    v->dimension = newDimension;
    v->data =  malloc(newTypeInfo->size * v->dimension);

    if (v->data == NULL) return VECTOR_ERR_NOT_INITIALIZED;

    memcpy(v->data, newData, newDimension * newTypeInfo->size);
    
    return VECTOR_OK;
}