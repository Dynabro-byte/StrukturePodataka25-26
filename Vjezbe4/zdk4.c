#include <stdio.h>
#include <stdlib.h>
#define CRT_SECURE_NO_WARNINGS

typedef struct poly* Position;
typedef struct poly {
        int coefficient;
        int power;
        Position Next;
}Poly;

int fileReader(Position, int);
int add(Position, Position,Position);
int multiply(Position, Position, Position);
int printpoly(Position);

int main() {
    Poly Head = {0,0,NULL};
    Poly Head2 = {0,0,NULL};
    Poly firstP = Head;
    Poly secondP = Head;
    int FLAG;

    FLAG=fileReader(&firstP, 1);
    if(FLAG == EXIT_FAILURE){
         return EXIT_FAILURE;
    }
    FLAG=fileReader(&secondP, 2);
    if(FLAG == EXIT_FAILURE){
        return EXIT_FAILURE;
    }

    add(&firstP, &secondP, &Head);
    multiply(&firstP, &secondP, &Head2);

    printpoly(&firstP);
    printpoly(&secondP);
    printpoly(&Head);
    printpoly(&Head2);

    return EXIT_SUCCESS;
}
int multiply(Position First, Position Second, Position Start){
    Position Q1 = First->Next;
    Position Q2 = Second->Next;
    Position temp = Start;

    int max, tempCoefficient1, tempCoefficient2;
    max = Q2->power + Q1->power;
    int copyMax = max;
    for(copyMax; copyMax > -1; copyMax--){
        Position Q = (Position)malloc(sizeof(Poly));
        if(Q == NULL){
            printf("Error!");
            return EXIT_FAILURE;
        }
        while(temp->Next != NULL){
            temp = temp->Next;
        }
        Q->coefficient = 0;
        Q->power = copyMax;
        Q->Next = temp->Next;
        temp->Next = Q;
    }

    for(Q2 = Second->Next; Q2 != NULL; Q2 = Q2->Next){
        tempCoefficient2 = Q2->coefficient;
        for(Q1 = First->Next; Q1 != NULL; Q1 = Q1->Next){
            tempCoefficient1 = Q1->coefficient;
            int mul = tempCoefficient1 * tempCoefficient2;
            int tempPower = Q2->power + Q1->power;
            for(temp = Start->Next; temp != NULL; temp = temp->Next){
                if(temp->power == tempPower){
                    temp->coefficient = temp->coefficient + mul;
                }
            }
            mul = 0;
            tempPower = 0;
        }
    }

    return EXIT_SUCCESS;
}
int add(Position First, Position Second, Position Start){

    Position Q1 = First->Next;
    Position Q2 = Second->Next;
    Position temp = Start;
    int max;

    if(Q1->power >= Q2->power){
        max = Q1->power;
    }
    else max = Q2->power;

    for(max; max > -1; max--){
        int firstNum = 0, secondNum = 0;
        for(Q1 = First->Next; Q1->Next != NULL; Q1 = Q1->Next){
            if(max == Q1->power){
                firstNum = Q1->coefficient;
                break;
            }
        }
        for(Q2 = Second->Next; Q2->Next != NULL; Q2 = Q2->Next){
            if(max == Q2->power){
                secondNum = Q2->coefficient;
                break;
            }
        }
        int added = firstNum + secondNum;
        if(added == 0){}
        else {
            Position Q = (Position)malloc(sizeof(Poly));
            if(Q == NULL){
                printf("Error!");
                return EXIT_FAILURE;
            }
            while(temp->Next != NULL){
                temp = temp->Next;
            } 
            Q->coefficient = added;
            Q->power = max;
            Q->Next = temp->Next;
            temp->Next = Q;
        }
    }

    return EXIT_SUCCESS;
}
int fileReader(Position Start, int num){

    Position temp = Start;
    Position P;
    FILE* fp;

    if(num == 1){
        fp = fopen("poly1.txt", "r");
    }
    else fp = fopen("poly2.txt", "r");
        
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    char* c = (char*)malloc(sizeof(char) * 10);
    int tempCoefficient, tempPower;
    while(feof(fp) == 0){
        Position Q = (Position)malloc(sizeof(Poly));
        if(Q == NULL){
            printf("G");
            return EXIT_FAILURE;
        }

        fscanf(fp, "%s", c);
        if(sscanf(c, "%d", &tempCoefficient) == 0){
            return EXIT_FAILURE;
        }
        sscanf(c, "%d", &tempCoefficient);

        fscanf(fp, "%s", c);
        if(sscanf(c, "%d", &tempPower) == 0){
                return EXIT_FAILURE;
        }
        sscanf(c, "%d", &tempPower);

        for(P = temp; P->Next != NULL; P = P->Next){
            if(tempPower > P->Next->power){
                break;
            }
        }
        Q->coefficient = tempCoefficient;
        Q->power = tempPower;
        Q->Next = P->Next;
        P->Next = Q;
    }
    free(c);
    fclose(fp);

    return EXIT_SUCCESS;
}
int printpoly(Position Start){

    Position Q = Start->Next;
    while(Q != NULL){   
        printf("%dx%d ", Q->coefficient, Q->power);
        Q = Q->Next;
    }
    Q = Start;
    Position temp;
    while(Q->Next != NULL){        
        temp = Q->Next;
        Q->Next = temp->Next; 
        temp->Next = NULL;
        free(temp);
    }
    printf("\n");

    return EXIT_SUCCESS;
}