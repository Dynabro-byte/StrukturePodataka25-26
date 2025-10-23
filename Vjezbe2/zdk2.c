#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;
typedef struct _Person{
    char name[50];
    char surname[50];
    int birthYear;
    Position Next;
}_Person;

int PrintList(Position);
int InputStart(Position); 
int InputEnd(Position);   
Position Alloc(void);
Position Find(char [], Position);
Position FindPrevious(char [], Position);
int Erase(char [], Position);

int main(){

    _Person Head = {"", "", 0, NULL};
    Position temp = NULL;
    int n, i;
    char z;
    char x[20];

    printf("How many persons?\n");
    scanf("%d", &n);

    for(i=0; i<n; i++){
        printf("Options: S-input at start, E-input at end, O-no input\n");
        scanf(" %c", &z);
        while(getchar() != '\n'); //eliminates '\n' from buffer after scanf

        switch(z){
            case 'S':
            case 's':
            InputStart(&Head);
            PrintList(Head.Next);
            break;

            case 'E':
            case 'e':
            InputEnd(&Head);
            PrintList(Head.Next);
            break;

            case 'O':
            case 'o':
            return EXIT_SUCCESS;

            default:
            printf("Invalid option");
            break;
        }
    }

    printf("Find member?\n");
    scanf(" %c", &z);
    switch(z){
        case 'Y':
        case 'y':
        printf("Input surname of desired member:\n");
        scanf("%s", &x);
        temp=Find(x, &Head);
        if(temp==NULL){
            printf("Member does not exist.\n");
            return EXIT_FAILURE;
        }
        else printf("Member exists:\n\nName: %s\nSurname: %s\nYear of birth: %d\n\n", temp->name, temp->surname, temp->birthYear);
        break;

        case 'N':
        case 'n':
        break;
    }

    printf("Terminate member/member's? Y-yes, N-no\n");
    scanf(" %c", &z);
    switch(z){
        case 'Y':
        case 'y':
        printf("How many terminations?\n");
        scanf("%d", &n);
        for(i=0; i<n; i++){
            printf("Input surname of member designated for termination:\n");
            scanf("%s", &x);
            Erase(x, &Head);
            PrintList(Head.Next);
        }
        break;

        case 'N':
        case 'n':
        break;
    }
     
    PrintList(Head.Next);

    return 0;
}

Position Alloc(void){
    return (Position)malloc(sizeof(_Person));
}

int PrintList(Position P){
    
    printf("Printed list:\n\n");

    while(P != NULL){
        printf("Name: %s\nSurname: %s\nYear of birth: %d\n\n", P->name, P->surname, P->birthYear);
        P = P->Next;
    }

    return EXIT_SUCCESS;
}

int InputStart(Position P){

    Position Q = Alloc();

    if(Q==NULL){
        printf("Memory alloc. failed.");
        return EXIT_FAILURE;
    }

    printf("Name: ");
    fgets(Q->name, sizeof(Q->name), stdin); //skips without line 34
    Q->name[strcspn(Q->name, "\n")] = 0;    //eliminates '\n' from buffer after fgets
    printf("Surname: ");
    fgets(Q->surname, sizeof(Q->surname), stdin);
    Q->surname[strcspn(Q->surname, "\n")] = 0; //eliminates '\n' from buffer after fgets
    printf("Year: ");
    scanf("%d", &Q->birthYear);
    while(getchar() != '\n');   //eliminates '\n' from buffer after scanf
    if(Q->birthYear<0){
        printf("Invalid year.");
        free(Q);
        return EXIT_FAILURE;
    }
    
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

int InputEnd(Position P){

    Position Q = Alloc();

    if(Q==NULL){
        printf("Memory alloc. failed.");
        return EXIT_FAILURE;
    }

    while(P->Next != NULL){
        P=P->Next;
    }

    printf("Name: ");
    fgets(Q->name, sizeof(Q->name), stdin); //skips without line 34
    Q->name[strcspn(Q->name, "\n")] = 0;    //eliminates '\n' from buffer after fgets
    printf("Surname: ");
    fgets(Q->surname, sizeof(Q->surname), stdin);
    Q->surname[strcspn(Q->surname, "\n")] = 0; //eliminates '\n' from buffer after fgets
    printf("Year: ");
    scanf("%d", &Q->birthYear);
    while(getchar() != '\n');   //eliminates '\n' from buffer after scanf
    if(Q->birthYear<0){         //ensures only positive year input
        printf("Invalid year.");
        free(Q);
        return EXIT_FAILURE;
    }
    
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

Position Find(char S[20], Position P){

    while(P != NULL && strcmp(P->surname, S) != 0){
        P = P->Next;
    }
    
    return P;
}

Position FindPrevious(char S[20], Position P){

   Position Previous = P;
   P = P->Next;

   while(P != NULL && strcmp(P->surname, S) != 0){
        Previous=P;
        P=P->Next;
    }
   if(P==NULL) return NULL;

   return Previous;
}

int Erase(char S[20], Position P){

    Position temp=Alloc();

    P=FindPrevious(S, P);
    if(P==NULL) return EXIT_FAILURE;
    if(P != NULL){
        temp = P->Next;
        P->Next = temp->Next;
        temp=NULL;
        free(temp);
    }

    return EXIT_SUCCESS;
}
