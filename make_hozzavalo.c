#include "make_hozzavalo.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "debugmalloc.h"
#include "input.h"

static int valid_unit(const char *unit)
{
    for (size_t i = 0; unit[i] != '\0'; i++)
    {
        if ((unsigned char)unit[i] >= 0x80)
            return strcmp(unit, "evőkanál") == 0;
        if (!isalpha((unsigned char)unit[i]))
            return 0;
    }
    return 1;
}

int make_hozzavalo(int osszetevo_id, hozzavalo *result)
{
    double mennyiseg;
    char unit[sizeof(result->mertekegyseg)];
    if (!input_read_positive_double("Adja meg a hozzavalo mennyiseget: ", &mennyiseg))
        return 0;
    while (input_read_text("Adja meg a hozzavalo mertekegyseget: ", unit, sizeof(unit)))
    {
        if (valid_unit(unit))
        {
            result->osszetevo_id = osszetevo_id;
            result->mennyiseg = mennyiseg;
            snprintf(result->mertekegyseg, sizeof(result->mertekegyseg), "%s", unit);
            return 1;
        }
        printf("Ervenytelen mertekegyseg. Betukbol allo mertekegyseget adjon meg.\n");
    }
    return 0;
}
