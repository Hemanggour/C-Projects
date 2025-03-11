#include <stdlib.h>
#include <string.h>

#define INCREAMENT 2

typedef struct
{
    void *data;
    size_t elementSize;
    size_t size;
    size_t capacity;
} Vector;

Vector *vectorInit(size_t);
Vector *vectorResize(Vector *, size_t);
void vectorPushBack(Vector *, void *);
void vectorPopBack(Vector *);
void *vectorGet(Vector *);
void vectorFree(Vector *);

Vector *getVectorBlock()
{
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    return vec;
}

Vector *vectorInit(size_t elementSize)
{
    if (!elementSize)
        return NULL;
    void *memory = (void *)malloc(INCREAMENT * elementSize);
    if (!memory)
        return NULL;
    Vector *vec = getVectorBlock();
    if (!vec)
    {
        free(memory);
        return NULL;
    }
    vec->data = memory;
    vec->elementSize = elementSize;
    vec->capacity = INCREAMENT;
    vec->size = 0;
    return vec;
}

void vectorPushBack(Vector *vec, void *data)
{
    if (!vec)
        return;

    if (vec->size >= vec->capacity) {
        size_t newCapacity = vec->capacity * INCREAMENT;
        if (!vectorResize(vec, newCapacity))
            return;
    }

    memcpy((char *)vec->data + (vec->size * vec->elementSize), 
           data, 
           vec->elementSize);
    vec->size++;
}

void vectorPopBack(Vector *vec)
{
    if (!vec)
        return;
    vec->size--;
}

Vector *vectorResize(Vector *vec, size_t newCapacity)
{
    if (!newCapacity)
        return NULL;
    if (!vec)
        return NULL;

    void *newMemory = malloc(newCapacity * vec->elementSize);
    if (!newMemory)
        return NULL;

    if (vec->data) {
        memcpy(newMemory, vec->data, vec->size * vec->elementSize);
        free(vec->data);
    }

    vec->data = newMemory;
    vec->capacity = newCapacity;
    return vec;
}

void *vectorGet(Vector *vec)
{
    if (!vec)
        return NULL;
    return vec->data;
}

void vectorFree(Vector *vec)
{
    if (!vec)
        return;
    if (vec->data)
        free(vec->data);
    free(vec);
}