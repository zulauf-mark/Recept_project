#include "keres_nev.h"

#include <stdio.h>
#include <string.h>

#include "input.h"
#include "print_recipe.h"
#include "recipe_globals.h"

#include <limits.h>

void keres_nev(void)
{
    char nev[50 + 1];
    int id;
    if (!input_read_text("Adja meg a recept nevet: ", nev, sizeof(nev)))
        return;
    int found = 0;
    for (int i = 0; i < recept_db; i++)
    {
        if (strstr(receptek[i].nev, nev) != NULL)
        {
            printf("Recept neve: %d. %s\n", receptek[i].id, receptek[i].nev);
            found = 1;
        }
    }
    if (!found)
    {
        printf("Nincs ilyen nevű recept az adatbázisban!\n");
        return;
    }

    while (1)
    {
        if (!input_read_int("Adja meg a recept ID-ját a részletekhez (-1 a megszakitas): ", -1, INT_MAX, &id))
            return;
        if (id == -1)
        {
            printf("A keresés megszakítva!\n");
            return;
        }
        for (int i = 0; i < recept_db; i++)
        {
            if (receptek[i].id == id && strstr(receptek[i].nev, nev) != NULL)
            {
                print_recipe(id);
                return;
            }
        }
        printf("Valasszon egy ID-t a fenti talalatok kozul.\n");
    }
}
