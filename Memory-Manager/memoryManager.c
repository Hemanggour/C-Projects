#include <stdlib.h>

typedef struct MemoryBlock
{
    size_t size;
    void *memory;
    struct MemoryBlock *next;
} MemoryBlock;
MemoryBlock *MemoryBlockHead = NULL, *MemoryBlockTail = NULL;

MemoryBlock *getMemoryBlock()
{
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
    if (!block)
        return NULL;
    block->next = NULL;
    return block;
}

void *MMalloc(size_t size)
{
    if (!size)
        return NULL;
    void *mallocMemory = malloc(size);
    if (!mallocMemory)
        return NULL;
    MemoryBlock *block = getMemoryBlock();
    block->size = size;
    block->memory = mallocMemory;
    if (!MemoryBlockHead)
        MemoryBlockHead = MemoryBlockTail = block;
    else
    {
        MemoryBlockTail->next = block;
        MemoryBlockTail = block;
    }
    return mallocMemory;
}

int MFree(void *ptr)
{
    if (!ptr)
        return 0;

    MemoryBlock *temp = MemoryBlockHead, *prev = NULL;
    while (temp)
    {
        if (temp->memory == ptr)
        {
            if (prev)
                prev->next = temp->next;
            else
                MemoryBlockHead = temp->next;
            if (temp == MemoryBlockTail)
                MemoryBlockTail = prev;

            free(temp->memory);
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

int MFreeAll()
{
    MemoryBlock *temp = MemoryBlockHead;
    while (MemoryBlockHead)
    {
        MemoryBlockHead = temp->next;
        free(temp->memory);
        free(temp);
        temp = MemoryBlockHead;
    }
    return ((!MemoryBlockHead) ? 1 : 0);
}