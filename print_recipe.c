#include "print_recipe.h"

#include <stdio.h>

#include "recipe_globals.h"
#include "recipe_types.h"

void print_recipe(int recipeid)
{
    recept ki;
    for (int i = 0; i < recept_db; i++)
    {
        if (receptek[i].id == recipeid)
        {
            ki = receptek[i];
            break;
        }
    }

    osszetevo current_osszetevo[ki.hozzavalo_db];
    for (int i = 0; i < ki.hozzavalo_db; i++)
    {
        for (int j = 0; j < osszetevo_db; j++)
        {
            if (ki.hozzavalok[i].osszetevo_id == osszetevok[j].id)
            {
                current_osszetevo[i] = osszetevok[j];
                break;
            }
        }
    }

    printf("\n=== RECEPT ===\n");
    printf("Recept neve: %s\n", ki.nev);
    printf("Elkészítési idő: %d\n", ki.elkeszitesi_ido);
    printf("Leírás: %s\n", ki.leiras);
    printf("Hozzávalók:\n");
    for (int j = 0; j < ki.hozzavalo_db; j++)
    {
        printf("  %d. %s \t| %.2lf %s\n", j + 1, current_osszetevo[j].nev, ki.hozzavalok[j].mennyiseg, ki.hozzavalok[j].mertekegyseg);
    }
    printf("=============\n");
}
