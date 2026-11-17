#include "list_recipes.h"

#include <stdio.h>

#include "print_recipe.h"
#include "recipe_globals.h"

void list_recipes(void)
{
    int id;
    for (int i = 0; i < recept_db; i++)
    {
        printf("%d. %s\n", receptek[i].id, receptek[i].nev);
    }
    printf("Adja meg a recept ID-ját a részletekhez:\n(-1 a megszakitas)\n");
    if (scanf("%d", &id) == -1)
    {
        printf("A keresés megszakítva!\n");
        return;
    }
    print_recipe(id);
}
