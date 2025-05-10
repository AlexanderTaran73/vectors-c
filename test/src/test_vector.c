#include "test_vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "DoubleTypeInfo.h"
#include "IntTypeInfo.h"
#include "VectorError.h"

static void test_vector_creation_and_free() {
    VectorError err;
    double data[] = {1.0, 2.0, 3.0};
    Vector* v = createVector(getDoubleTypeInfo(), data, 3, &err);
    assert(err == VECTOR_OK);
    assert(v != NULL);
    assert(v->dimension == 3);
    assert(memcmp(v->data, data, 3 * sizeof(double)) == 0);
    freeVector(v);
}

static void test_vector_addition() {
    VectorError err;
    double data1[] = {1.0, 2.0, 3.0};
    double data2[] = {4.0, 5.0, 6.0};
    double expected[] = {5.0, 7.0, 9.0};
    
    TypeInfo* type = getDoubleTypeInfo();

    Vector* v1 = createVector(type, data1, 3, &err);
    Vector* v2 = createVector(type, data2, 3, &err);
    Vector* res = createVector(type, NULL, 3, &err);

    err = additionVectors(v1, v2, res);
    assert(err == VECTOR_OK);
    assert(memcmp(res->data, expected, 3 * sizeof(double)) == 0);

    freeVector(v1);
    freeVector(v2);
    freeVector(res);
}

static void test_vector_scalar_product() {
    VectorError err;
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int result = 0;

    TypeInfo* type = getIntTypeInfo();
    Vector* v1 = createVector(type, data1, 3, &err);
    Vector* v2 = createVector(type, data2, 3, &err);

    err = multiplyVectors(v1, v2, &result);
    assert(err == VECTOR_OK);
    assert(result == 32);  // 1*4 + 2*5 + 3*6 = 32

    freeVector(v1);
    freeVector(v2);
}

static void test_change_vector() {
    VectorError err;
    int data[] = {1, 2, 3};
    Vector* v = createVector(getIntTypeInfo(), data, 3, &err);
    assert(err == VECTOR_OK);

    double new_data[] = {10.0, 20.0};
    err = changeVector(getDoubleTypeInfo(), v, 2, new_data);
    assert(err == VECTOR_OK);
    assert(v->dimension == 2);
    assert(memcmp(v->data, new_data, 2 * sizeof(double)) == 0);

    freeVector(v);
}

void run_vector_tests() {
    test_vector_creation_and_free();
    test_vector_addition();
    test_vector_scalar_product();
    test_change_vector();
}
