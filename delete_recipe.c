#include "delete_recipe.h"

#include <stdio.h>

#include "delete_one_from_tomb.h"
#include "input.h"
#include "recipe_globals.h"

#include <limits.h>

void delete_recipe(void)
{
    if (recept_db == 0)
    {
        printf("Nincs torolheto recept az adatbazisban!\n");
        return;
    }

    for (int i = 0; i < recept_db; i++)
        printf("%d. %s\n", receptek[i].id, receptek[i].nev);

    int id;
    if (!input_read_int("Adja meg a torlendo recept ID-jat (-1 a megszakitas): ", -1, INT_MAX, &id))
        return;
    if (id == -1)
    {
        printf("A recept torlese megszakitva!\n");
        return;
    }
    for (int i = 0; i < recept_db; i++)
    {
        if (receptek[i].id == id)
        {
            delete_one_from_tomb(i, &recept_db, receptek);
            printf("A recept sikeresen torolve lett!\n");
            return;
        }
    }
    printf("Nincs ilyen ID-ju recept az adatbazisban!\n");
}
