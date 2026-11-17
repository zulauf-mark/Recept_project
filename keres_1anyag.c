#include "keres_1anyag.h"

#include <stdio.h>
#include <string.h>

#include "recipe_globals.h"

void keres_1anyag(void)
{
    char osszetevo_nev[50 + 1];
    int osszetevo_id = -1;
    printf("Adja meg az osszetevo nevet: ");
    scanf("%50s", osszetevo_nev);
    for (int i = 0; i < osszetevo_db; i++)
    {
        if (strstr(osszetevok[i].nev, osszetevo_nev) != NULL)
        {
            osszetevo_id = osszetevok[i].id;
            break;
        }
    }
    if (osszetevo_id == -1)
    {
        printf("Nincs ilyen nevű osszetevo az adatbázisban!\n");
        return;
    }

    for (int i = 0; i < recept_db; i++)
    {
        for (int j = 0; j < receptek[i].hozzavalo_db; j++)
        {
            if (receptek[i].hozzavalok[j].osszetevo_id == osszetevo_id)
            {
                printf("Recept neve: %d. %s\n", receptek[i].id, receptek[i].nev);
            }
        }
    }
}
