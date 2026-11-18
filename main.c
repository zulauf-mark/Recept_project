//RECEPT PROJECT

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "debugmalloc.h"

//HEADER FILES
#include "delete_one_from_tomb.h"
#include "delete_recipe.h"
#include "input.h"
#include "keres_1anyag.h"
#include "keres_nev.h"
#include "keres_random.h"
#include "keres_tobbanyag.h"
#include "list_recipes.h"
#include "load_data.h"
#include "make_hozzavalo.h"
#include "new_osszetevo.h"
#include "new_recipe.h"
#include "print_recipe.h"
#include "recipe_globals.h"
#include "recipe_types.h"
#include "save_data.h"

//MAIN FUNCTION
int main(void)
{
    int valasztas;

    load_data();

    do
    {
        printf("\n=== RECEPTGYUJTEMENY ===\n");
        printf("1. Uj recept\n");
        printf("2. Recept torlese\n");
        printf("3. Kereses nev alapjan\n");
        printf("4. Nincs otletem\n");
        printf("5. De ennek egy kis...\n");
        printf("6. El kell hasznalni\n");
        printf("7. Osszetevo hozzaadasa\n");
        printf("8. Receptek listazasa\n");
        printf("0. Kilepes\n");

        if (!input_read_int("Valasztas: ", 0, 8, &valasztas))
            break;

        switch (valasztas)
        {
            case 1:
                new_recipe();
                break;

            case 2:
                delete_recipe();
                break;

            case 3:
                keres_nev();
                break;

            case 4:
                keres_random();
                break;

            case 5:
                keres_1anyag();
                break;

            case 6:
                keres_tobbanyag();
                break;

            case 7:
                new_osszetevo();
                break;

            case 8:
                list_recipes();
                break;

            case 0:
                printf("Viszlat!\n");
                break;

            default:
                printf("Ervenytelen valasztas!\n");
        }
    } while (valasztas != 0);

    save_data();
    return 0;
}
