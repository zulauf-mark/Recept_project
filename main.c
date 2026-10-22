//RECEPT PROJECT

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//STRUKTÚRÁK
typedef struct { //összetevő struktúra
    int id;
    char nev[50+1];
} osszetevo;

typedef struct { //recept struktúra
    int id;
    char nev[50+1];
    int osszetevokszama;
    int osszetevoid[50];
    char mertek[50][20+1];
    char leiras[2000+1];
} recept;

//GLOBÁLIS VÁLTOZÓK
int db=0;
recept receptek[1000];
osszetevo osszetevok[1000];


//FUNCTIONS
void load_osszetevok()
{

}

void save_osszetevok()
{

}

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
                sscanf(sor, "%d %50s", &receptek[db].id, &receptek[db].nev);
                break;
            case '2':
                sscanf(sor[1], "%d", &receptek[db].osszetevokszama);
                osszetevoszam=receptek[db].osszetevokszama;
                break;
            case '3':
                for(int i=1;i<osszetevoszam+1; i++)
                {
                    sscanf(sor[i], "%d", &receptek[db].osszetevoid[i]);
                }
                break;
            case '4':
                for(int i=1; i<osszetevoszam+1; i++)
                {
                    sscanf(sor[i], "%50s", &receptek[db].mertek[i]);
                }
                break;
            case '5':
                sscanf(sor, "%2000s", &receptek[db].leiras);
                break;
            default:
                printf("Nem található kezdeti érték.");
                break;
        }
    }
    db++;
}

void save_recipes(recept receptek[100],int db) //receptek mentése tömbből file-ba
{
    FILE *file = fopen("receptek.txt", "w");

    for(int i=0;i<db+1;i++)
    {
        printf("1 %d %50s\n", receptek[i].id,receptek[i].nev);
        printf("2 %d\n", receptek[db].osszetevokszama);
        printf("3 ");
        for(int j=0;j<receptek[db].osszetevokszama;j++)
        {
            printf("%d ",receptek[db].osszetevoid[j]);
        }
        printf("4 ");
        for(int j=0;j<receptek[db].osszetevokszama;j++)
        {
            printf("%20s ",receptek[db].mertek[j]);
        }
        printf("\n5 %2000s\n",receptek[db].leiras);
    }
}

void print_recipe(int recipeid)//recept kirása a konzolra id alapján
{
    //recept keresése
    recept ki;
    for(int i=0;i<db;i++)
    {
        if(receptek[i].id==recipeid)
        {
            ki=receptek[i];
        }
    }

    //formatted output
    printf("%d %50s", ki.id,ki.nev);
    for(int i=0;i<ki.osszetevokszama;i++)
    {
        printf("%d", ki.osszetevoid[i]);
    }
    printf("%2000s\n",ki.leiras);

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

void keres_nev()// recept keresése név alapján
{
    char nev[50+1];
    printf("Adja meg a recept nevet: ");
    scanf("%50s", nev);
    for(int i=0;i<db;i++)
    {
        if(receptek[i].nev==nev)
        {
            print_recipe(receptek[i].id);
        }
    }
}

void keres_random()//random recept keresése amíg a felhasználó el nem fogadja
{
    char accept;
    while(accept!='y')
    {
        srand(time(NULL));
        int random = rand() % db;
        print_recipe(random);
        printf("Tetszik ez a recept? (y/n): ");
        scanf(" %c", &accept);
    }
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