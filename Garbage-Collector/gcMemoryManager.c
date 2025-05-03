// Includes
#include <stdio.h>
#include <stdlib.h>

// Globals and MACROS
#define GC_MALLOC(ptr, size) gcMalloc((void **)&(ptr), size)
#define GC_CALLOC(ptr, size, typeSize) gcCalloc((void **)&(ptr), size, typeSize)
#define GC_TRACK(second, first) gcTrack((void **)&(second), (void **)&first)
#define GC_UNTRACK(ptr) gcUntrack((void **)&(ptr))
#define GC_GET_LEAKS(ptr) getAddrLeaks((void **)&(ptr))
#define GC_REALLOC(ptr, size) gcRealloc((void **)&(ptr), size)

typedef struct AssignedPtrNode
{
    void **assignedPtr;
    struct AssignedPtrNode *next;
} AssignedPtrNode;

typedef struct GCMemoryManager
{
    AssignedPtrNode *assignedBlock;
    void *memory;
    size_t sizeOfMemory;
    size_t totalAssignedBlock;
    struct GCMemoryManager *next;
} GCMemoryManager;

GCMemoryManager *gcMemoryHead = NULL, *gcMemoryTail = NULL;

typedef struct Leaks
{
    size_t addrSize;
    size_t leaksCount;
    void *ptr;
} Leaks;

// Declarations
AssignedPtrNode *getAssignedPtrNode(void);
GCMemoryManager *getGCMemoryBlock(void);
void insertInAssignedPtrStack(GCMemoryManager *, void **);
void gcTrack(void **, void **);
void gcUntrack(void **);
void gcRun(void);
void gcMalloc(void **, size_t);
void gcMCalloc(void *, size_t);
void gcRealloc(void *, size_t);
void gcMFree(void *);
void gcMFreeAll(void);

// Function Definitions
AssignedPtrNode *getAssignedPtrNode(void)
{
    AssignedPtrNode *assignedPtrNode = (AssignedPtrNode *)malloc(sizeof(AssignedPtrNode));

    if (!assignedPtrNode)
        return NULL;

    assignedPtrNode->assignedPtr = NULL;
    assignedPtrNode->next = NULL;

    return assignedPtrNode;
}

GCMemoryManager *getGCMemoryBlock(void)
{
    GCMemoryManager *gcMemoryBlock = (GCMemoryManager *)malloc(sizeof(GCMemoryManager));

    if (!gcMemoryBlock)
        return NULL;

    gcMemoryBlock->assignedBlock = NULL;
    gcMemoryBlock->memory = NULL;
    gcMemoryBlock->totalAssignedBlock = 0;
    gcMemoryBlock->next = NULL;

    return gcMemoryBlock;
}

void insertInAssignedPtrStack(GCMemoryManager *gcMemoryBlock, void **ptr)
{
    if (!gcMemoryBlock || !ptr)
        return;

    AssignedPtrNode *newnode = getAssignedPtrNode();

    if (!newnode)
        return;

    newnode->assignedPtr = ptr;
    newnode->next = gcMemoryBlock->assignedBlock;
    gcMemoryBlock->assignedBlock = newnode;
    gcMemoryBlock->totalAssignedBlock++;
}

void gcMalloc(void **ptr, size_t size)
{
    if (!ptr || !size)
        return;

    GCMemoryManager *gcMemoryBlock = getGCMemoryBlock();

    if (!gcMemoryBlock)
        return;

    *ptr = malloc(size);

    if (!*ptr)
    {
        free(gcMemoryBlock);
        return;
    }

    gcMemoryBlock->memory = *ptr;
    gcMemoryBlock->sizeOfMemory = size;

    if (!gcMemoryHead)
        gcMemoryHead = gcMemoryTail = gcMemoryBlock;
    else
        gcMemoryTail->next = gcMemoryBlock;

    gcMemoryTail = gcMemoryBlock;

    insertInAssignedPtrStack(gcMemoryBlock, ptr);
}

void gcCalloc(void **ptr, size_t size, size_t typeSize)
{
    if (!ptr || !size || !typeSize)
        return;

    GCMemoryManager *gcMemoryBlock = getGCMemoryBlock();
    if (!gcMemoryBlock)
        return;

    *ptr = calloc(size, typeSize);

    if (!*ptr)
    {
        free(gcMemoryBlock);
        return;
    }

    gcMemoryBlock->memory = *ptr;
    gcMemoryBlock->sizeOfMemory = size * typeSize;

    if (!gcMemoryHead)
        gcMemoryHead = gcMemoryTail = gcMemoryBlock;
    else
        gcMemoryTail->next = gcMemoryBlock;

    gcMemoryTail = gcMemoryBlock;

    insertInAssignedPtrStack(gcMemoryBlock, ptr);
}

void gcTrack(void **second, void **first)
{
    if (!second || !first || !gcMemoryHead || !*first)
        return;

    GCMemoryManager *tempGC = gcMemoryHead;

    while (tempGC)
    {
        if (*first == tempGC->memory)
        {
            *second = *first;
            insertInAssignedPtrStack(tempGC, second);
            return;
        }

        tempGC = tempGC->next;
    }
}

GCMemoryManager *getAddrLeaks(void **addr)
{
    if (!addr || !gcMemoryHead || !*addr)
        return NULL;

    GCMemoryManager *gcMemoryBlock = gcMemoryHead;

    while (gcMemoryBlock)
    {
        if (*addr == gcMemoryBlock->memory)
            return gcMemoryBlock;
        gcMemoryBlock = gcMemoryBlock->next;
    }

    return NULL;
}

void gcUntrack(void **addr)
{
    if (!addr || !gcMemoryHead)
        return;

    GCMemoryManager *gcMemoryBlock = gcMemoryHead;
    GCMemoryManager *prevBlock = NULL;

    while (gcMemoryBlock && (*addr != gcMemoryBlock->memory))
    {
        prevBlock = gcMemoryBlock;
        gcMemoryBlock = gcMemoryBlock->next;
    }

    if (!gcMemoryBlock)
        return;

    AssignedPtrNode *currentPtr = gcMemoryBlock->assignedBlock;
    AssignedPtrNode *prevPtr = NULL;

    while (currentPtr && currentPtr->assignedPtr != addr)
    {
        prevPtr = currentPtr;
        currentPtr = currentPtr->next;
    }

    if (!currentPtr)
        return;

    if (prevPtr)
        prevPtr->next = currentPtr->next;
    else
        gcMemoryBlock->assignedBlock = currentPtr->next;

    gcMemoryBlock->totalAssignedBlock--;

    if (gcMemoryBlock->totalAssignedBlock == 0)
    {
        if (prevBlock)
            prevBlock->next = gcMemoryBlock->next;
        else
            gcMemoryHead = gcMemoryBlock->next;

        if (gcMemoryTail == gcMemoryBlock)
            gcMemoryTail = prevBlock;

        free(gcMemoryBlock->memory);
        free(gcMemoryBlock);
    }

    free(currentPtr);
}

void gcMFreeAll(void)
{
    while (gcMemoryHead)
    {
        GCMemoryManager *current = gcMemoryHead;
        gcMemoryHead = gcMemoryHead->next;

        while (current->assignedBlock)
        {
            AssignedPtrNode *temp = current->assignedBlock;
            current->assignedBlock = current->assignedBlock->next;
            free(temp);
        }

        free(current->memory);
        free(current);
    }
    gcMemoryTail = NULL;
}