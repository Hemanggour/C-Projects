#include <stdio.h>
#include "gcMemoryManager.c"

void printMemoryStatus(const char* testName) {
    printf("\n========== %s ==========\n", testName);
    for (GCMemoryManager *tempGC = gcMemoryHead; tempGC; tempGC = tempGC->next) {
        printf("\nMemory Block Info:\n");
        printf("|-- Address: %p\n", tempGC->memory);
        printf("|-- Size: %zu bytes\n", tempGC->sizeOfMemory);
        printf("|-- Reference Count: %zu\n", tempGC->totalAssignedBlock);
        printf("|-- Tracked Pointers:\n");
        
        for (AssignedPtrNode *temp = tempGC->assignedBlock; temp; temp = temp->next) {
            printf("    |-- Pointer Address: %p\n", (void*)temp->assignedPtr);
            printf("    |-- Points to: %p\n", *(temp->assignedPtr));
        }
        printf("--------------------------------\n");
    }
}

void test_simple_allocation(void) {
    printf("\nTest 1: Simple Allocation\n");
    
    int* number = NULL;
    GC_MALLOC(number, sizeof(int));
    *number = 42;
    
    printMemoryStatus("Simple Int Allocation");
}

void test_array_allocation(void) {
    printf("\nTest 2: Array Allocation\n");
    
    int* array = NULL;
    GC_CALLOC(array, 5, sizeof(int));
    
    for(int i = 0; i < 5; i++) {
        array[i] = i * 10;
    }
    
    printMemoryStatus("Array Allocation");
}

void test_pointer_tracking(void) {
    printf("\nTest 3: Pointer Tracking\n");
    
    int* original = NULL;
    GC_MALLOC(original, sizeof(int));
    *original = 100;
    
    int* tracked1 = NULL;
    int* tracked2 = NULL;
    
    tracked1 = original;
    tracked2 = original;
    
    GC_TRACK(tracked1, original);
    GC_TRACK(tracked2, original);
    
    printMemoryStatus("Multiple Pointer Tracking");
}

void test_complex_structure(void) {
    printf("\nTest 4: Complex Structure\n");
    
    typedef struct Node {
        int data;
        struct Node* next;
    } Node;
    
    Node* head = NULL;
    GC_MALLOC(head, sizeof(Node));
    head->data = 1;
    
    Node* second = NULL;
    GC_MALLOC(second, sizeof(Node));
    second->data = 2;
    
    head->next = second;
    GC_TRACK(head->next, second);
    
    printMemoryStatus("Linked List Structure");
}

int main() {
    printf("Starting Garbage Collector Tests\n");
    printf("================================\n");
    
    test_simple_allocation();
    test_array_allocation();
    test_pointer_tracking();
    test_complex_structure();
    
    printf("\nAll tests completed.\n");
    return 0;
}