#ifndef VECTOR_ERROR_H
#define VECTOR_ERROR_H

#include <stdio.h>

typedef enum {
    VECTOR_OK = 0,                          // Нет ошибки
    VECTOR_ERR_MEMORY_ALLOCATION = 1,        // Ошибка выделения памяти
    VECTOR_ERR_NOT_INITIALIZED = 2,          // Вектор не инициализирован
    VECTOR_ERR_OPERATION_NOT_SUPPORTED = 3,  // Операция не поддерживается
    VECTOR_ERR_TYPE_MISMATCH = 4,             // Несовместимые типы векторов
    VECTOR_ERR_DIMENSION_MISMATCH = 5         // Векторы разной размерности
} VectorError;

typedef struct {
    VectorError code;
    const char* message;
} VectorErrorEntry;

static const VectorErrorEntry vectorErrorTable[] = {
    { VECTOR_ERR_MEMORY_ALLOCATION,         "ERROR: memory allocation failed." },
    { VECTOR_ERR_NOT_INITIALIZED,           "ERROR: vector not initialized." },
    { VECTOR_ERR_OPERATION_NOT_SUPPORTED,   "ERROR: operation is not supported." },
    { VECTOR_ERR_TYPE_MISMATCH,             "ERROR: incompatible vector types." },
    { VECTOR_ERR_DIMENSION_MISMATCH,        "ERROR: different dimension of vectors." }
};

static const char* getVectorErrorMessage(VectorError code) {
    size_t count = sizeof(vectorErrorTable) / sizeof(vectorErrorTable[0]);
    for (size_t i = 0; i < count; ++i) {
        if (vectorErrorTable[i].code == code) {
            return vectorErrorTable[i].message;
        }
    }
    return "ERROR: unknown error.";
}

static int errorsHandler(VectorError operationResult) {
    if (operationResult != VECTOR_OK) {
        fprintf(stderr, "%s\n", getVectorErrorMessage(operationResult));
        return 1;
    }
    return 0;
}

#endif