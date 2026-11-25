#include "list_recipes.h"

#include <stdio.h>

#include "input.h"
#include "print_recipe.h"
#include "recipe_types.h"

#include <limits.h>

void list_recipes(const recipe_data *data)
{
    if (data->recept_db == 0)
    {
        printf("Nincs recept az adatbazisban!\n");
        return;
    }

    int id;
    for (int i = 0; i < data->recept_db; i++)
    {
        printf("%d. %s\n", data->receptek[i].id, data->receptek[i].nev);
    }
    while (1)
    {
        if (!input_read_int("Adja meg a recept ID-jat a reszletekhez (-1 a megszakitas): ", -1, INT_MAX, &id))
            return;
        if (id == -1)
        {
            printf("A keresés megszakítva!\n");
            return;
        }
        for (int i = 0; i < data->recept_db; i++)
        {
            if (data->receptek[i].id == id)
            {
                print_recipe(data, id);
                return;
            }
        }
        printf("Nincs ilyen ID-ju recept az adatbazisban!\n");
    }
}
