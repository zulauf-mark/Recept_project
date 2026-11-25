#ifndef RECIPE_TYPES_H
#define RECIPE_TYPES_H

typedef struct {
    int id;
    char nev[50 + 1];
} osszetevo;

typedef struct {
    int osszetevo_id;
    double mennyiseg;
    char mertekegyseg[32];
} hozzavalo;

typedef struct {
    int id;
    char nev[50 + 1];
    char leiras[2000 + 1];
    int elkeszitesi_ido;

    hozzavalo *hozzavalok;
    int hozzavalo_db;
} recept;

typedef struct {
    int recept_db;
    int osszetevo_db;
    recept *receptek;
    osszetevo *osszetevok;
} recipe_data;

#endif
