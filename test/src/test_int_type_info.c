#include "test_int_type_info.h"

#include <assert.h>
#include "IntTypeInfo.h"
#include "TypeInfo.h"

static void test_intAdd() {
    TypeInfo* info = getIntTypeInfo();
    int a = 5;
    int b = 7;
    int result = 0;
    info->add(&a, &b, &result);
    assert(result == 12);
}

static void test_intMultiply() {
    TypeInfo* info = getIntTypeInfo();
    int a = 3;
    int b = 4;
    int result = 0;
    info->multiply(&a, &b, &result);
    assert(result == 12);
}

static void test_structure() {
    TypeInfo* info = getIntTypeInfo();
    assert(info);
    assert(info->size == sizeof(int));
    assert(info->add);
    assert(info->multiply);
    assert(info->print);
}

void run_int_type_info_tests() {
    test_structure();
    test_int_add();
    test_int_multiply();
}
