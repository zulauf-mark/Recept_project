#include "delete_recipe.h"

#include <stdio.h>

#include "delete_one_from_tomb.h"
#include "recipe_globals.h"

void delete_recipe(void)
{
    int id;
    printf("Adja meg a torlendo recept ID-jat:\n(-1 a megszakitas)\n");
    scanf("%d", &id);
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
