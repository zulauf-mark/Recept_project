#include "load_data.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recipe_types.h"

void load_data(recipe_data *data)
{
    FILE *file1 = fopen("receptek.txt", "r");
    if (file1 == NULL)
    {
        printf("Meg nincs recept az adatbazisban!\n");
        return;
    }

    char line[2000];
    int line_num = 0;
    while (fgets(line, sizeof(line), file1))
    {
        recept current_recipe = {.id = 0, .nev = "", .leiras = "", .elkeszitesi_ido = 0, .hozzavalok = NULL, .hozzavalo_db = 0};
        if (line_num == 0)
        {
            sscanf(line, "%d\n", &data->recept_db);
            line_num++;
        }
        else
        {
            switch (line_num)
            {
                case 1:
                    sscanf(line, "%d|%[^|]|%d\n", &current_recipe.id, current_recipe.nev, &current_recipe.elkeszitesi_ido);
                    line_num++;
                    break;
                case 2:
                    sscanf(line, "%[^\\n]\n", current_recipe.leiras);
                    line_num++;
                    break;
                case 3:
                    sscanf(line, "%d\n", &current_recipe.hozzavalo_db);
                    current_recipe.hozzavalok = malloc((size_t)current_recipe.hozzavalo_db * sizeof(hozzavalo));
                    line_num++;
                    break;
                case 4:
                    for (int i = 0; i < current_recipe.hozzavalo_db; i++)
                    {
                        sscanf(line, "%d|%lf|%31[^\n]", &current_recipe.hozzavalok[i].osszetevo_id, &current_recipe.hozzavalok[i].mennyiseg, current_recipe.hozzavalok[i].mertekegyseg);
                        fgets(line, sizeof(line), file1);
                    }
                    data->receptek = realloc(data->receptek, (size_t)(data->recept_db + 1) * sizeof(recept));
                    data->receptek[data->recept_db] = current_recipe;
                    line_num = 1;
                    break;
            }
        }
    }
    fclose(file1);

    FILE *file2 = fopen("osszetevok.txt", "r");
    if (file2 == NULL)
    {
        printf("Meg nincs osszetevo az adatbazisban!\n");
        return;
    }
    while (fgets(line, sizeof(line), file2))
    {
        osszetevo current_osszetevo = {.id = 0, .nev = ""};
        sscanf(line, "%d|%[^|]\n", &current_osszetevo.id, current_osszetevo.nev);
        data->osszetevok = realloc(data->osszetevok, (size_t)(data->osszetevo_db + 1) * sizeof(osszetevo));
        data->osszetevok[data->osszetevo_db] = current_osszetevo;
        data->osszetevo_db++;
        break;
    }
    fclose(file2);
}
