#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

typedef struct Tree* TreePosition;
typedef struct Tree{
    int element;
    TreePosition Left, Right;
}Tree;

TreePosition DeleteTree(TreePosition);
TreePosition TreeInput(TreePosition, int);
TreePosition Menu(TreePosition);
int RNG();
int InOrderFile(TreePosition, FILE *);
int Replace(TreePosition);

int main(){

    TreePosition root = NULL;
    root = Menu(root);
    root = DeleteTree(root);
    if(root == NULL) printf("Binary tree is empty.\n");

    return EXIT_SUCCESS;
}

TreePosition DeleteTree(TreePosition rootDummy){

    if(rootDummy == NULL) return NULL;
    DeleteTree(rootDummy->Left);
    DeleteTree(rootDummy->Right);
    free(rootDummy);

    return NULL;
}

TreePosition TreeInput(TreePosition rootDummy, int value){

    if(rootDummy == NULL){
        rootDummy = (TreePosition)malloc(sizeof(Tree));
        rootDummy->Left = NULL;
        rootDummy->Right = NULL;
        rootDummy->element = value;
        return rootDummy;
    }
    else if(value >= rootDummy->element){
        rootDummy->Left = TreeInput(rootDummy->Left, value);
        return rootDummy;
    }
    else if(value < rootDummy->element){
        rootDummy->Right = TreeInput(rootDummy->Right, value);
        return rootDummy;
    }
    
}

int Replace(TreePosition rootDummy){

    if(rootDummy == NULL) return 0;
    int currentVal = rootDummy->element;
    rootDummy->element = Replace(rootDummy->Left) + Replace(rootDummy->Right);

    return currentVal + rootDummy->element;
}

int InOrderFile(TreePosition rootDummy, FILE *fp){

    if(rootDummy == NULL) return EXIT_SUCCESS;
    InOrderFile(rootDummy->Left, fp);
    fprintf(fp, "%d ", rootDummy->element);
    InOrderFile(rootDummy->Right, fp);

    return EXIT_SUCCESS;
}

int RNG(){

    int maxrange = 90;
    int minrange = 10;

    return (rand() % (maxrange + 1 - minrange)) + minrange;
}

TreePosition Menu(TreePosition rootDummy){

    int command, i, flag = 1;
    int samplearray[SIZE] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};

    FILE *fp = fopen("inorder.txt", "w");
    if(fp == NULL){
        printf("File was not opened.\n");
        return NULL;
    }

    while(flag){
        printf("Select a command: 0-EXIT || 1-Create bin. tree from existing array || 2-Modify bin. tree with Replace func. || ");
        printf("3-Create bin. tree using RNG || 4-Flush current bin. tree\n");
        scanf("%d", &command);
        switch(command){
            case 0:
                printf("Program will terminate.\n");
                flag = 0;
                break;
            case 1:
                printf("Sample array will be inserted into the bin. tree.\n");
                for(i = 0; i < SIZE; i++){
                    rootDummy = TreeInput(rootDummy, samplearray[i]);
                }
                InOrderFile(rootDummy, fp);
                fprintf(fp, "\n");
                break;
            case 2:
                printf("Bin. tree will be modified.\n");
                if(rootDummy != NULL){
                    rootDummy->element = Replace(rootDummy);
                    InOrderFile(rootDummy, fp);
                    fprintf(fp, "\n");
                }
                else printf("Bin. tree does not exist.\n");
                break;
            case 3:
                printf("Random numbers will be inserted into the bin. tree.\n");
                srand(time(NULL));
                for(i = 0; i < SIZE; i++){
                    rootDummy = TreeInput(rootDummy, RNG());
                }
                InOrderFile(rootDummy, fp);
                fprintf(fp, "\n");
                break;
            case 4:
                rootDummy = DeleteTree(rootDummy);
                if(rootDummy == NULL) printf("Binary tree is empty.\n");
                break;
            default:
                printf("Invalid command.\n");
                break;
        }
    }
    fclose(fp);

    return rootDummy;
}