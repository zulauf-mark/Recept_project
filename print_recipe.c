#include "print_recipe.h"

#include <stdio.h>
#include "debugmalloc.h"
#include "recipe_types.h"

void print_recipe(const recipe_data *data, int recipeid)
{
    recept ki;
    for (int i = 0; i < data->recept_db; i++)
    {
        if (data->receptek[i].id == recipeid)
        {
            ki = data->receptek[i];
            break;
        }
    }

    osszetevo current_osszetevo[ki.hozzavalo_db];
    for (int i = 0; i < ki.hozzavalo_db; i++)
    {
        for (int j = 0; j < data->osszetevo_db; j++)
        {
            if (ki.hozzavalok[i].osszetevo_id == data->osszetevok[j].id)
            {
                current_osszetevo[i] = data->osszetevok[j];
                break;
            }
        }
    }

    printf("\n=== RECEPT ===\n");
    printf("Recept neve: %s\n", ki.nev);
    printf("Elkeszitesi ido: %d\n", ki.elkeszitesi_ido);
    printf("Leiras: %s\n", ki.leiras);
    printf("Hozzavalok:\n");
    for (int j = 0; j < ki.hozzavalo_db; j++)
    {
        printf("  %d. %s \t| %.2lf %s\n", j + 1, current_osszetevo[j].nev, ki.hozzavalok[j].mennyiseg, ki.hozzavalok[j].mertekegyseg);
    }
    printf("=============\n");
}
