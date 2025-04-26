#include "./gcMemoryManager.c"

void testMalloc(int *ptr)
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

void testCalloc(int *ptr)
{
    printf("\n------ TESTING CALLOC ------\n");
    // int *ptr = NULL;
    GC_CALLOC(ptr, sizeof(int) * 10, sizeof(int));

    printf("Address of ptr variable: %p\n", &ptr);

    printf("Value in assignedPtr:    %p\n", gcMemoryHead->assignedBlock->assignedPtr);

    printf("Allocated memory addr:   %p\n", ptr);

    printf("Allocated memory addr in assignedPtr: %p\n", *gcMemoryHead->assignedBlock->assignedPtr);

    for (int i = 0; i < 10; i++)
        printf("%d ", ptr[i]);

    printf("\n");
    int *temp = *gcMemoryHead->next->assignedBlock->assignedPtr;

    for (int i = 0; i < 10; i++)
        printf("%d ", temp[i]);

    printf("\n------ CALLOC TEST COMPLETE ------\n");
    printf("Size: %d", gcMemoryHead->sizeOfAssignedBlock);
}

int main()
{
    int *ptr, *ptr2;
    GC_MALLOC(ptr, sizeof(int) * 10);
    // testMalloc(ptr);

    for (int i = 0; i < 10; i++)
        ptr[i] = i;

    ptr2 = ptr;
    GC_TRACK(ptr2, ptr);

    printf("\n------ Malloc Ptr ------\n");
    for (int i = 0; i < 10; i++)
        printf("%p: %d\n", ptr, ptr[i]);
    printf("-----------------\n");

    printf("\n------ Malloc Ptr2 ------\n");
    for (int i = 0; i < 10; i++)
        printf("%p: %d\n", ptr2, ptr2[i]);
    printf("-----------------\n");

    printf("ptr: %p\n", &ptr);
    printf("ptr2: %p\n", &ptr2);

    GC_CALLOC(ptr, 10, sizeof(int));

    printf("\n------ Calloc Ptr ------\n");
    for (int i = 0; i < 10; i++)
        printf("%p: %d\n", ptr, ptr[i]);
    printf("-----------------\n");

    GCMemoryManager *tempGC = gcMemoryHead;
    for (; tempGC; tempGC = tempGC->next)
    {
        printf("\nMemory: %p, Total Allocations: %d\n", tempGC->memory, tempGC->sizeOfAssignedBlock);
        for (AssignedPtrNode *temp = tempGC->assignedBlock; temp; temp = temp->next)
            printf("Allocated Ptr: %p\n", (temp->assignedPtr));
    }

    return 0;
}