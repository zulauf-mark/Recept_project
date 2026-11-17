#include "save_data.h"

#include <stdio.h>
#include <stdlib.h>

#include "recipe_globals.h"
#include "recipe_types.h"

void save_data(void)
{
    FILE *file1 = fopen("receptek.txt", "w");
    if (sizeof(receptek) == 0)
    {
        printf("Nincs mentheto recept az adatbazisban!\n");
        return;
    }
    fprintf(file1, "%d\n", recept_db);
    for (int i = 0; i < recept_db; i++)
    {
        fprintf(file1, "%d|%s|%d\n", receptek[i].id, receptek[i].nev, receptek[i].elkeszitesi_ido);
        fprintf(file1, "%s\n", receptek[i].leiras);
        fprintf(file1, "%d\n", receptek[i].hozzavalo_db);
        for (int j = 0; j < receptek[i].hozzavalo_db; j++)
        {
            fprintf(file1, "%d|%.2lf|%c\n", receptek[i].hozzavalok[j].osszetevo_id, receptek[i].hozzavalok[j].mennyiseg, receptek[i].hozzavalok[j].mertekegyseg);
        }
    }
    fclose(file1);

    FILE *file2 = fopen("osszetevok.txt", "w");
    if (sizeof(osszetevok) == 0)
    {
        printf("Nincs menthető összetevő az adatbazisban!\n");
        return;
    }
    fprintf(file2, "%d\n", osszetevo_db);
    for (int i = 0; i < osszetevo_db; i++)
    {
        fprintf(file2, "%d|%s\n", osszetevok[i].id, osszetevok[i].nev);
    }
    fclose(file2);
}
