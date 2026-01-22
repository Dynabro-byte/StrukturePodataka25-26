#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _city_tree CityTree;
typedef struct _city_tree *TreePosition;
typedef struct _country_list CountryList;
typedef struct _country_list *Position;
typedef struct _hash_table Hash;

struct _city_tree{
    char name[20];
    int population;
    TreePosition Left, Right;
};

struct _country_list{
    char name[20];
    Position Next;
    TreePosition listroot;
};

struct  _hash_table{
    int size;
    Position hashtable[11];
};

int HashFunction(char *, int);
int InitHash(Hash *);
int addListtoHash(Hash *, char *);
int addTreetoList(Hash *, char *, char *, int);
TreePosition TreeInput(TreePosition, char *, int);
TreePosition DeleteTree(TreePosition);
int Inorder(TreePosition);
int Output(Hash *, char *);

int main(){

    Hash hash;
    InitHash(&hash);

    char *countryName = (char *)malloc(sizeof(char)*20);
    char *cityPath = (char *)malloc(sizeof(char)*20);
    char *cityName = (char *)malloc(sizeof(char)*20);
    int population;

    FILE *countries = fopen("drzave.txt", "r");
    if(countries == NULL){
        printf("Error in opening file.\n");
        return EXIT_FAILURE;
    }

    while(!feof(countries)){

        fscanf(countries, "%s %s", countryName, cityPath);
        FILE *cities = fopen(cityPath, "r");
        if(cities == NULL){
            printf("Error in opening file.\n");
            return EXIT_FAILURE;
        }
        
        addListtoHash(&hash, countryName);
        while(!feof(cities)){
            fscanf(cities, "%s %d", cityName, &population);
            addTreetoList(&hash, countryName, cityName, population);
        }
        fclose(cities);
    }
    fclose(countries);
    fgets(countryName, 20, stdin);
    Output(&hash, countryName);

    return EXIT_SUCCESS;
}

int InitHash(Hash *h){

    h->size = 11;
    for(int i = 0; i < h->size; i++){
        h->hashtable[i] = NULL;
    }

    return EXIT_SUCCESS;
}

int HashFunction(char *countryName, int tableSize){

    int sum = 0;
    for(int i = 0; i < 5; i++){
        sum += countryName[i];
    }

    return sum % tableSize;
}

int addListtoHash(Hash *H, char *country){
    
    int key = HashFunction(country, H->size);
    if(H->hashtable[key] == NULL){

        H->hashtable[key] = (Position)malloc(sizeof(CountryList));
        strcpy(H->hashtable[key]->name, country);
        H->hashtable[key]->listroot = NULL;
        H->hashtable[key]->Next = NULL;

    }
    else{

        Position P = H->hashtable[key];
        Position Q = (Position)malloc(sizeof(CountryList));
        while(P->Next != NULL){
            P = P->Next;
        }
        Q->Next = P->Next;
        P->Next = Q;

        strcpy(Q->name, country);
        Q->listroot = NULL;
    }

    return EXIT_SUCCESS;
}

int addTreetoList(Hash *H, char *country, char *city, int pop){

    int key = HashFunction(country, H->size);
    H->hashtable[key]->listroot = TreeInput(H->hashtable[key]->listroot, city, pop);

    return EXIT_SUCCESS;
}

TreePosition TreeInput(TreePosition rootDummy, char* city, int pop){

    if(rootDummy == NULL){

        rootDummy = (TreePosition)malloc(sizeof(CityTree));
        rootDummy->Left = NULL;
        rootDummy->Right = NULL;
        strcpy(rootDummy->name, city);
        rootDummy->population = pop;

        return rootDummy;
    }
    else if(rootDummy->population < pop){
        rootDummy->Right = TreeInput(rootDummy->Right, city, pop);
        return rootDummy;
    }
    else if(rootDummy->population > pop){
        rootDummy->Left = TreeInput(rootDummy->Left, city, pop);
        return rootDummy;
    }

}

TreePosition DeleteTree(TreePosition rootDummy){

    if(rootDummy == NULL) return NULL;
    DeleteTree(rootDummy->Left);
    DeleteTree(rootDummy->Right);
    free(rootDummy);

    return NULL;
}

int InOrder(TreePosition rootDummy){

    if(rootDummy == NULL) return EXIT_SUCCESS;
    InOrder(rootDummy->Left);
    printf("City name: %s || Population: %d\n", rootDummy->name, rootDummy->population);
    InOrder(rootDummy->Right);

    return EXIT_SUCCESS;
}

int Output(Hash *H, char *country){

    int key = HashFunction(country, H->size);
    printf("Country: %s\n", country);
    InOrder(H->hashtable[key]->listroot);

    return EXIT_SUCCESS;
}
