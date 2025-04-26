#ifndef INT_TYPE_INFO_H
#define INT_TYPE_INFO_H

#include "TypeInfo.h"

static TypeInfo* INT_TYPE_INFO = NULL;

void intAdd(const void* arg1, const void* arg2, void* result);
void intMultiply(const void* arg1, const void* arg2, void* result);
void intAbs(const void* arg, void* result);
void intPrint(const void* data);
TypeInfo* getIntTypeInfo();

#endif