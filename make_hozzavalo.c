#include "make_hozzavalo.h"

#include <stdio.h>

hozzavalo make_hozzavalo(int osszetevo_id)
{
    double mennyiseg;
    char mertekegyseg;
    hozzavalo uj_hozzavalo;
    uj_hozzavalo.osszetevo_id = osszetevo_id;
    printf("Adja meg a hozzavalo mennyiseget:\n");
    scanf("%lf", &mennyiseg);
    printf("Adja meg a hozzavalo mertekegyseget:\n");
    scanf(" %c", &mertekegyseg);
    uj_hozzavalo.mennyiseg = mennyiseg;
    uj_hozzavalo.mertekegyseg = mertekegyseg;
    return uj_hozzavalo;
}
