#include "keres_nev.h"

#include <stdio.h>
#include <string.h>

#include "print_recipe.h"
#include "recipe_globals.h"

void keres_nev(void)
{
    char nev[50 + 1];
    int id;
    printf("Adja meg a recept nevet: ");
    scanf("%50s", nev);
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
    }
    printf("Adja meg a recept ID-ját a részletekhez:\n(-1 a megszakitas)\n");
    if (scanf("%d", &id) == -1)
    {
        printf("A keresés megszakítva!\n");
        return;
    }
    print_recipe(id);
}
