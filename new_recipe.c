#include "new_recipe.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "input.h"
#include "make_hozzavalo.h"
#include "new_osszetevo.h"
#include "recipe_types.h"

static int append_ingredient(recept *recipe, int ingredient_id)
{
    for (int i = 0; i < recipe->hozzavalo_db; i++)
    {
        if (recipe->hozzavalok[i].osszetevo_id == ingredient_id)
        {
            printf("Ez az osszetevo mar szerepel a receptben.\n");
            return 1;
        }
    }

    hozzavalo uj_hozzavalo;
    if (!make_hozzavalo(ingredient_id, &uj_hozzavalo))
        return 0;

    hozzavalo *temp = realloc(recipe->hozzavalok, (size_t)(recipe->hozzavalo_db+1) * sizeof(*recipe->hozzavalok));
    if (temp == NULL)
    {
        printf("Hiba a memoriafoglalas soran, hozzavalo hozzaadasakor!\n");
        return 0;
    }
    recipe->hozzavalok = temp;
    recipe->hozzavalok[recipe->hozzavalo_db++] = uj_hozzavalo;
    return 1;
}

static int next_recipe_id(const recipe_data *data, int *id)
{
    for (int candidate = 0; ; candidate++)
    {
        int used = 0;
        for (int i = 0; i < data->recept_db; i++)
        {
            if (data->receptek[i].id == candidate)
            {
                used = 1;
                break;
            }
        }
        if (!used)
        {
            *id = candidate;
            return 1;
        }
        if (candidate == INT_MAX)
            return 0;
    }
}

void new_recipe(recipe_data *data)
{
    recept draft = {.id = 0, .nev = "", .leiras = "", .elkeszitesi_ido = 0,.hozzavalok = NULL, .hozzavalo_db = 0};
    int valid_name = 0;
    while (input_read_text("Adja meg a recept nevet: ", draft.nev, sizeof(draft.nev)))
    {
        if (strchr(draft.nev, '|') == NULL)
        {
            valid_name = 1;
            break;
        }
        printf("A recept neve nem tartalmazhat | karaktert.\n");
    }
    if (!valid_name ||
        !input_read_int("Adja meg az elkeszitesi idot percben: ", 1, INT_MAX, &draft.elkeszitesi_ido) ||
        !input_read_text("Adja meg a leirast: ", draft.leiras, sizeof(draft.leiras)))
        return;

    printf("Osszetevok megadasa:\n");
    while (1)
    {
        char answer;
        if (!input_read_yes_no("Szeretne osszetevot hozzaadni? (y/n): ", &answer))
        {
            free(draft.hozzavalok);
            return;
        }
        if (answer == 'n')
        {
            if (draft.hozzavalo_db == 0)
            {
                printf("Legalabb egy osszetevot meg kell adni.\n");
                continue;
            }
            break;
        }

        for (int i = 0; i < data->osszetevo_db; i++)
            printf("%d. %s\n", data->osszetevok[i].id, data->osszetevok[i].nev);

        char selection[32];
        if (!input_read_text("Adjon meg egy osszetevo ID-t, 'n' uj osszetevohoz, vagy -1 a megszakitashoz: ", selection, sizeof(selection)))
        {
            free(draft.hozzavalok);
            return;
        }
        if (strcmp(selection, "-1") == 0)
        {
            printf("A recept hozzaadasa megszakitva!\n");
            free(draft.hozzavalok);
            return;
        }

        int ingredient_id;
        if (strcmp(selection, "n") == 0 || strcmp(selection, "N") == 0)
        {
            int previous_count = data->osszetevo_db;
            new_osszetevo(data);
            if (data->osszetevo_db == previous_count)
                continue;
            ingredient_id = data->osszetevok[data->osszetevo_db - 1].id;
        }
        else
        {
            if (!input_parse_int(selection, &ingredient_id))
            {
                printf("Ervenytelen osszetevo ID.\n");
                continue;
            }
            int exists = 0;
            for (int i = 0; i < data->osszetevo_db; i++)
                if (data->osszetevok[i].id == ingredient_id)
                    exists = 1;
            if (!exists)
            {
                printf("Nincs ilyen ID-ju osszetevo az adatbazisban.\n");
                continue;
            }
        }

        if (!append_ingredient(&draft, ingredient_id))
        {
            free(draft.hozzavalok);
            return;
        }
    }

    if (!next_recipe_id(data, &draft.id))
    {
        printf("Nem hozhato letre uj recept: elfogytak az azonosito-k.\n");
        free(draft.hozzavalok);
        return;
    }
    recept *temp = realloc(data->receptek, (size_t)(data->recept_db + 1) * sizeof(*data->receptek));
    if (temp == NULL)
    {
        printf("Hiba a memoriafoglalas soran, uj recept letrehozasakor!\n");
        free(draft.hozzavalok);
        return;
    }
    data->receptek = temp;
    data->receptek[data->recept_db++] = draft;
    printf("A recept sikeresen hozzaadva.\n");
}
