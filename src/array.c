#include "array.h"
#include <string.h>

void arrayRemove(void *array, int *count, int index, size_t elementSize)
{
    if (index < 0 || index >= *count)
        return;
    
    char *elements = array;

    memmove(
        elements + index * elementSize,
        elements + (index + 1) * elementSize,
        (*count - index - 1) * elementSize
    );

    (*count)--;
}