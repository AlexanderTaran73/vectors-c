#include "test_double_type_info.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "DoubleTypeInfo.h"
#include "TypeInfo.h"

#define EPSILON 0.0001

static bool almostEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

static void test_doubleAdd() {
    TypeInfo* info = getDoubleTypeInfo();
    double a = 1.5, b = 2.3, result = 0;
    info->add(&a, &b, &result);
    assert(almostEqual(result, 3.8));
}

static void test_doubleMultiply() {
    TypeInfo* info = getDoubleTypeInfo();
    double a = 2.0, b = 3.5, result = 0;
    info->multiply(&a, &b, &result);
    assert(almostEqual(result, 7.0));
}

static void test_structure() {
    TypeInfo* info = getDoubleTypeInfo();
    assert(info);
    assert(info->size == sizeof(double));
    assert(info->add);
    assert(info->multiply);
    assert(info->print);
}

void run_double_type_info_tests() {
    test_structure();
    test_doubleAdd();
    test_doubleMultiply();
}
