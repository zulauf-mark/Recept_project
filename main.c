//RECEPT PROJECT

//INCLUDES
#include <stdio.h>


//STRUKTÚRÁK
typedef struct {
    int id;
    char nev[50];
} osszetevo;

typedef struct {
    int id;
    char nev[50];
    int osszetevokszama;
    osszetevo osszetevok[50];
    char mertek[50][20];
    char leiras[2000];
} recept;

//GLOBÁLIS VÁLTOZÓK
int db=0;


//FUNCTIONS
void load_recipes(recept receptek[1000]) //receptek töltése file-ból a tömbbe
{
    FILE *file = fopen("receptek.txt", "r");

    if(file==NULL)
    {
        printf("Nem található elmentett recept.");
        return;
    }
    char sor[3000];
    
    while(fgets(sor,sizeof(sor),file)!=NULL)
    {   
        int osszetevoszam=0;
        switch(sor[0]){
            case '1':
                sscanf(sor, "%d %49s", &receptek[db].id, &receptek[db].nev);
                break;
            case '2':
                sscanf(sor[1], "%d", &receptek[db].osszetevokszama);
                osszetevoszam=receptek[db].osszetevokszama;
            case '3':
                for(int i=0;i<osszetevoszam+1; i++)
                {
                    sscanf(sor[i], "%d%49s", &receptek[db].osszetevok[i].id, &receptek[db].osszetevok[i].nev);
                }
                break;
            case '4':
                for(int i=0; i<osszetevoszam; i++)
                {
                    sscanf(sor[db], "%49s", &receptek[db].mertek[i]);
                }
                break;
            case '5':
                sscanf(sor, "%1999", &receptek[db].leiras);
                break;
            default:
                printf("Nem található kezdeti érték.");
                break;
        }
    }
    db++;
}

void save_recipes(recept receptek[100],int db)
{
    FILE *file = fopen("receptek.txt", "w");

    for(int i=0;i<db+1;i++)
    {
        printf("1 %d %49s\n", receptek[i].id,receptek[i].nev);
        printf("2 %d\n", receptek[db].osszetevokszama);
        printf("3 ");
        for(int i=0;i<receptek[db].osszetevokszama;i++)
        {
            printf("%d%49s ",receptek[db].osszetevok.id, receptek[db].osszetevok.id);
        }
    }
}

void print_recipe()
{

}

void new_recipe()
{
    db++;
}

void new_osszetevo()
{

}

void delete_recipe()
{

}

void keres_nev()
{

}

void keres_random()
{

}

void keres_1anyag()
{

}

void keres_tobbanyag()
{

}


//MAIN FUNCTION
int main()
{
    //Változók
    int valasztas; //GUI választás
    recept receptek[1000]; //Receptek tömbje



    //Receptek betöltése
    load_recipes(receptek);
    

    do 
    {

        //GUI
        printf("\n=== RECEPTGYUJTEMENY ===\n");
        printf("1. Uj recept\n");
        printf("2. Recept torlese\n");
        printf("3. Kereses nev alapjan\n");
        printf("4. Nincs otletem\n");
        printf("5. De ennek egy kis...\n");
        printf("6. El kell hasznalni\n");
        printf("7. Osszetevo hozzaadasa\n");
        printf("0. Kilepes\n");

        printf("Valasztas: ");
        scanf("%d", &valasztas);

        switch (valasztas) {

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

            case 0:
                printf("Viszlat!\n");
                break;

            default:
                printf("Ervenytelen valasztas!\n");
        }

    } while (valasztas != 0);
}