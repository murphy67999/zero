#include "array.h"
#include <string.h>

void array_remove(void *array, size_t *count, size_t index, size_t element_size)
{
    if (index < 0 || index >= *count)
        return;
    
    char *elements = array;

    memmove(
        elements + index * element_size,
        elements + (index + 1) * element_size,
        (*count - index - 1) * element_size
    );

    (*count)--;
}