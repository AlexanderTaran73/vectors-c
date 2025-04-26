#ifndef COMPLEX_TYPE_INFO_H
#define COMPLEX_TYPE_INFO_H

#include "TypeInfo.h"

typedef struct {
    double real;
    double imag;
} Complex;

static TypeInfo* COMPLEX_TYPE_INFO = NULL;

void complexAdd(const void* arg1, const void* arg2, void* result);
void complexMultiply(const void* arg1, const void* arg2, void* result);
void complexAbs(const void* arg, void* result);
void complexPrint(const void* data);
TypeInfo* getComplexTypeInfo();

#endif