#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct _Stack* Position;
typedef struct _Stack{
    float element;
    Position Next;
}_Stack;

int push(Position, float);
int pop(Position);
int evalPostfix(Position);
Position Alloc(void);

int main(){

    _Stack Head = {0, NULL};
    float result = evalPostfix(&Head);
    printf("%.2f", result);

    return 0;
}

Position Alloc(void){
    return (Position)malloc(sizeof(_Stack));
}

int push(Position P, float num){
    
    Position Q = Alloc();
    if(Q==NULL){
        printf("Error!");
        return EXIT_FAILURE;
    }

    Q->element = num;
    Q->Next = P->Next;
    P->Next = Q;

    return EXIT_SUCCESS;
}

int pop(Position P){

    Position Prev = Alloc();
    if(Prev==NULL){
        printf("Error!");
        return EXIT_FAILURE;
    }

    Prev = P;
    P = P->Next;
    float val = P->element;
    Prev->Next = P->Next;
    P->Next = NULL;
    free(P);

    return val;
}

int evalPostfix(Position P){
    
    FILE *fp = fopen("postfix.txt", "r");
    if(fp==NULL){
        printf("Error!");
        return EXIT_FAILURE;
    }
    float num, val1, val2, result, finalresult;
    int i, n;
    char expression[80];
    
    fgets(expression, sizeof(expression), fp);
    n = strlen(expression); 

    for(i=0; i<n; i++){
        while(isspace(expression[i])) i++; //skips whitespace read from file
        if (isdigit(expression[i])) {
            num = 0;
            while (i < n && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0'); // (-'0') turns ASCII value of expression[i] into real numeric value,
                i++;                                    // num*10 allows for multiple digit numbers,
            }                                           // i++ increments until it reaches an operator character or the next whitespace                                                               
            push(P, num);
            i--;  //fixes i++ from above while loop
        }
        else{
            val1 = pop(P);
            val2 = pop(P);
            switch(expression[i]){
                case '+': result = val2 + val1; break;
                case '-': result = val2 - val1; break;
                case '*': result = val2 * val1; break;
                case '/': result = val2 / val1; break;
                default:
                    printf("Error!");
                    return EXIT_FAILURE;
            }
            push(P, result);
        }
    }
    finalresult = pop(P);
    fclose(fp);

    return finalresult;
}