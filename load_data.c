#include "load_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recipe_globals.h"
#include "recipe_types.h"
#include "debugmalloc.h"

void load_data(void)
{
    FILE *file1 = fopen("receptek.txt", "r");
    if (file1 == NULL)//Ellenőrzés
    {
        printf("Meg nincs recept az adatbazisban!\n");
        return;
    }

    char line[2001];
    if (fgets(line, sizeof(line), file1) == NULL ||
        sscanf(line, "%d", &recept_db) != 1 ||
        recept_db < 0)
    {
        printf("Hibas receptadatbazis!\n");
        fclose(file1);
        recept_db = 0;
        receptek = NULL;
        return;
    }

    receptek = recept_db > 0 ? malloc((size_t)recept_db * sizeof(recept)) : NULL;
    if (recept_db > 0 && receptek == NULL)
    {
        printf("Hiba a memoriafoglalas soran, receptadatbazis betoltesehez!\n");
        fclose(file1);
        recept_db = 0;
        return;
    }

    int loaded_recipes = 0;
    for (int i = 0; i < recept_db; i++)
    {
        recept current_recipe = {
            .id = 0, .nev = "", .leiras = "",
            .elkeszitesi_ido = 0, .hozzavalok = NULL, .hozzavalo_db = 0
        };

        if (fgets(line, sizeof(line), file1) == NULL ||
            sscanf(line, "%d|%50[^|]|%d",
                   &current_recipe.id, current_recipe.nev,
                   &current_recipe.elkeszitesi_ido) != 3)
            break;

        if (fgets(line, sizeof(line), file1) == NULL ||
            sscanf(line, "%2000[^\n]", current_recipe.leiras) != 1)
            break;

        if (fgets(line, sizeof(line), file1) == NULL ||
            sscanf(line, "%d", &current_recipe.hozzavalo_db) != 1 ||
            current_recipe.hozzavalo_db < 0)
            break;

        if (current_recipe.hozzavalo_db > 0)
        {
            current_recipe.hozzavalok =
                malloc((size_t)current_recipe.hozzavalo_db * sizeof(hozzavalo));
            if (current_recipe.hozzavalok == NULL)
                break;
        }

        int valid = 1;
        for (int j = 0; j < current_recipe.hozzavalo_db; j++)
        {
            if (fgets(line, sizeof(line), file1) == NULL ||
                sscanf(line, "%d|%lf|%31[^\n]",
                       &current_recipe.hozzavalok[j].osszetevo_id,
                       &current_recipe.hozzavalok[j].mennyiseg,
                       current_recipe.hozzavalok[j].mertekegyseg) != 3)
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            free(current_recipe.hozzavalok);
            break;
        }

        receptek[loaded_recipes++] = current_recipe;
    }

    if (loaded_recipes != recept_db)
    {
        for (int i = 0; i < loaded_recipes; i++)
            free(receptek[i].hozzavalok);
        free(receptek);
        receptek = NULL;
        recept_db = 0;
        printf("Hibas receptadatbazis!\n");
    }
    fclose(file1);

    FILE *file2 = fopen("osszetevok.txt", "r");//osszetevok file megnyitása
    if (file2 == NULL)
    {
        printf("Meg nincs osszetevo az adatbazisban!\n");
        return;
    }

    if (fgets(line, sizeof(line), file2) == NULL ||
        sscanf(line, "%d", &osszetevo_db) != 1 ||
        osszetevo_db < 0)
    {
        printf("Hibas osszetevo-adatbazis!\n");
        fclose(file2);
        osszetevo_db = 0;
        osszetevok = NULL;
        return;
    }

    osszetevok = osszetevo_db > 0
        ? malloc((size_t)osszetevo_db * sizeof(osszetevo))
        : NULL;
    if (osszetevo_db > 0 && osszetevok == NULL)
    {
        printf("Hiba a memoriafoglalas soran, osszetevo-adatbazis betoltesehez!\n");
        fclose(file2);
        osszetevo_db = 0;
        return;
    }

    int loaded_ingredients = 0;
    for (int i = 0; i < osszetevo_db; i++)
    {
        osszetevo current_osszetevo = {.id = 0, .nev = ""};
        if (fgets(line, sizeof(line), file2) == NULL ||
            sscanf(line, "%d|%50[^\n]",
                   &current_osszetevo.id, current_osszetevo.nev) != 2)
            break;

        osszetevok[loaded_ingredients++] = current_osszetevo;
    }

    if (loaded_ingredients != osszetevo_db)
    {
        free(osszetevok);
        osszetevok = NULL;
        osszetevo_db = 0;
        printf("Hibas osszetevo-adatbazis!\n");
    }
    fclose(file2);
}
