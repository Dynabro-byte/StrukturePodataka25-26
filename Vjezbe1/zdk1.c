#include <stdio.h>
#include <malloc.h>

typedef struct{
    char ime[50];
    char prezime[50];
    int apsbod;
    float relbod;
}_Student;

int PrebrojStud(int);
int Ucitaj(int, _Student *);
int Ispis(int, _Student *);

int main(){

    int br;
    _Student *Stud;

    br=PrebrojStud(0);
    Stud=(_Student *)malloc(br*sizeof(_Student));

    Ucitaj(br, Stud);
    Ispis(br, Stud);
    
    return 0;
}

int PrebrojStud(int n){

    FILE *fp;

    fp=fopen("studenti.txt", "r");

    while(!feof(fp)){
        if(fgetc(fp) == '\n') n++;
    }

    fclose(fp);

    return n+1;     //+1 da uhvati posljednju liniju od studenti.txt
}

int Ucitaj(int n, _Student *S){

    FILE *fp;
    int i;

    fp=fopen("studenti.txt", "r");

    for(i=0; i<n; i++){
        fscanf(fp, "%s %s %d", S[i].ime, S[i].prezime, &S[i].apsbod);
    }

    fclose(fp);

    return 0;
}

int Ispis(int n, _Student *S){

    int i;
    int maxBod=50;

    for(i=0; i<n; i++){
        S[i].relbod = ((float)S[i].apsbod / maxBod)*100;
        printf("Ime: %s\tPrezime: %s", S[i].ime, S[i].prezime);
        printf("\tApsolutni bodovi: %d\tRelativni bodovi: %.2f%%\n", S[i].apsbod, S[i].relbod);
    }

    return 0;
}