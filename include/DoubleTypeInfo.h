#ifndef DOUBLE_TYPE_INFO_H
#define DOUBLE_TYPE_INFO_H

#include "TypeInfo.h"

static TypeInfo* DOUBLE_TYPE_INFO = NULL;

void doubleAdd(const void* arg1, const void* arg2, void* result);

void doubleMultiply(const void* arg1, const void* arg2, void* result);

void doublePrint(const void* data);

TypeInfo* getDoubleTypeInfo();

#endif