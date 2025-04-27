#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <stddef.h>

typedef void (*BinaryOperator)(const void* arg1, const void* arg2, void* result);

typedef void (*PrintOperator)();

typedef struct {
    size_t size;
    BinaryOperator add;
    BinaryOperator multiply;
    PrintOperator print;
} TypeInfo;

#endif