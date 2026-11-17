#include "keres_tobbanyag.h"

#include <stdio.h>

#include "input.h"
#include "recipe_globals.h"

void keres_tobbanyag(void)
{
    osszetevo *keresett_osszetevok = NULL;
    if (osszetevo_db == 0)
    {
        printf("Nincs osszetevo az adatbazisban!\n");
        return;
    }
    int keresett_osszetevok_db;
    if (!input_read_int("Adja meg a keresett osszetevok szamat: ", 1, osszetevo_db, &keresett_osszetevok_db))
        return;
    (void)keresett_osszetevok;
    (void)keresett_osszetevok_db;
}
