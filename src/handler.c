#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handler.h"
#include "VectorError.h"
#include "VectorList.h"
#include "ComplexTypeInfo.h"
#include "DoubleTypeInfo.h"
#include "IntTypeInfo.h"
#include <math.h>

void printMenu() {
    printf("\nChoose operation:\n");
    printf("1 - Addition\n");
    printf("2 - Scalar Product\n");
    printf("3 - Show all vectors\n");
    printf("4 - Change a vector\n");
    printf("5 - Add a vector\n");
    printf("6 - Remove a vector\n");
    printf("7 - Exit\n");
}

void handleAddition(const VectorList* vector_list, VectorError* operation_result) {
    if (vector_list->size < 2) {
        printf("At least two vectors are required.\n");
        return;
    }

    unsigned index1, index2;
    printf("Enter indices of two vectors to add (1 to %u): ", vector_list->size);
    while (scanf("%u %u", &index1, &index2) != 2 || index1 < 1 || index2 < 1 || index1 > vector_list->size || index2 > vector_list->size) {
        printf("Invalid input. Try again: ");
        while (getchar() != '\n');
    }

    index1--; index2--;

    Vector* result = createVector(
        vector_list->items[index1]->typeInfo,
        malloc(vector_list->items[index1]->dimension * vector_list->items[index1]->typeInfo->size),
        vector_list->items[index1]->dimension,
        operation_result
    );

    if (errorsHandler(additionVectors(vector_list->items[index1], vector_list->items[index2], result))) {
        freeVector(result);
        return;
    }

    printf("Result of addition:\n");
    printVector(result);
    freeVector(result);
}

void handleScalarProduct(const VectorList* vector_list, VectorError* operation_result) {
    if (vector_list->size < 2) {
        printf("At least two vectors are required.\n");
        return;
    }

    unsigned index1, index2;
    printf("Enter indices of two vectors (1 to %u): ", vector_list->size);
    while (scanf("%u %u", &index1, &index2) != 2 ||
           index1 < 1 || index2 < 1 || index1 > vector_list->size || index2 > vector_list->size) {
        printf("Invalid input. Try again: ");
        while (getchar() != '\n');
    }

    index1--; index2--;

    void* scalar_result = malloc(vector_list->items[index1]->typeInfo->size);
    if (errorsHandler(multiplyVectors(vector_list->items[index1], vector_list->items[index2], scalar_result))) {
        free(scalar_result);
        return;
    }

    printf("Scalar product result: ");
    vector_list->items[index1]->typeInfo->print(scalar_result);
    printf("\n");

    free(scalar_result);
}

void printAllVectors(const VectorList* vector_list) {
    if (vector_list->size == 0) {
        printf("No vectors to display.\n");
        return;
    }

    printf("---- Vector List ----\n");
    for (unsigned int i = 0; i < vector_list->size; i++) {
        printf("Vector %u:\n", i + 1);
        printVector(vector_list->items[i]);
        printf("---------------------\n");
    }
}

void handleChangeVector(VectorList* vector_list) {
    if (vector_list->size == 0) {
        printf("No vectors to modify.\n");
        return;
    }

    unsigned int index;
    printf("Enter vector index (1 to %u): ", vector_list->size);
    while (scanf("%u", &index) != 1 || index < 1 || index > vector_list->size) {
        printf("Invalid input. Try again: ");
        while (getchar() != '\n');
    }
    index--;

    printf("Choose new type: 1 - Double, 2 - Complex, 3 - Integer: ");
    int new_type;
    while (scanf("%d", &new_type) != 1 || new_type < 1 || new_type > 3) {
        printf("Invalid choice. Try again: ");
        while (getchar() != '\n');
    }

    TypeInfo* new_typeInfo = NULL;
    switch (new_type) {
        case 1: new_typeInfo = getDoubleTypeInfo(); break;
        case 2: new_typeInfo = getComplexTypeInfo(); break;
        case 3: new_typeInfo = getIntTypeInfo(); break;
    }

    int newDimension;
    printf("Enter new vector dimension: ");
    while (scanf("%d", &newDimension) != 1 || newDimension <= 0) {
        printf("Invalid size. Try again: ");
        while (getchar() != '\n');
    }

    void* new_data = malloc(newDimension * new_typeInfo->size);
    if (!new_data) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    printf("Enter coordinates (%s):\n", (new_type == 2) ? "real imag pairs" : "one per element");

    for (int j = 0; j < newDimension; j++) {
        switch (new_type) {
            case 1:
                while (scanf("%lf", (double*)((char*)new_data + j * new_typeInfo->size)) != 1) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }
                break;
            case 2: {
                Complex* z = (Complex*)((char*)new_data + j * new_typeInfo->size);
                while (scanf("%lf %lf", &z->real, &z->imag) != 2) {
                    printf("Invalid complex input. Try again: ");
                    while (getchar() != '\n');
                }
                break;
            }
            case 3:
                while (scanf("%d", (int*)((char*)new_data + j * new_typeInfo->size)) != 1) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }
                break;
        }
    }

    if (errorsHandler(changeVector(new_typeInfo, vector_list->items[index], newDimension, new_data))) {
        free(new_data);
        return;
    }

    free(new_data);
    printf("Vector modified.\n");
}

void handleAddVector(VectorList* vector_list, VectorError* operation_result) {
    int data_type;
    printf("Choose data type:\n1 - Double\n2 - Complex\n3 - Integer\n");
    while (scanf("%d", &data_type) != 1 || data_type < 1 || data_type > 3) {
        printf("Invalid choice. Try again: ");
        while (getchar() != '\n');
    }

    TypeInfo* type_info = NULL;
    switch (data_type) {
        case 1: type_info = getDoubleTypeInfo(); break;
        case 2: type_info = getComplexTypeInfo(); break;
        case 3: type_info = getIntTypeInfo(); break;
    }

    int size;
    printf("Enter vector size: ");
    while (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid input. Try again: ");
        while (getchar() != '\n');
    }

    void* data = malloc(size * type_info->size);
    printf("Enter coordinates (%s):\n", (data_type == 2) ? "real imag pairs" : "one per element");

    for (int j = 0; j < size; j++) {
        switch (data_type) {
            case 1:
                while (scanf("%lf", (double*)((char*)data + j * type_info->size)) != 1) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }
                break;
            case 2: {
                Complex* z = (Complex*)((char*)data + j * type_info->size);
                while (scanf("%lf %lf", &z->real, &z->imag) != 2) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }
                break;
            }
            case 3:
                while (scanf("%d", (int*)((char*)data + j * type_info->size)) != 1) {
                    printf("Invalid input. Try again: ");
                    while (getchar() != '\n');
                }
                break;
        }
    }

    Vector* new_vector = createVector(type_info, data, size, operation_result);
    if (errorsHandler(*operation_result)) return;
    pushVectorToList(vector_list, new_vector);
    printf("Vector added successfully.\n");
}

void handleRemoveVector(VectorList* vector_list) {
    if (vector_list->size == 0) {
        printf("No vectors to remove.\n");
        return;
    }
    unsigned int index1;
    printf("Enter index of vector to remove (1 to %u): ", vector_list->size);
    while (scanf("%u", &index1) != 1 || index1 < 1 || index1 > vector_list->size) {
        printf("Invalid input. Try again: ");
        while (getchar() != '\n');
    }

    removeVectorFromList(vector_list, index1 - 1);
    printf("Vector removed.\n");
    return;
}

void cleanupAndExit(VectorList* vector_list){
    for (unsigned int i = 0; i < vector_list->size; i++) {
        freeVector(vector_list->items[i]);
    }
    free(vector_list->items);
    free(vector_list);
    printf("Exit successful\n");
}

void startInterface() {
    VectorList* vector_list = createVectorList();
    VectorError operation_result;

    while (1) {
        printMenu();

        short operation;
        while (scanf("%hd", &operation) != 1 || operation < 1 || operation > 7) {
            printf("Invalid choice. Try again: ");
            while (getchar() != '\n');
        }

        switch (operation) {
            case 1: // Addition
                handleAddition(vector_list, &operation_result);
                break;

            case 2: // Scalar Product
                handleScalarProduct(vector_list, &operation_result);
                break;

            case 3: // Show all vectors
                printAllVectors(vector_list);
                break;

            case 4: // Change vector
                handleChangeVector(vector_list);
                break;

            case 5: // Add vector
                handleAddVector(vector_list, &operation_result);
                break;

            case 6:  // Remove vector
                handleRemoveVector(vector_list);
                break;

            case 7: // Exit
                cleanupAndExit(vector_list);
                return;
        }
    }
}
