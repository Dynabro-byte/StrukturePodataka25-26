#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _list List;
typedef struct _list *Position;
typedef struct _tree Tree;
typedef struct _tree *TreePosition;

struct _tree{
    char name[20];
    int population;
    TreePosition Right, Left;
    Position listHead;
};

struct _list{
    char name[20];
    int population;
    Position Next;
    TreePosition Listroot;
};

int ListMode(List);
int ParentSortedList(Position, char *, char *, int);
int ChildSortedList(Position, char *, char *, int);
int DeleteList(Position);
int OutputListMain(Position);
int OutputTreeMain(TreePosition);
int InOrder(TreePosition);
TreePosition TreeMode(TreePosition);
TreePosition ParentTreeInput(TreePosition, char *, char *, int);
TreePosition ChildTreeInput(TreePosition, char *, char *, int);
TreePosition DeleteTree(TreePosition);

int main(){

    List head = {"", 0, NULL, NULL};
    TreePosition root = NULL;
    int mode, flag = 1;

    while(flag){
        printf("Select a mode of work: 0-EXIT || 1-List as parent, bin. tree as child || 2-Bin. tree as parent, list as child\n");
        scanf("%d", &mode);
        switch(mode){
            case 0:
                printf("Program will terminate.\n");
                flag = 0;
                break;
            case 1:
                ListMode(head);
                break;
            case 2:
                root = TreeMode(root);
                if(root == NULL) printf("Bin. tree is empty.\n");
                break;
            default:
                printf("Invalid mode.\n");
                break;
        }
    }

    return EXIT_SUCCESS;
}

int ParentSortedList(Position Start, char *argname, char *argname2, int pop){

    if(Start == NULL) return EXIT_FAILURE;

    Position P = Start;
    Position Q = (Position)malloc(sizeof(List));
    if(Q == NULL){
        printf("Error in alloc.\n");
        return EXIT_FAILURE;
    }

    while(P->Next != NULL && strcmp(P->Next->name, argname) > 0){
        P = P->Next;
    }
    strcpy(Q->name, argname);
    Q->population = pop;
    Q->Listroot = NULL;
    Q->Listroot = ChildTreeInput(Q->Listroot, argname2, "", pop);
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

int ChildSortedList(Position Start, char *argname, char *argname2, int pop){

    if(Start == NULL){
        Start = (Position)malloc(sizeof(List));
        Start->Listroot = NULL;
        Start->Next = NULL;
    }

    Position P = Start;
    Position Q = (Position)malloc(sizeof(List));
    if(Q == NULL){
        printf("Error in alloc.\n");
        return EXIT_FAILURE;
    }

    while(P->Next != NULL && strcmp(P->Next->name, argname) > 0){
        P = P->Next;
    }
    
    strcpy(Q->name, argname);
    Q->population = pop;
    Q->Listroot = NULL;
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

TreePosition ParentTreeInput(TreePosition rootDummy, char *argname, char *argname2, int pop){

    if(rootDummy == NULL){

        rootDummy = (TreePosition)malloc(sizeof(Tree));
        rootDummy->Left = NULL;
        rootDummy->Right = NULL;
        rootDummy->listHead = NULL;
        ChildSortedList(rootDummy->listHead, "", argname2, pop);
        strcpy(rootDummy->name, argname);
        rootDummy->population = pop;

        return rootDummy;
    }
    else if(strcmp(rootDummy->name, argname) < 0){
        rootDummy->Right = ParentTreeInput(rootDummy->Right, argname, argname2, pop);
        return rootDummy;
    }
    else if(strcmp(rootDummy->name, argname) > 0){
        rootDummy->Left = ParentTreeInput(rootDummy->Left, argname, argname2, pop);
        return rootDummy;
    }

}

TreePosition ChildTreeInput(TreePosition rootDummy, char *argname, char *argname2, int pop){

    if(rootDummy == NULL){

        rootDummy = (TreePosition)malloc(sizeof(Tree));
        rootDummy->Left = NULL;
        rootDummy->Right = NULL;
        rootDummy->listHead = NULL;
        strcpy(rootDummy->name, argname);
        rootDummy->population = pop;

        return rootDummy;
    }
    else if(strcmp(rootDummy->name, argname) < 0){
        rootDummy->Right = ChildTreeInput(rootDummy->Right, argname, argname2, pop);
        return rootDummy;
    }
    else if(strcmp(rootDummy->name, argname) > 0){
        rootDummy->Left = ChildTreeInput(rootDummy->Left, argname, argname2, pop);
        return rootDummy;
    }

}

TreePosition DeleteTree(TreePosition rootDummy){

    if(rootDummy == NULL) return NULL;
    DeleteTree(rootDummy->Left);
    DeleteTree(rootDummy->Right);
    DeleteList(rootDummy->listHead);
    if(rootDummy->listHead == NULL) printf("List child is empty.\n");
    free(rootDummy);

    return NULL;
}

int DeleteList(Position Start){
    
    if(Start == NULL) return EXIT_FAILURE;
    Position temp;

    while(Start->Next != NULL){
        Start->Next->Listroot = DeleteTree(Start->Next->Listroot);
        if(Start->Next->Listroot == NULL) printf("Bin. tree child is empty.\n");
        temp = Start->Next;
        Start->Next = temp->Next;
        temp->Next = NULL;
        free(temp);
    }

    return EXIT_SUCCESS;
}

int OutputTreeMain(TreePosition rootDummy){

    if(rootDummy == NULL) return EXIT_SUCCESS;
    OutputTreeMain(rootDummy->Left);
    printf("Country name: %s\n", rootDummy->name);
    Position P = rootDummy->listHead;
    while(P != NULL){
        printf("City name: %s || Population: %d\n", P->name, P->population);
        P = P->Next;
    }
    OutputTreeMain(rootDummy->Right);

    return EXIT_SUCCESS;
}

int OutputListMain(Position Start){

    Position P = Start;

    printf("Country name: %s\n", P->name);
    while(P != NULL){
        InOrder(P->Listroot);
        P = P->Next;
    }
    
    return EXIT_SUCCESS;
}

int InOrder(TreePosition rootDummy){

    if(rootDummy == NULL) return EXIT_SUCCESS;
    InOrder(rootDummy->Left);
    printf("City name: %s || Population: %d\n", rootDummy->name, rootDummy->population);
    InOrder(rootDummy->Right);

    return EXIT_SUCCESS;
}

int ListMode(List head){

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

        while(!feof(cities)){
            fscanf(cities, "%s %d", cityName, &population);
            ParentSortedList(&head, countryName, cityName, population);
        }
        fclose(cities);
    }
    fclose(countries);;

    OutputListMain(head.Next);
    DeleteList(&head);
    if(head.Next == NULL) printf("List is empty.\n");

    return EXIT_SUCCESS;
}

TreePosition TreeMode(TreePosition rootDummy){

    char *countryName = (char *)malloc(sizeof(char)*20);
    char *cityPath = (char *)malloc(sizeof(char)*20);
    char *cityName = (char *)malloc(sizeof(char)*20);
    int population;

    FILE *countries = fopen("drzave.txt", "r");
    if(countries == NULL){
        printf("Error in opening file.\n");
        return NULL;
    }

    while(!feof(countries)){

        fscanf(countries, "%s %s", countryName, cityPath);
        FILE *cities = fopen(cityPath, "r");
        if(cities == NULL){
            printf("Error in opening file.\n");
            return NULL;
        }

        while(!feof(cities)){
            fscanf(cities, "%s %d", cityName, &population);
            rootDummy = ParentTreeInput(rootDummy, countryName, cityName, population);
        }
        fclose(cities);
    }
    fclose(countries);
    free(countryName);
    free(cityPath);
    free(cityName);
    OutputTreeMain(rootDummy);
    rootDummy = DeleteTree(rootDummy);

    return rootDummy;
}