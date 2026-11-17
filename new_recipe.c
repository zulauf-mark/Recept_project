#include "new_recipe.h"

#include <stdio.h>
#include <stdlib.h>

#include "make_hozzavalo.h"
#include "new_osszetevo.h"
#include "recipe_globals.h"
#include "recipe_types.h"

void new_recipe(void)
{
    recept new_recipe;

    recept *receptek_temp = realloc(receptek, (size_t)(recept_db + 1) * sizeof(recept));
    if (receptek_temp == NULL)
    {
        printf("Hiba a memoriafoglalas soran, uj recept letrehozasakor!\n");
        return;
    }
    receptek = receptek_temp;

    int flag = 0;
    for (new_recipe.id = 0; new_recipe.id < recept_db && flag == 0; new_recipe.id++)
    {
        for (int j = 0; j < recept_db + 1; j++)
        {
            if (receptek[j].id == new_recipe.id)
                break;
            else if (j == recept_db + 1)
                flag = 1;
        }
    }

    printf("Adja meg a recept nevet: ");
    scanf("%s", new_recipe.nev);
    printf("Adja meg az elkészítési időt: ");
    scanf("%d", &new_recipe.elkeszitesi_ido);
    printf("Adja meg a leírást: ");
    scanf("%s", new_recipe.leiras);
    receptek[recept_db] = new_recipe;
    recept_db++;

    printf("Osszetevok megadasa:\n");
    char valasz;
    int valasztas;
    printf("Szeretne osszetevot hozzaadni? (y/n)\n");
    while (scanf(" %c", &valasz) && valasz != 'n')
    {
        if (valasz == 'y')
        {
            for (int i = 0; i < osszetevo_db; i++)
            {
                printf("%d. %s\n", osszetevok[i].id, osszetevok[i].nev);
            }
            printf("Adja meg az osszetevo ID-jat, vagy adjon meg egy uj osszetevot(1):\n(-1 a megszakitas)\n");
            switch (scanf("%d", &valasztas))
            {
                case 1:
                    new_osszetevo();
                    break;
                case -1:
                    printf("A recept hozzaadasa megszakitva!\n");
                    return;
                default:
                    hozzavalo uj_hozzavalo = make_hozzavalo(valasztas);
                    receptek[recept_db - 1].hozzavalok = realloc(receptek[recept_db - 1].hozzavalok, (size_t)(receptek[recept_db - 1].hozzavalo_db + 1) * sizeof(hozzavalo));
                    receptek[recept_db - 1].hozzavalok[receptek[recept_db - 1].hozzavalo_db] = uj_hozzavalo;
                    receptek[recept_db - 1].hozzavalo_db++;
                    break;
            }
        }
        else
        {
            printf("Ervenytelen valasz!\n");
        }
        printf("Szeretne osszetevot hozzaadni? (y/n)\n");
    }
}
