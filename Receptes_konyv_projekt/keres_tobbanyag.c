#include "keres_tobbanyag.h"

#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "recipe_types.h"
#include "limits.h"

void keres_tobbanyag(const recipe_data *data)
{
    osszetevo *keresett_osszetevok = NULL;
    int keresett_osszetevok_db;
    int osszetevo_id;
    int talalat;
    int i;
    int j;
    int k;

    int find;

    if (data->osszetevo_db == 0)
    {
        printf("Nincs osszetevo az adatbazisban!\n");
        return;
    }

    if (!input_read_int("Adja meg a keresett osszetevok szamat: ", 1, data->osszetevo_db, &keresett_osszetevok_db))
    {
        printf("A keresett osszetevok szamat nem adta meg, a keresest megszakitjuk.\n");
        return;
    }

    keresett_osszetevok = malloc((size_t)keresett_osszetevok_db * sizeof(*keresett_osszetevok));
    if (keresett_osszetevok == NULL)
    {
        printf("Hiba a memoriafoglalas soran, a keresest megszakitjuk.\n");
        return;
    }

    for (i = 0; i < keresett_osszetevok_db; i++)
    {
        for (j = 0; j < data->osszetevo_db; j++)
            printf("%d. %s\n", data->osszetevok[j].id, data->osszetevok[j].nev);

        if (!input_read_int("Adja meg a keresett osszetevo ID-t: ", 0, INT_MAX, &osszetevo_id))
        {
            printf("A keresett osszetevo ID-t nem adta meg, a keresest megszakitjuk.\n");
            free(keresett_osszetevok);
            return;
        }

        talalat = 0;
        for (j = 0; j < data->osszetevo_db; j++)
        {
            if (osszetevo_id == data->osszetevok[j].id)
            {
                keresett_osszetevok[i] = data->osszetevok[j];
                talalat = 1;
                break;
            }
        }

        if (!talalat)
        {
            printf("Nincs ilyen osszetevo az adatbazisban, a keresest megszakitjuk.\n");
            free(keresett_osszetevok);
            return;
        }
    }

    for (i = 0; i < data->recept_db; i++)
    {
        int match = 0;
        find = 0;
        recept draft = data->receptek[i];

        for (k = 0; k < keresett_osszetevok_db; k++)
        {
            for (j = 0; j < draft.hozzavalo_db; j++)
            {
                if (keresett_osszetevok[k].id == draft.hozzavalok[j].osszetevo_id)
                {
                    match++;
                    break;
                }
            }
        }

        if (find == keresett_osszetevok_db)
        {
            printf("Recept neve: %d. %s\n", data->receptek[i].id, data->receptek[i].nev);
            find++;
        }
    }
    if(!find)
        printf("Nem letezik ezeket az osszetevoket tartalmazo recept.\n");
    free(keresett_osszetevok);
}
