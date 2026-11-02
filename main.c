//RECEPT PROJECT

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//STRUKTÚRÁK
typedef struct { //összetevő struktúra
    int id;
    char nev[50+1];
} osszetevo;

typedef struct {//hozzávaló struktúra
    int osszetevo_id;
    double mennyiseg;
    char mertekegyseg;
} hozzavalo;

typedef struct { //recept struktúra
    int id;
    char nev[50+1];
    char leiras[2000+1];
    int elkeszitesi_ido;

    hozzavalo *hozzavalok;
    int hozzavalo_db;
} recept;

//GLOBÁLIS VÁLTOZÓK
int recept_db=0;
int osszetevo_db=0;
recept *receptek=NULL;
osszetevo *osszetevok=NULL;


//FUNCTIONS
void load_data()//receptek és összetevők betöltése fileból, formázott alakból dinamikus tömbbe
{
    FILE *file1 = fopen("receptek.txt", "r");//receptek betöltése
    if(file1==NULL)
    {
        printf("Meg nincs recept az adatbazisban!\n");
        return;
    }
    char line[2000];
    int line_num=0;
    while(fgets(line, sizeof(line), file1) && line != NULL)
    {
        recept current_recipe={.id=0, .nev="", .leiras="", .elkeszitesi_ido=0, .hozzavalok=NULL, .hozzavalo_db=0};
        if(line_num==0)
        {
            sscanf(line, "%d\n", &recept_db);
            line_num++;
        }
        else
        {
            switch(line_num)
            {
                case 1://Cím, név, elkészítési idő beolvasása
                    sscanf(line, "%d|%[^|]|%d\n", &current_recipe.id, current_recipe.nev, &current_recipe.elkeszitesi_ido);
                    line_num++;
                    break;
                case 2://Leírás beolvasása
                    sscanf(line, "%[^\\n]\n", current_recipe.leiras);
                    line_num++;
                    break;
                case 3://Hozzávalók számának beolvasása és memóriafoglalás
                    sscanf(line, "%d\n", &current_recipe.hozzavalo_db);
                    current_recipe.hozzavalok = malloc(current_recipe.hozzavalo_db * sizeof(hozzavalo));
                    line_num++;
                    break;
                case 4://Hozzávalók beolvasása és recept hozzáadása a tömbhöz
                    for(int i=0; i<current_recipe.hozzavalo_db; i++)
                    {
                        sscanf(line, "%d|%lf|%c\n", &current_recipe.hozzavalok[i].osszetevo_id, &current_recipe.hozzavalok[i].mennyiseg, &current_recipe.hozzavalok[i].mertekegyseg);
                        fgets(line, sizeof(line), file1);
                    }
                    receptek = realloc(receptek, (recept_db + 1) * sizeof(recept));
                    receptek[recept_db] = current_recipe;
                    line_num = 1;
                    break;
            }
        }
    }
    fclose(file1);

    FILE *file2 = fopen("osszetevok.txt", "r");//összetevők betöltése
    if(file2==NULL)
    {
        printf("Még nincs összetevő az adatbazisban!\n");
        return;
    }
    while(fgets(line, sizeof(line), file2) && line!=NULL)
    {
        osszetevo current_osszetevo={.id=0, .nev=""};
        sscanf(line, "%d|%[^|]\n", &current_osszetevo.id, &current_osszetevo.nev);
        osszetevok = realloc(osszetevok, (osszetevo_db + 1) * sizeof(osszetevo));
        osszetevok[osszetevo_db] = current_osszetevo;
        osszetevo_db++;
        break;
    }


}

void save_data()// receptek és összetevők mentése fileba, formázott alakban tömbből
{
    FILE *file1 = fopen("receptek.txt", "w");//receptek mentése
    if(sizeof(receptek)==0)
    {
        printf("Nincs mentheto recept az adatbazisban!\n");
        return;
    }
    fprintf(file1, "%d\n", recept_db);
    for(int i=0;i<recept_db;i++)
    {
        fprintf(file1, "%d|%s|%d\n", receptek[i].id, receptek[i].nev, receptek[i].elkeszitesi_ido);
        fprintf(file1, "%s\n", receptek[i].leiras);
        fprintf(file1, "%d\n", receptek[i].hozzavalo_db);
        for(int j=0;j<receptek[i].hozzavalo_db;j++)
        {
            fprintf(file1, "%d|%.2lf|%c\n", receptek[i].hozzavalok[j].osszetevo_id, receptek[i].hozzavalok[j].mennyiseg, receptek[i].hozzavalok[j].mertekegyseg);
        }
    }
    fclose(file1);

    FILE *file2 = fopen("osszetevok.txt", "w");//összetevők mentése
    if(sizeof(osszetevok)==0)
    {
        printf("Nincs menthető összetevő az adatbazisban!\n");
        return;
    }
    fprintf(file2, "%d\n", osszetevo_db);
    for(int i=0;i<osszetevo_db;i++)
    {
        fprintf(file2, "%d|%s\n", osszetevok[i].id, osszetevok[i].nev);
    }
    fclose(file2);
}


void print_recipe(int recipeid)//recept kirása a konzolra id alapján
{
    //recept keresése
    recept ki;
    for(int i=0;i<recept_db;i++)//recept keresése id alapján
    {
        if(receptek[i].id==recipeid)
        {
            ki=receptek[i];
            break;
        }
    }
    osszetevo current_osszetevo[ki.hozzavalo_db];
    for(int i=0;i<ki.hozzavalo_db;i++)//összetevők kigyűjtése tömbbe id alapján
    {
        for(int j=0;j<osszetevo_db;j++)
        {
            if(ki.hozzavalok[i].osszetevo_id==osszetevok[j].id)
            {
                current_osszetevo[i]=osszetevok[j];
                break;
            }
        }
    }

    //KIÍRÁS FORMÁJA
    printf("\n=== RECEPT ===\n");
    printf("Recept neve: %s\n", ki.nev);
    printf("Elkészítési idő: %d\n", ki.elkeszitesi_ido);
    printf("Leírás: %s\n", ki.leiras);
    printf("Hozzávalók:\n");
    for(int j=0;j<ki.hozzavalo_db;j++)
    {
        printf("  %d. %s \t| %.2lf %s\n", j+1, current_osszetevo[j].nev, ki.hozzavalok[j].mennyiseg, ki.hozzavalok[j].mertekegyseg);
    }
    printf("=============\n");


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

void keres_nev()// recept keresése név alapján
{
    char nev[50+1];
    printf("Adja meg a recept nevet: ");
    scanf("%50s", nev);
    for(int i=0;i<recept_db;i++)
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
        int random = rand() % recept_db;
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



    //Receptek betöltése
    load_data();
    

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