#include "delete_one_from_tomb.h"

#include <stdio.h>
#include "recipe_types.h"
#include "debugmalloc.h"

void delete_one_from_tomb(int index, int *tomb_meret, void *tomb)
{
    if (index < 0 || index >= *tomb_meret)
    {
        printf("Hibas index recept torlesekor!\n");
        return;
    }

    if (tomb == NULL)
    {
        printf("Ures tomb a torleshez!\n");
        return;
    }

    char *bytes = (char *)tomb;
    size_t item_size = sizeof(recept);
    for (int i = index; i < *tomb_meret - 1; i++)
    {
        for (size_t j = 0; j < item_size; j++)
        {
            bytes[(i * item_size) + j] = bytes[((i + 1) * item_size) + j];
        }
    }

    *tomb_meret -= 1;
}
