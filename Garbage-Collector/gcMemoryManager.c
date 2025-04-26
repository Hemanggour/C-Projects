// Includes
#include <stdio.h>
#include <stdlib.h>

// Globals and MACROS
#define GC_MALLOC(ptr, size) gcMalloc((void **)&(ptr), size)
#define GC_CALLOC(ptr, size, typeSize) gcCalloc((void **)&(ptr), size, typeSize)
#define GC_TRACK(second, first) gcTrack((void **)&(second), (void **)&first)

typedef struct AssignedPtrNode
{
    void **assignedPtr;
    struct AssignedPtrNode *next;
} AssignedPtrNode;

typedef struct GCMemoryManager
{
    AssignedPtrNode *assignedBlock;
    void *memory;
    size_t sizeOfAssignedBlock;
    struct GCMemoryManager *next;
} GCMemoryManager;

GCMemoryManager *gcMemoryHead = NULL, *gcMemoryTail = NULL;

// Declarations
AssignedPtrNode *getAssignedPtrNode(void);
GCMemoryManager *getGCMemoryBlock(void);
void insertInAssignedPtrStack(GCMemoryManager *, void **);
void gcTrack(void **, void **);
void gcUnTrack(void *);
void gcRun(void);
void gcMalloc(void **, size_t);
void gcMCalloc(void *, size_t);
void gcMRealloc(void *, size_t);
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
}

GCMemoryManager *getGCMemoryBlock(void)
{
    GCMemoryManager *gcMemoryBlock = (GCMemoryManager *)malloc(sizeof(GCMemoryManager));
    if (!gcMemoryBlock)
        return NULL;

    gcMemoryBlock->assignedBlock = NULL;
    gcMemoryBlock->memory = NULL;
    gcMemoryBlock->sizeOfAssignedBlock = 0;
    gcMemoryBlock->next = NULL;
    return gcMemoryBlock;
}

void insertInAssignedPtrStack(GCMemoryManager *gcMemoryBlock, void **ptr)
{
    AssignedPtrNode *newnode = getAssignedPtrNode();
    newnode->assignedPtr = ptr;
    newnode->next = gcMemoryBlock->assignedBlock;
    gcMemoryBlock->assignedBlock = newnode;
    gcMemoryBlock->sizeOfAssignedBlock++;
}

void gcMalloc(void **ptr, size_t size)
{
    if (!size)
        return;

    GCMemoryManager *gcMemoryBlock = getGCMemoryBlock();
    if (!gcMemoryBlock)
        return;

    *ptr = malloc(size);
    if (!*ptr)
        return;

    gcMemoryBlock->memory = *ptr;
    if (!gcMemoryHead)
        gcMemoryHead = gcMemoryBlock;
    else
        gcMemoryTail->next = gcMemoryBlock;
    gcMemoryTail = gcMemoryBlock;
    insertInAssignedPtrStack(gcMemoryBlock, ptr);
}

void gcCalloc(void **ptr, size_t size, size_t typeSize)
{
    if (!size)
        return;

    GCMemoryManager *gcMemoryBlock = getGCMemoryBlock();
    if (!gcMemoryBlock)
        return;

    *ptr = calloc(size, typeSize);
    if (!*ptr)
        return;

    gcMemoryBlock->memory = *ptr;
    if (!gcMemoryHead)
        gcMemoryHead = gcMemoryTail = gcMemoryBlock;
    else
        gcMemoryTail->next = gcMemoryBlock;
    gcMemoryTail = gcMemoryBlock;
    insertInAssignedPtrStack(gcMemoryBlock, ptr);
}

void gcTrack(void **second, void **first)
{
    GCMemoryManager *tempGC = gcMemoryHead;
    AssignedPtrNode *temp = gcMemoryHead->assignedBlock;
    for (; tempGC->next; tempGC = tempGC->next)
    {
        temp = tempGC->assignedBlock;
        while ((first != temp->assignedPtr) && (temp))
            temp = temp->next;
    }
    if (first == temp->assignedPtr)
        insertInAssignedPtrStack(tempGC, second);
}