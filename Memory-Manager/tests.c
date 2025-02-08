#include <stdio.h>
#include "memoryManager.c"

int main()
{
    // Test 1: Basic Allocation and Deallocation
    printf("Test 1: Basic Allocation and Deallocation\n");
    int *p1 = (int *)MMalloc(sizeof(int));
    *p1 = 42;
    printf("Allocated value: %d\n", *p1);
    printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(p1));

    // Test 2: Double Free (Should handle gracefully without crashing)
    printf("\nTest 2: Double Free\n");
    int *p2 = (int *)MMalloc(sizeof(int));
    *p2 = 84;
    printf("Allocated value: %d\n", *p2);
    printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(p2));
    printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(p2)); // Freeing twice should be handled (Output Should be '0' failed)

    // Test 3: Memory Leak Check
    printf("\nTest 3: Memory Leak Check\n");
    for (int i = 0; i < 10; i++)
    {
        int *p = (int *)MMalloc(sizeof(int));
        *p = i;
        printf("Allocated value: %d\n", *p);
        if (i % 2 == 0)
        {
            printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(p)); // Freeing every alternate pointer
        }
    }

    // Test 4: Zero-byte Allocation (Edge Case)
    printf("\nTest 4: Zero-byte Allocation\n");
    void *zeroPtr = MMalloc(0); // Should handle gracefully
    if (zeroPtr == NULL)
        printf("Allocated zero bytes, returned NULL\n");
    else
        printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(zeroPtr));

    // Test 5: Large Allocation
    printf("\nTest 5: Large Allocation\n");
    int *pLarge = (int *)MMalloc(1000000 * sizeof(int)); // Large allocation
    if (pLarge)
        printf("Successfully allocated a large memory block\n");
    else
        printf("Failed to allocate a large memory block\n");
    printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(pLarge));

    // Test 6: Allocate After Free
    printf("\nTest 6: Allocate After Free\n");
    int *pReAlloc = (int *)MMalloc(sizeof(int));
    *pReAlloc = 123;
    printf("Allocated value: %d\n", *pReAlloc);
    printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(pReAlloc));
    pReAlloc = (int *)MMalloc(sizeof(int));
    *pReAlloc = 456;
    printf("Allocated value after re-allocation: %d\n", *pReAlloc);
    printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(pReAlloc));

    // Test 7: Freeing a Pointer Not Allocated
    printf("\nTest 7: Freeing a Pointer Not Allocated\n");
    int *pInvalid = (int *)malloc(sizeof(int));                                   // Direct malloc, not tracked by MMalloc (Output should be '0' failed)
    printf("Status code (('0' failed) or ('1' success)): %d\n", MFree(pInvalid)); // Should print status code ('0' for failed) or ('1' for success)

    printf("FREE_ALL Status code (('0' failed) or ('1' success)): %d\n", MFreeAll());

    return 0;
}