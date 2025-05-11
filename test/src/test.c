#include <stdio.h>
#include "test_complex_type_info.h"
#include "test_double_type_info.h"
#include "test_int_type_info.h"
#include "test_vector.h"

int main() {
    run_complex_type_info_tests();
    printf("ComplexTypeInfo tests passed.\n");

    run_double_type_info_tests();
    printf("DoubleTypeInfo tests passed.\n");

    run_int_type_info_tests();
    printf("IntTypeInfo tests passed.\n");

    run_vector_tests();
    printf("Vector tests passed.\n");

    printf("All tests completed successfully.\n");
    return 0;
}
