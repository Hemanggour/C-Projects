#include "./gcMemoryManager.c"

int *ptr, *ptr2, *ptr3, *ptr4;

void testMalloc(void)
{
    printf("\n------ TESTING MALLOC ------\n");
    GC_MALLOC(ptr, sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        ptr[i] = i;

    printf("Address of ptr variable: %p\n", &ptr);

    printf("Value in assignedPtr:    %p\n", gcMemoryHead->assignedBlock->assignedPtr);

    printf("Allocated memory addr:   %p\n", ptr);

    printf("Allocated memory addr in assignedPtr: %p\n", *gcMemoryHead->assignedBlock->assignedPtr);

    for (int i = 0; i < 10; i++)
        printf("%d ", ptr[i]);

    printf("\n");
    int *temp = *gcMemoryHead->assignedBlock->assignedPtr;

    for (int i = 0; i < 10; i++)
        printf("%d ", temp[i]);

    printf("\n------ MALLOC TEST COMPLETE ------\n");
}

void testCalloc(void)
{
    printf("\n------ TESTING CALLOC ------\n");
    GC_CALLOC(ptr2, sizeof(int) * 10, sizeof(int));

    printf("Address of ptr2 variable: %p\n", &ptr2);

    printf("Value in assignedPtr:    %p\n", gcMemoryHead->assignedBlock->assignedPtr);

    printf("Allocated memory addr:   %p\n", ptr2);

    printf("Allocated memory addr in assignedPtr: %p\n", *gcMemoryHead->assignedBlock->assignedPtr);

    for (int i = 0; i < 10; i++)
        printf("%d ", ptr2[i]);

    printf("\n");
    printf("------ LEAKS CHECK ------\n");
    GCMemoryManager *leaks = GC_GET_LEAKS(ptr2);
    printf("Memory: %p\nMemory Size: %d\n", leaks->memory, leaks->sizeOfMemory);
    printf("Total Refrence Pointers: %d\n", leaks->totalAssignedBlock);
    for (AssignedPtrNode *temp = leaks->assignedBlock; temp; temp = temp->next)
        printf("%p ", temp->assignedPtr);

    printf("\n");
    printf("-------------------------\n");

    printf("\n------ CALLOC TEST COMPLETE ------\n");
}

void unitTest(void)
{
    printf("\n------ UNIT TESTING ------\n");
    // int *ptr = NULL, *ptr2 = NULL;
    GC_MALLOC(ptr3, sizeof(int) * 10);

    for (int i = 0; i < 10; i++)
        ptr3[i] = i;

    ptr4 = ptr3;
    GC_TRACK(ptr4, ptr3);

    printf("\n------ Malloc Ptr ------\n");
    for (int i = 0; i < 10; i++)
        printf("%p: %d\n", ptr3, ptr3[i]);
    printf("-----------------\n");

    printf("\n------ Malloc Ptr2 ------\n");
    for (int i = 0; i < 10; i++)
        printf("%p: %d\n", ptr4, ptr4[i]);
    printf("-----------------\n");

    printf("ptr3: %p\n", &ptr3);
    printf("ptr4: %p\n", &ptr4);

    GC_CALLOC(ptr3, 10, sizeof(int));

    printf("\n------ Calloc Ptr ------\n");
    for (int i = 0; i < 10; i++)
        printf("%p: %d\n", ptr3, ptr3[i]);
    printf("-----------------\n");
    printf("\n------ UNIT TEST COMPLETE ------\n");
}

int main()
{
    testMalloc();
    for (GCMemoryManager *tempGC = gcMemoryHead; tempGC; tempGC = tempGC->next)
    {
        printf("\nMemory: %p, Total Allocations: %d\n", tempGC->memory, tempGC->totalAssignedBlock);
        for (AssignedPtrNode *temp = tempGC->assignedBlock; temp; temp = temp->next)
            printf("Allocated Ptr: %p\n", (temp->assignedPtr));
    }

    testCalloc();
    for (GCMemoryManager *tempGC = gcMemoryHead; tempGC; tempGC = tempGC->next)
    {
        printf("\nMemory: %p, Total Allocations: %d\n", tempGC->memory, tempGC->totalAssignedBlock);
        for (AssignedPtrNode *temp = tempGC->assignedBlock; temp; temp = temp->next)
            printf("Allocated Ptr: %p\n", (temp->assignedPtr));
    }

    unitTest();
    printf("---------- CHECK FOR LEAKS ----------\n");
    for (GCMemoryManager *tempGC = gcMemoryHead; tempGC; tempGC = tempGC->next)
    {
        printf("\nMemory Addr: %p\nMemory Size: %d\nTotal Refrence Pointers : %d\n", tempGC->memory, tempGC->sizeOfMemory, tempGC->totalAssignedBlock);
        printf("Pointers:\n");
        for (AssignedPtrNode *temp = tempGC->assignedBlock; temp; temp = temp->next)
            printf("Allocated Ptr: %p\n", (temp->assignedPtr));
        printf("--------------------\n");
    }

    printf("--------------\n");
    printf("ptr: %p\n", &ptr);
    printf("ptr2: %p\n", &ptr2);
    printf("ptr3: %p\n", &ptr3);
    printf("ptr4: %p\n", &ptr4);

    return 0;
}