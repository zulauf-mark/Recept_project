#include "keres_1anyag.h"

#include <stdio.h>
#include <string.h>

#include "input.h"
#include "recipe_globals.h"

void keres_1anyag(void)
{
    char osszetevo_nev[50 + 1];
    int osszetevo_id = -1;
    if (!input_read_text("Adja meg az osszetevo nevet: ", osszetevo_nev, sizeof(osszetevo_nev)))
        return;
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
