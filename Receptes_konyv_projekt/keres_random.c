#include "keres_random.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "delete_one_from_tomb.h"
#include "input.h"
#include "print_recipe.h"
#include "recipe_types.h"

void keres_random(const recipe_data *data)
{
    if (data->recept_db == 0)
    {
        printf("Nincs recept az adatbazisban!\n");
        return;
    }

    char accept = 'n';
    recept *recept_halmaz = malloc((size_t)data->recept_db * sizeof(*recept_halmaz));
    if (recept_halmaz == NULL)
    {
        printf("Hiba a memoriafoglalas soran!\n");
        return;
    }
    int delete_index, random, halmaz_meret = data->recept_db;
    for (int i = 0; i < data->recept_db; i++)
    {
        recept_halmaz[i] = data->receptek[i];
    }

    srand((unsigned int)time(NULL));
    while (accept != 'y')
    {
        random = rand() % halmaz_meret;
        printf("Recept neve: %s\n", recept_halmaz[random].nev);
        char answer[16];
        if (!input_read_text("Tetszik ez a recept? (y/n, -1 megszakitas): ", answer, sizeof(answer)))
        {
            free(recept_halmaz);
            return;
        }

        if (strcmp(answer, "-1") == 0)
        {
            printf("A keresés megszakítva!\n");
            free(recept_halmaz);
            return;
        }
        if (strcmp(answer, "y") != 0 && strcmp(answer, "Y") != 0 &&
            strcmp(answer, "n") != 0 && strcmp(answer, "N") != 0)
        {
            printf("Ervenytelen valasz. Csak y vagy n adható meg.\n");
            continue;
        }
        accept = (char)tolower((unsigned char)answer[0]);
        if (accept == 'y')
        {
            print_recipe(data, recept_halmaz[random].id);
            free(recept_halmaz);
            return;
        }
        delete_index = random;
        delete_one_from_tomb(delete_index, &halmaz_meret, recept_halmaz);
        if (halmaz_meret == 0)
        {
            printf("Nincs tovabbi recept!\n");
            free(recept_halmaz);
            return;
        }
    }
}
