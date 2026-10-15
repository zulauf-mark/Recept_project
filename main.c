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
    osszetevo osszetevok[50];
    char mértekegysegek[50][20];
    char leiras[2000];
} recept;


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
    int i=0;
    while(fgets(sor,sizeof(sor),file)!=NULL)
    {
        switch(sor[0]){
            case '1':
                //id,nev
                break;
            case '2':
                //osszetevok
                break;
            case '3':
                //mertekegyseg
                break;
            case '4':
                //leiras
                break;
            default:
                printf("Nem található kezdeti érték.");
                break;
        }
    }
}

void save_recipes(recept receptek[1000])
{

}

void print_recipe()
{

}

void new_recipe()
{
    
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