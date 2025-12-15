#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _bintree *TreePosition;
typedef struct _bintree{
    int element;
    TreePosition Left, Right;
}Tree;

TreePosition TreeInput(TreePosition, int);
TreePosition DeleteTreeNode(TreePosition, int);
TreePosition DeleteTree(TreePosition);
TreePosition FindMax(TreePosition);
int FindNode(TreePosition, int);
int InOrder(TreePosition);
int PostOrder(TreePosition);
int PreOrder(TreePosition);
int LevelOrder(TreePosition);
int TreeHeight(TreePosition);
int CurrentLevel(TreePosition, int);

int main(){

    TreePosition root = NULL;
    int flag = 1;
    int command;
    int value;
    
    while(flag){
        printf("Enter a number: 0-EXIT || 1-Input into tree || 2-Delete a node || 3-Find a node || 4-Output in all variations\n");
        scanf("%d", &command);
        switch(command){
            case 0:
                printf("Program will terminate.\n");
                flag = 0;
                break;
            case 1:
                printf("Enter a value to add to the binary tree:\n");
                scanf("%d", &value);
                root = TreeInput(root, value);
                break;
            case 2:
                printf("Choose a value to delete from the binary tree:\n");
                scanf("%d", &value);
                root = DeleteTreeNode(root, value);
                break;
            case 3:
                printf("Choose a value to find in the binary tree:\n");
                scanf("%d", &value);
                if(FindNode(root, value)) printf("Node containing element %d exists within binary tree.\n", value);
                else printf("Node does not exist within binary tree.\n");
                break;
            case 4:
                printf("Post-order output:\n"); PostOrder(root); printf("\n");
                printf("Pre-order output:\n"); PreOrder(root); printf("\n");
                printf("In-order output:\n"); InOrder(root); printf("\n");
                printf("Level-order output:\n"); LevelOrder(root); printf("\n");
                break;
            default:
                printf("Invalid command. Try again.\n");
                break;
        }
    }
    root = DeleteTree(root);
    if(root == NULL) printf("Binary tree is empty.\n");

    return EXIT_SUCCESS;
}

int LevelOrder(TreePosition rootDummy){

    if(rootDummy == NULL) return EXIT_FAILURE;
    int i;
    int height = TreeHeight(rootDummy);
    for(i = 1; i<=height; i++){
        CurrentLevel(rootDummy, i);
    }
    
    return EXIT_SUCCESS;
}

int CurrentLevel(TreePosition rootDummy, int level){

    if(rootDummy == NULL) return EXIT_FAILURE;
    if(level == 1){
        printf("%d ", rootDummy->element);
    }
    else if(level > 1){
        CurrentLevel(rootDummy->Left, level - 1);
        CurrentLevel(rootDummy->Right, level - 1);
    }

    return EXIT_SUCCESS;
}

int TreeHeight(TreePosition rootDummy){

    if(rootDummy == NULL){
        return 0;
    }
    else{
        int lheight = TreeHeight(rootDummy->Left);
        int rheight = TreeHeight(rootDummy->Right);
        if(lheight > rheight){
            return (lheight + 1);
        }
        else return (rheight + 1);
    }
}

int InOrder(TreePosition rootDummy){

    if(rootDummy == NULL) return EXIT_SUCCESS;
    InOrder(rootDummy->Left);
    printf("%d ", rootDummy->element);
    InOrder(rootDummy->Right);

    return EXIT_SUCCESS;
}

int PostOrder(TreePosition rootDummy){

    if(rootDummy == NULL) return EXIT_SUCCESS;
    PostOrder(rootDummy->Left);
    PostOrder(rootDummy->Right);
    printf("%d ", rootDummy->element);

    return EXIT_SUCCESS;
}

int PreOrder(TreePosition rootDummy){

    if(rootDummy == NULL) return EXIT_SUCCESS;
    printf("%d ", rootDummy->element);
    PreOrder(rootDummy->Left);
    PreOrder(rootDummy->Right);

    return EXIT_SUCCESS;
}

int FindNode(TreePosition rootDummy, int value){

    if(rootDummy == NULL) return 0;
    if(rootDummy->element == value) return 1;
    int found1 = FindNode(rootDummy->Left, value);
    if(found1) return 1;
    int found2 = FindNode(rootDummy->Right, value);
    if(found2) return 1;

    return found2;
}

TreePosition TreeInput(TreePosition rootDummy, int value){

    if(rootDummy == NULL){
        rootDummy = (TreePosition)malloc(sizeof(Tree));
        rootDummy->Left = NULL;
        rootDummy->Right = NULL;
        rootDummy->element = value;
        return rootDummy;
    }
    else if(value < rootDummy->element){
        rootDummy->Left = TreeInput(rootDummy->Left, value);
        return rootDummy;
    }
    else if(value > rootDummy->element){
        rootDummy->Right = TreeInput(rootDummy->Right, value);
        return rootDummy;
    }
    else{
        printf("Variable value is equal to element in tree node. No new node will be created.\n");
        rootDummy->element = value;
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

TreePosition DeleteTreeNode(TreePosition rootDummy, int value){

    TreePosition temp = NULL;
    if(rootDummy == NULL){
        return NULL;
    }
    else if(value < rootDummy->element){
        rootDummy->Left = DeleteTreeNode(rootDummy->Left, value);
    }
    else if(value > rootDummy->element){
        rootDummy->Right = DeleteTreeNode(rootDummy->Right, value);
    }
    else{
        if(rootDummy->Left != NULL && rootDummy->Right != NULL){
            temp = FindMax(rootDummy->Left);
            rootDummy->element = temp->element;
            rootDummy->Left = DeleteTreeNode(rootDummy->Left, temp->element);
        }
        else{
            temp = rootDummy;
            if(rootDummy->Left != NULL){
                rootDummy = rootDummy->Left;
            }
            else rootDummy = rootDummy->Right;
            free(temp);
        }
    }

    return rootDummy;
}

TreePosition FindMax(TreePosition rootDummy){

    if(rootDummy == NULL) return NULL;
    while(rootDummy->Right != NULL){
        rootDummy = rootDummy->Right;
    }

    return rootDummy;
}