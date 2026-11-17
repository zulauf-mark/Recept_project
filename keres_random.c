#include "keres_random.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "delete_one_from_tomb.h"
#include "print_recipe.h"
#include "recipe_globals.h"
#include "recipe_types.h"

void keres_random(void)
{
    char accept = 'n';
    char input[16];
    recept recept_halmaz[recept_db];
    int delete_index, random, halmaz_meret = recept_db;
    for (int i = 0; i < recept_db; i++)
    {
        recept_halmaz[i] = receptek[i];
    }

    while (accept != 'y')
    {
        srand((unsigned int)time(NULL));
        random = rand() % halmaz_meret;
        printf("Recept neve: %s\n", recept_halmaz[random].nev);
        printf("Tetszik ez a recept? (y/n):\n(-1 a megszakitas)\n");
        if (scanf("%15s", input) != 1)
        {
            printf("A keresés megszakítva!\n");
            return;
        }

        if (strcmp(input, "-1") == 0)
        {
            printf("A keresés megszakítva!\n");
            return;
        }

        accept = input[0];
        delete_index = random;
        delete_one_from_tomb(delete_index, &halmaz_meret, recept_halmaz);
        if (halmaz_meret == 0)
        {
            printf("Nincs további recept!\n");
            break;
        }
    }
    print_recipe(recept_halmaz[random].id);
}
