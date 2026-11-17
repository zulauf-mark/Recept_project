#include "new_osszetevo.h"

#include <stdio.h>
#include <stdlib.h>

#include "recipe_globals.h"
#include "recipe_types.h"

void new_osszetevo(void)
{
    osszetevo *osszetevok_temp = realloc(osszetevok, (size_t)(osszetevo_db + 1) * sizeof(osszetevo));
    if (osszetevok_temp == NULL)
    {
        printf("Hiba a memoriafoglalas soran, uj osszetevo letrehozasakor!\n");
        return;
    }
    osszetevok = osszetevok_temp;

    int flag = 0;
    osszetevo new_osszetevo;
    for (new_osszetevo.id = 0; new_osszetevo.id < osszetevo_db && flag == 0; new_osszetevo.id++)
    {
        for (int j = 0; j < osszetevo_db + 1; j++)
        {
            if (osszetevok[j].id == new_osszetevo.id)
                break;
            else if (j == osszetevo_db + 1)
                flag = 1;
        }
    }
    printf("Adja meg az osszetevo nevet:\n");
    scanf("%s", new_osszetevo.nev);
    osszetevok[osszetevo_db] = new_osszetevo;
    osszetevo_db++;
}
