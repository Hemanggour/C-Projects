#include <stdio.h>
#include <assert.h>
#include "gcMemoryManager.c"

void printMemoryStatus(const char* testName) {
    printf("\n========== %s ==========\n", testName);
    int blockCount = 0;
    for (GCMemoryManager *tempGC = gcMemoryHead; tempGC; tempGC = tempGC->next) {
        blockCount++;
        printf("\nMemory Block #%d Info:\n", blockCount);
        printf("├── Address: %p\n", tempGC->memory);
        printf("├── Size: %zu bytes\n", tempGC->sizeOfMemory);
        printf("├── Reference Count: %zu\n", tempGC->totalAssignedBlock);
        printf("└── Tracked Pointers:\n");
        
        int ptrCount = 0;
        for (AssignedPtrNode *temp = tempGC->assignedBlock; temp; temp = temp->next) {
            ptrCount++;
            printf("    ├── [%d] Pointer Address: %p\n", ptrCount, (void*)temp->assignedPtr);
            printf("    └── [%d] Points to: %p\n", ptrCount, *(temp->assignedPtr));
        }
        printf("--------------------------------\n");
    }
    printf("Total Memory Blocks: %d\n", blockCount);
}

void test_memory_leaks() {
    printf("\nTest 1: Memory Leak Detection\n");
    
    int* ptr1 = NULL;
    GC_MALLOC(ptr1, sizeof(int));
    *ptr1 = 42;
    
    // Create a scope to test cleanup
    {
        int* ptr2 = NULL;
        GC_MALLOC(ptr2, sizeof(int));
        *ptr2 = 100;
        printMemoryStatus("Inside Scope");
    } // ptr2 goes out of scope here
    
    printMemoryStatus("After Scope");
}

void test_reference_counting() {
    printf("\nTest 2: Reference Counting\n");
    
    int* original = NULL;
    GC_MALLOC(original, sizeof(int));
    *original = 42;
    
    printMemoryStatus("After Initial Allocation");
    
    int* ref1 = original;
    GC_TRACK(ref1, original);
    
    printMemoryStatus("After First Reference");
    
    int* ref2 = original;
    GC_TRACK(ref2, original);
    
    printMemoryStatus("After Second Reference");
    
    // Untrack ref1
    GC_UNTRACK(ref1);
    
    printMemoryStatus("After Untracking First Reference");
}

// void test_reallocation() {
//     printf("\nTest 3: Reallocation Test\n");
    
//     int* array = NULL;
//     GC_MALLOC(array, sizeof(int) * 2);
//     array[0] = 1;
//     array[1] = 2;
    
//     printMemoryStatus("Initial Array");
    
//     // Attempt reallocation
//     GC_REALLOC(array, sizeof(int) * 4);
//     array[2] = 3;
//     array[3] = 4;
    
//     printMemoryStatus("After Reallocation");
// }

void test_circular_references() {
    printf("\nTest 4: Circular References\n");
    
    typedef struct Node {
        int data;
        struct Node* next;
    } Node;
    
    Node* node1 = NULL;
    Node* node2 = NULL;
    
    GC_MALLOC(node1, sizeof(Node));
    GC_MALLOC(node2, sizeof(Node));
    
    node1->data = 1;
    node2->data = 2;
    
    // Create circular reference
    node1->next = node2;
    node2->next = node1;
    
    GC_TRACK(node1->next, node2);
    GC_TRACK(node2->next, node1);
    
    printMemoryStatus("Circular Reference Created");
}

int main() {
    printf("Enhanced Garbage Collector Tests\n");
    printf("================================\n");
    
    test_memory_leaks();
    test_reference_counting();
    // test_reallocation();
    test_circular_references();
    
    printf("\nAll enhanced tests completed.\n");
    return 0;
}