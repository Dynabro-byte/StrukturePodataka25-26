#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct _directory *dirPosition;
typedef struct _directory{
    char name[MAX];
    dirPosition Next;
    dirPosition subDirPosition;
}Directory;

typedef struct _stack *stackPosition;
typedef struct _stack{
    stackPosition Next;
    dirPosition dirLevel;
}Stack;

int displayPaths(dirPosition);
int createDisk(dirPosition, stackPosition);
int push(dirPosition, stackPosition);
int md(dirPosition, char *);
int cd(dirPosition, stackPosition, char *);
int cdDotDot(stackPosition);
int dir(dirPosition);
int deleteStack(stackPosition);
int deleteDirectory(dirPosition);
int deleteSubDirectory(dirPosition);

int main(){

    Directory directoryHead = {"", NULL, NULL};
    Stack stackHead = {NULL, NULL};
    createDisk(&directoryHead, &stackHead);
    int flag = 1;
    int command;
    char *input = (char *)malloc(MAX*sizeof(char));
    
    while(flag){
        printf("Select a number corresponding to a command:\n1-md\n2-cd\n3-cd..\n4-dir\n5-EXIT\n");
        scanf("%d", &command);
        switch(command){
            case 1:
                printf("Name of new directory:\n");
                scanf("%s", input);
                md(stackHead.Next->dirLevel, input);
                break;
            case 2:
                printf("Change directory to:\n");
                scanf("%s", input);
                cd(stackHead.Next->dirLevel, &stackHead, input);
                break;
            case 3:
                cdDotDot(&stackHead);
                printf("Returned to:\n%s\n", stackHead.Next->dirLevel->name);
                break;
            case 4:
                dir(stackHead.Next->dirLevel);
                break;
            case 5:
                displayPaths(directoryHead.Next);
                deleteStack(&stackHead);
                deleteDirectory(&directoryHead);
                displayPaths(directoryHead.Next);
                flag = 0;
                break;
            default:
                printf("Invalid command. Menu will be displayed again.\n");
                break;         
        }
    }

    return 0;
}

int createDisk(dirPosition P, stackPosition Q){

    dirPosition Start = P;
    stackPosition stackStart = Q;
    char *p = (char *)malloc(MAX*sizeof(char));
    dirPosition P1 = (dirPosition)malloc(sizeof(Directory));
    if(P1 == NULL){
        printf("ERROR");
        return -1;
    }
    
    printf("Name of disk:\n");
    scanf("%s", p);
    strcpy(P1->name, p);
    while(Start->Next != NULL){
        Start = Start->Next;
    }
    
    P1->Next = Start->Next;
    Start->Next = P1;
    P1->subDirPosition = NULL;
    push(P1, stackStart);
    free(p);
    
    return 0;
}

int push(dirPosition P, stackPosition Q){

    stackPosition Q1 = (stackPosition)malloc(sizeof(Stack));
    if(Q1 == NULL){
        printf("ERROR");
        return -1;
    }
    
    Q1->Next = Q->Next;
    Q->Next = Q1;
    Q1->dirLevel = P;

    return 0;
}

int md(dirPosition P, char *Name){
    
   dirPosition Parent = P;
   dirPosition newEl = (dirPosition)malloc(sizeof(Directory));
   if(newEl == NULL){
       printf("ERROR");
       return -1;
   }
   
   strcpy(newEl->name, Name);
   newEl->Next = Parent->subDirPosition;
   Parent->subDirPosition = newEl;
   newEl->subDirPosition = NULL;
   
   return 0;
}

int cd(dirPosition Start, stackPosition stackStart, char *Name){

    dirPosition P = Start->subDirPosition;
    int tracker = 0;
    printf("C://");
    while(P != NULL){
        if(strcmp(P->name, Name) == 0){
            printf("%s//", P->name);
            push(P, stackStart);
            tracker++;
        }
        P = P->Next;
    }
    if(tracker == 0){
        printf("Directory does not exist.");
        return -1;
    }
    printf("\n");

    return 0;
}

int cdDotDot(stackPosition stackStart){

    stackPosition temp = stackStart->Next;
    stackStart->Next = temp->Next;
    temp->Next = NULL;
    temp->dirLevel = NULL;
    free(temp);

    return 0;
}

int dir(dirPosition P){

    dirPosition PsubDir = NULL;
    if(P->subDirPosition != NULL){
        PsubDir = P->subDirPosition;
        while(PsubDir != NULL){
            printf("%s//", PsubDir->name);
            dir(PsubDir);
            PsubDir = PsubDir->Next;
        }
    }

    return 0;
}

int deleteStack(stackPosition Start){

    stackPosition temp;
    while(Start->Next != NULL){
        temp = Start->Next;
        Start->Next = temp->Next;
        temp->Next = NULL;
        temp->dirLevel = NULL;
        free(temp);
    }

    return 0;
}

int deleteDirectory(dirPosition Start){

    dirPosition temp;
    while(Start->Next != NULL){
        temp = Start->Next;
        deleteSubDirectory(temp->subDirPosition);
        Start->Next = temp->Next;
        temp->Next = NULL;
        temp->subDirPosition = NULL;
        free(temp);
    }

    return 0;
}

int deleteSubDirectory(dirPosition Start){
    
    dirPosition currentSub = Start;
    if(currentSub == NULL) return 0;
    dirPosition nextcurrentSub = NULL;
    dirPosition temp;
    
    if(currentSub->subDirPosition != NULL){
        nextcurrentSub = currentSub->subDirPosition;
        while(nextcurrentSub->Next != NULL){
            deleteSubDirectory(nextcurrentSub);
            temp = nextcurrentSub->Next;
            nextcurrentSub->Next = temp->Next;
            temp->Next = NULL;
            free(temp);
        }
    }

    return 0;
}

int displayPaths(dirPosition P){

    dirPosition Start = P;
    if(Start == NULL){
        printf("Empty disk.");
        return 0;
    }
    
    while(Start != NULL){
        printf("%s//");
        dir(Start);
        Start = Start->Next;
    }

    return 0;
}