#include "test_complex_type_info.h"

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "ComplexTypeInfo.h"
#include "TypeInfo.h"

#define EPSILON 0.0001

bool almostEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

void test_complexAdd() {
    TypeInfo* info = getComplexTypeInfo();
    assert(info != NULL);

    Complex c1 = { .real = 1.0, .imag = 2.0 };
    Complex c2 = { .real = 3.0, .imag = 4.0 };
    Complex result;

    info->add(&c1, &c2, &result);

    assert(almostEqual(result.real, 4.0));
    assert(almostEqual(result.imag, 6.0));
}

void test_complexMultiply() {
    TypeInfo* info = getComplexTypeInfo();
    assert(info != NULL);

    Complex c1 = { .real = 1.0, .imag = 2.0 };
    Complex c2 = { .real = 3.0, .imag = 4.0 };
    Complex result;

    info->multiply(&c1, &c2, &result);

    assert(almostEqual(result.real, -5.0));
    assert(almostEqual(result.imag, 10.0));
}

void test_getComplexTypeInfo_structure() {
    TypeInfo* info = getComplexTypeInfo();
    assert(info != NULL);
    assert(info->size == sizeof(Complex));
    assert(info->add != NULL);
    assert(info->multiply != NULL);
    assert(info->print != NULL);
}

void test_complex_type_info() {
    test_getComplexTypeInfo_structure();
    test_complexAdd();
    test_complexMultiply();
}
