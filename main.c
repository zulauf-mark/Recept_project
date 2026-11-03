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
    recept new_recipe;
    
    //Új recept helyének lefoglalása
    recept *receptek_temp = realloc(receptek, (recept_db + 1) * sizeof(recept));
    if (receptek_temp == NULL) {
        printf("Hiba a memoriafoglalas soran, uj recept letrehozasakor!\n");
        return;
    }
    receptek = receptek_temp;

    //Új recept ID generálása
    int flag=0;
    for(new_recipe.id=0; new_recipe.id<recept_db && flag==0; new_recipe.id++)
    {
        for(int j=0;j<recept_db+1;j++)
        {
            if(receptek[j].id==new_recipe.id)
                break;
            else if(j==recept_db+1)
                flag=1;

        }
    }


    //Adatok bekérése a felhasználótól
    printf("Adja meg a recept nevet: ");
    scanf("%s", new_recipe.nev);
    printf("Adja meg az elkészítési időt: ");
    scanf("%d", &new_recipe.elkeszitesi_ido);
    printf("Adja meg a leírást: ");
    scanf("%s", new_recipe.leiras);
    receptek[recept_db] = new_recipe;
    recept_db++;


    //Összetevők hozzáadása a recepthez
    printf("Osszetevok megadasa:\n");
    char valasz;
    int valasztas, osszetevo_id;
    printf("Szeretne osszetevot hozzaadni? (y/n)\n");
    while(scanf(" %c", &valasz) && valasz != 'n')
    {
        if(valasz=='y')
        {
            for(int i=0;i<osszetevo_db;i++)
            {
                printf("%d. %s\n", osszetevok[i].id, osszetevok[i].nev);
            }
            printf("Adja meg az osszetevo ID-jat, vagy adjon meg egy uj osszetevot(1):\n(-1 a megszakitas)\n");
            switch(scanf("%d", &valasztas))
            {
                case 1:
                    new_osszetevo();
                    break;
                case -1:
                    printf("A recept hozzaadasa megszakitva!\n");
                    return;
                default:
                    osszetevo_id=valasztas;

                    break;
            }
            //Hozzávaló hozzáadása
            new_osszetevo();
        }
        else
        {
            printf("Ervenytelen valasz!\n");
        }
        printf("Szeretne osszetevot hozzaadni? (y/n)\n");
    }
}

void new_osszetevo()
{

}

void delete_one_from_tomb(int index, int *tomb_meret, recept *tomb)//egy elem törlése a tömbből index alapján
{
    if (index < 0 || index >= *tomb_meret) 
    {
        printf("Hibas index recept torlesekor!\n");
        return;
    }

    for (int i = index; i < *tomb_meret - 1; i++) 
    {
        tomb[i] = tomb[i + 1];
    }

    *tomb_meret--;
}

void delete_recipe()//recept törlése id alapján
{
    int id;
    printf("Adja meg a torlendo recept ID-jat:\n(-1 a megszakitas)\n");
    scanf("%d", &id);
    if(id==-1)
    {
        printf("A recept torlese megszakitva!\n");
        return;
    }
    for(int i=0;i<recept_db;i++)
    {
        if(receptek[i].id==id)
        {
            delete_one_from_tomb(i, &recept_db, receptek);
            printf("A recept sikeresen torolve lett!\n");
            return;
        }
    }
    printf("Nincs ilyen ID-ju recept az adatbazisban!\n");
}

void keres_nev()// recept keresése név vagy annak részlete alapján
{
    char nev[50+1];
    int id;
    printf("Adja meg a recept nevet: ");
    scanf("%50s", nev);
    for(int i=0;i<recept_db;i++)
    {
        if(strstr(receptek[i].nev, nev) != NULL)
        {
            printf("Recept neve: %d. %s\n", receptek[i].id, receptek[i].nev);
        }
        else
        {
            printf("Nincs ilyen nevű recept az adatbázisban!\n");
        }
    }
    printf("Adja meg a recept ID-ját a részletekhez:\n(-1 a megszakitas)\n");
    if(scanf("%d", &id) == -1)
    {
        printf("A keresés megszakítva!\n");
        return;
    }
    print_recipe(id);
}

void keres_random()//random recept keresése amíg a felhasználó el nem fogadja
{
    char accept;
    recept recept_halmaz[recept_db];
    int delete_index, random,halmaz_meret=recept_db;
    for(int i=0;i<recept_db;i++)
    {
        recept_halmaz[i]=receptek[i];
    }
    while(accept!='y')
    {
        srand(time(NULL));
        random = rand() % halmaz_meret;
        printf("Recept neve: %s\n", recept_halmaz[random].nev);
        printf("Tetszik ez a recept? (y/n):\n(-1 a megszakitas)\n");
        if(scanf(" %c", &accept) == '-1')
        {
            printf("A keresés megszakítva!\n");
            return;
        }

        delete_index=random;
        delete_one_from_tomb(delete_index, &recept_db, recept_halmaz);
        halmaz_meret--;
        if(halmaz_meret==0)
        {
            printf("Nincs további recept!\n");
            break;
        }
    }
    print_recipe(random);
}

void keres_1anyag()
{

}

void keres_tobbanyag()
{

}

void list_recipes()//összes recept kiírása
{
    int id;
    for(int i=0;i<recept_db;i++)
    {
        printf("%d. %s\n", receptek[i].id, receptek[i].nev);
    }
    printf("Adja meg a recept ID-ját a részletekhez:\n(-1 a megszakitas)\n");
    if(scanf("%d", &id) == -1)
    {
        printf("A keresés megszakítva!\n");
        return;
    }
    print_recipe(id);
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
        printf("8. Receptek listazasa\n");
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