#include "new_osszetevo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "debugmalloc.h"
#include "input.h"
#include "recipe_types.h"

static int names_equal(const char *left, const char *right)
{
    while (*left != '\0' && *right != '\0')
    {
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right))
            return 0;
        left++;
        right++;
    }
    return *left == *right;
}

void new_osszetevo(recipe_data *data)
{
    osszetevo new_osszetevo;
    int valid_name = 0;
    while (input_read_text("Adja meg az osszetevo nevet: ", new_osszetevo.nev, sizeof(new_osszetevo.nev)))
    {
        if (strchr(new_osszetevo.nev, '|') == NULL)
        {
            valid_name = 1;
            break;
        }
        printf("Az osszetevo neve nem tartalmazhat | karaktert.\n");
    }
    if (!valid_name)
        return;
    for (int i = 0; i < data->osszetevo_db; i++)
    {
        if (names_equal(data->osszetevok[i].nev, new_osszetevo.nev))
        {
            printf("Ilyen nevu osszetevo mar szerepel az adatbazisban!\n");
            return;
        }
    }

    new_osszetevo.id = 0;
    while (1)
    {
        int used = 0;
        for (int i = 0; i < data->osszetevo_db; i++)
        {
            if (data->osszetevok[i].id == new_osszetevo.id)
            {
                used = 1;
                break;
            }
        }
        if (!used)
            break;
        if (new_osszetevo.id == INT_MAX)
        {
            printf("Nem hozhato letre uj osszetevo: elfogytak az azonosito-k.\n");
            return;
        }
        new_osszetevo.id++;
    }

    osszetevo *osszetevok_temp = realloc(data->osszetevok, (size_t)(data->osszetevo_db + 1) * sizeof(osszetevo));
    if (osszetevok_temp == NULL)
    {
        printf("Hiba a memoriafoglalas soran, uj osszetevo letrehozasakor!\n");
        return;
    }
    data->osszetevok = osszetevok_temp;
    data->osszetevok[data->osszetevo_db] = new_osszetevo;
    data->osszetevo_db++;
}
