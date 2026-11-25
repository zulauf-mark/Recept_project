#include "save_data.h"

#include <stdio.h>
#include <stdlib.h>

#include "recipe_types.h"

void save_data(const recipe_data *data)
{
    FILE *file1 = fopen("receptek.txt", "w");
    if (sizeof(data->receptek) == 0)
    {
        printf("Nincs mentheto recept az adatbazisban!\n");
        return;
    }
    fprintf(file1, "%d\n", data->recept_db);
    for (int i = 0; i < data->recept_db; i++)
    {
        fprintf(file1, "%d|%s|%d\n", data->receptek[i].id, data->receptek[i].nev, data->receptek[i].elkeszitesi_ido);
        fprintf(file1, "%s\n", data->receptek[i].leiras);
        fprintf(file1, "%d\n", data->receptek[i].hozzavalo_db);
        for (int j = 0; j < data->receptek[i].hozzavalo_db; j++)
        {
            fprintf(file1, "%d|%.2lf|%s\n", data->receptek[i].hozzavalok[j].osszetevo_id, data->receptek[i].hozzavalok[j].mennyiseg, data->receptek[i].hozzavalok[j].mertekegyseg);
        }
    }
    fclose(file1);

    FILE *file2 = fopen("osszetevok.txt", "w");
    if (sizeof(data->osszetevok) == 0)
    {
        printf("Nincs menthető összetevő az adatbazisban!\n");
        return;
    }
    fprintf(file2, "%d\n", data->osszetevo_db);
    for (int i = 0; i < data->osszetevo_db; i++)
    {
        fprintf(file2, "%d|%s\n", data->osszetevok[i].id, data->osszetevok[i].nev);
    }
    fclose(file2);
}
