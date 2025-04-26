#include "../gcMemoryManager.c"

int main()
{
    int *ptr = NULL;
    GC_MALLOC(ptr, sizeof(int) * 10);
    for (int i = 0; i < 10; i++)
        ptr[i] = i;

    printf("Address of ptr variable: %p\n", &ptr);

    printf("Value in assignedPtr:    %p\n", gcMemoryHead->assignedBlock->assignedPtr);

    printf("Allocated memory addr:   %p\n", ptr);

    printf("Allocated memory addr in assignedPtr: %p\n", *gcMemoryHead->assignedBlock->assignedPtr);

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", ptr[i]);
    }
    printf("\n");
    int *temp = *gcMemoryHead->assignedBlock->assignedPtr;

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", temp[i]);
    }

    return 0;
}