#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;
typedef struct _Person{
    char name[20];
    char surname[20];
    int birthYear;
    Position Next;
}_Person;

int PrintList(Position);
int SortList(Position);
int Input(Position);
int InputAfter(char [], Position);
int InputBefore(char [], Position);
int InputStart(Position); 
int InputEnd(Position);   
Position Alloc(void);
Position Find(char [], Position);
Position FindPrevious(char [], Position);
int Erase(char [], Position);
int ReadFromFile(Position);
int WriteIntoFile(Position);

int main(){

    _Person Head = {"", "", 0, NULL};
    Position temp = NULL;
    int n, i;
    char z;
    char x[20];

    printf("Read list from file? Y-yes, N-no\n");
    scanf(" %c", &z);

    switch(z){
        case 'Y':
        case 'y':
        ReadFromFile(&Head);
        SortList(&Head);
        PrintList(Head.Next);
        return EXIT_SUCCESS;

        case 'N':
        case 'n':
        break;

        default:
        printf("Invalid option!");
        break;
    }

    printf("How many people to input?\n");
    scanf("%d", &n);

    for(i=0; i<n; i++){
        printf("Options: S-input at start, E-input at end, A-input after member, B-input before member, O-no input\n");
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

            case 'A':
            case 'a':
            printf("Input surname of desired member:\n");
            scanf("%s", &x);
            while(getchar() != '\n'); //eliminates '\n' from buffer after scanf
            InputAfter(x, Head.Next);
            PrintList(Head.Next);
            break;

            case 'B':
            case 'b':
            printf("Input surname of desired member:\n");
            scanf("%s", &x);
            while(getchar() != '\n'); //eliminates '\n' from buffer after scanf
            InputBefore(x, Head.Next);
            PrintList(Head.Next);
            break;

            case 'O':
            case 'o':
            return EXIT_SUCCESS;

            default:
            printf("Invalid option!");
            return EXIT_FAILURE;
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

        default:
        printf("Invalid option!");
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

        default:
        printf("Invalid option!");
        break;
    }
    
    SortList(&Head);
    PrintList(Head.Next);

    printf("Write list into file? Y-yes, N-no\n");
    scanf(" %c", &z);

    switch(z){
        case 'Y':
        case 'y':
        WriteIntoFile(Head.Next);
        break;

        case 'N':
        case 'n':
        break;

        default:
        printf("Invalid option!");
        break;
    }

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

int Input(Position P){

    printf("Name: ");
    fgets(P->name, sizeof(P->name), stdin); //skips without lineS 41 and 60
    P->name[strcspn(P->name, "\n")] = 0;    //eliminates '\n' from buffer after fgets
    printf("Surname: ");
    fgets(P->surname, sizeof(P->surname), stdin);
    P->surname[strcspn(P->surname, "\n")] = 0; //eliminates '\n' from buffer after fgets
    printf("Year: ");
    scanf("%d", &P->birthYear);
    while(getchar() != '\n');   //eliminates '\n' from buffer after scanf
    if(P->birthYear<0){         //ensures only positive year input
        printf("Invalid year.");
        free(P);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int InputStart(Position P){

    Position Q = Alloc();
    Q->Next = NULL;

    if(Q==NULL){
        printf("Memory alloc. failed.");
        return EXIT_FAILURE;
    }

    Input(Q);
    
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

int InputEnd(Position P){

    Position Q = Alloc();
    Q->Next = NULL;

    if(Q==NULL){
        printf("Memory alloc. failed.");
        return EXIT_FAILURE;
    }

    while(P->Next != NULL){
        P=P->Next;
    }

    Input(Q);
    
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

int InputAfter(char S[20], Position P){

    Position Q = Alloc();
    Q->Next = NULL;

    if(Q==NULL){
        printf("Memory alloc. failed.");
        return EXIT_FAILURE;
    }

    P = Find(S, P);
    Input(Q);
    
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

int InputBefore(char S[20], Position P){

    Position Q = Alloc();
    Q->Next = NULL;

    if(Q==NULL){
        printf("Memory alloc. failed.");
        return EXIT_FAILURE;
    }

    P = FindPrevious(S, P);
    if(P==NULL) return EXIT_FAILURE;
    Input(Q);
    
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
        Previous = P;
        P = P->Next;
    }
   if(P==NULL) return NULL;

   return Previous;
}

int Erase(char S[20], Position P){

    Position temp = Alloc();
    temp->Next = NULL;

    P=FindPrevious(S, P);
    if(P==NULL) return EXIT_FAILURE;
    if(P != NULL){
        temp = P->Next;
        P->Next = temp->Next;
        temp->Next=NULL;
        free(temp);
    }

    return EXIT_SUCCESS;
}

int SortList(Position P){

    Position temp = NULL, eol = NULL, Q_Prev = NULL, Q = NULL;

    while(P->Next != eol){
        
        Q_Prev = P;
        Q = P->Next;
        while(Q->Next != eol){

            if(strcmp(Q->surname, Q->Next->surname) > 0){
                temp = Q->Next;
                Q_Prev->Next = temp;
                Q->Next = temp->Next;
                temp->Next = Q;
                Q = temp;
            }
            else{
                Q_Prev = Q;
                Q = Q->Next;
            }

        }

        eol = Q;
    }

    return EXIT_SUCCESS;
}

int ReadFromFile(Position P){

    FILE *fp = fopen("peopler.txt", "r");
    Position Q = NULL;
    int i, n = 1;

    if(fp==NULL){
        printf("Error!");
        return EXIT_FAILURE;
    }

    while(!feof(fp)){
        if(fgetc(fp) == '\n') n++;
    }
    rewind(fp);

    for(i=0; i<n; i++){
        Q = Alloc();
        fscanf(fp, "%s %s %d", Q->name, Q->surname, &Q->birthYear);
        Q->Next = P->Next;
        P->Next = Q;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int WriteIntoFile(Position P){

    FILE *fp = fopen("peoplew.txt", "w");

    if(fp==NULL){
        printf("Error!");
        return EXIT_FAILURE;
    }

    while(P != NULL){
        fprintf(fp, "%s\t %s\t %d\n", P->name, P->surname, P->birthYear);
        P = P->Next;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
