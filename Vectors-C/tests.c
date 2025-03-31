#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "vector.c"

void testIntVector()
{
    printf("Testing Integer Vector...\n");

    Vector *intVec = vectorInit(sizeof(int));
    assert(intVec != NULL && "Failed to initialize Integer Vector");
    assert(intVec->size == 0 && "Initial size should be 0");
    assert(intVec->capacity == INCREAMENT && "Initial capacity incorrect");

    // Test push_back
    for (int i = 0; i < 5; i++)
    {
        vectorPushBack(intVec, &i);
    }
    assert(intVec->size == 5 && "Size should be 5 after pushing 5 elements");

    // Test get and verify values
    int *data = (int *)vectorGet(intVec);
    for (int i = 0; i < 5; i++)
    {
        if (data[i] != i)
        {
            printf("Integer mismatch at index %d: expected %d, got %d\n", i, i, data[i]);
            assert(0);
        }
    }

    // Test pop_back
    vectorPopBack(intVec);
    assert(intVec->size == 4 && "Size should be 4 after pop");

    printf("Integer Vector tests passed!\n");
    vectorFree(intVec); // Changed from free to vectorFree
}

void testCharVector()
{
    printf("Testing Character Vector...\n");

    Vector *charVec = vectorInit(sizeof(char));
    assert(charVec != NULL && "Failed to initialize Character Vector");

    // Test push_back with characters
    char chars[] = {'H', 'E', 'L', 'L', 'O', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
    size_t charsLength = sizeof(chars) / sizeof(chars[0]);

    // Print memory addresses and values before push
    printf("Vector data address: %p\n", charVec->data);
    printf("Initial capacity: %zu, element size: %zu\n",
           charVec->capacity, charVec->elementSize);

    for (size_t i = 0; i < charsLength; i++)
    {
        vectorPushBack(charVec, &chars[i]);
        // Debug print after each push
        char *current = (char *)charVec->data;
        printf("Pushed '%c' (ASCII: %d) at index %zu, stored value: '%c' (ASCII: %d)\n",
               chars[i], chars[i], i, current[i], current[i]);
    }

    assert(charVec->size == charsLength &&
           "Size should match number of pushed characters");

    // Test get and verify values with detailed debugging
    char *data = (char *)vectorGet(charVec);
    printf("Retrieved data address: %p\n", data);

    for (size_t i = 0; i < charVec->size; i++)
    {
        printf("Index %zu - Expected: '%c' (ASCII: %d), Got: '%c' (ASCII: %d)\n",
               i, chars[i], chars[i], data[i], data[i]);

        if (data[i] != chars[i])
        {
            printf("Character mismatch at index %zu: expected '%c' (ASCII: %d), got '%c' (ASCII: %d)\n",
                   i, chars[i], chars[i], data[i], data[i]);
            assert(0 && "Character mismatch");
        }
    }

    printf("Character Vector tests passed!\n");
    vectorFree(charVec); // Changed from free to vectorFree
}

void testDoubleVector()
{
    printf("Testing Double Vector...\n");

    Vector *doubleVec = vectorInit(sizeof(double));
    assert(doubleVec != NULL);

    // Test push_back with doubles
    double values[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    for (int i = 0; i < 5; i++)
    {
        vectorPushBack(doubleVec, &values[i]);
    }
    assert(doubleVec->size == 5);

    // Test get and verify values
    double *data = (double *)vectorGet(doubleVec);
    for (int i = 0; i < 5; i++)
    {
        assert(data[i] == values[i]);
    }

    printf("Double Vector tests passed!\n");
    vectorFree(doubleVec); // Changed from free to vectorFree
}

typedef struct
{
    int id;
    char name[20];
} Person;

void testStructVector()
{
    printf("Testing Struct Vector...\n");

    Vector *structVec = vectorInit(sizeof(Person));
    assert(structVec != NULL);

    // Test push_back with structs
    Person people[] = {
        {1, "Alice"},
        {2, "Bob"},
        {3, "Charlie"}};

    for (int i = 0; i < 3; i++)
    {
        vectorPushBack(structVec, &people[i]);
    }
    assert(structVec->size == 3);

    // Test get and verify values
    Person *data = (Person *)vectorGet(structVec);
    for (int i = 0; i < 3; i++)
    {
        assert(data[i].id == people[i].id);
        assert(strcmp(data[i].name, people[i].name) == 0);
    }

    printf("Struct Vector tests passed!\n");
    vectorFree(structVec); // Changed from free to vectorFree
}

int main()
{
    printf("Starting Vector tests...\n\n");

    testIntVector();
    testCharVector();
    testDoubleVector();
    testStructVector();

    printf("\nAll tests passed successfully!\n");

    return 0;
}