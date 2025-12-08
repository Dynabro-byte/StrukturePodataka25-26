#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS
#define EXIT_FAILURE -1

typedef struct _date* DatePosition;
typedef struct _date{
    int year;
    int month;
    int day;
} Date;
typedef struct _item* ItemPosition;
typedef struct _item{
    char name[20];
    int amount;
    float price;
    ItemPosition Next;
} Item;
typedef struct _bill* BillPosition;
typedef struct _bill{
    char billname[20];
    int id;
    DatePosition Date;
    ItemPosition NextItem;
    BillPosition NextBill;
} Bill;

int ReadBills(BillPosition);
int ReadItems(BillPosition, ItemPosition, char *);
int Output(BillPosition);
int PrintFilteredBill(BillPosition, int);
int Menu();
int MenuOrEndProgram();
int ProfitBill(ItemPosition);
int SmallestProfitBill(BillPosition);
int LargestProfitBill(BillPosition);
int TotalProfit(BillPosition);
int SelectBillProfit(BillPosition);
int FindItem(BillPosition);
int DeleteBills(BillPosition);

int main(){

    Bill Head = {"", 0, NULL, NULL};
    int flag = 1;
    char x;
    ReadBills(&Head);

    while(flag){

        Menu();
        x = getchar();
        x = toupper(x);

        switch(x){
            case 'A':
                Output(Head.NextBill);
                flag = MenuOrEndProgram();
                break;
            case 'B':
                SmallestProfitBill(Head.NextBill);
                flag = MenuOrEndProgram();
                break;
            case 'C':
                LargestProfitBill(Head.NextBill);
                flag = MenuOrEndProgram();
                break;
            case 'D':
                TotalProfit(Head.NextBill);
                flag = MenuOrEndProgram();
                break;
            case 'E':
                SelectBillProfit(Head.NextBill);
                flag = MenuOrEndProgram();
                break;
            case 'F':
                FindItem(Head.NextBill);
                flag = MenuOrEndProgram();
                break;
            case 'O':
                flag = 0;
                break;
            default:
                printf("Invalid option. Program will terminate.\n");
                break;
        }
    }

    DeleteBills(&Head);
    Output(Head.NextBill);
    return 0;
}

int DeleteBills(BillPosition Start){

    BillPosition P = Start;
    BillPosition temp;

    while (P->NextBill != NULL) {

		ItemPosition Q = P->NextItem;
		ItemPosition tempItem;
		while (Q != NULL) {
			tempItem = Q->Next;
			Q->Next = tempItem->Next;
			tempItem->Next = NULL;
			free(tempItem);

		}
		
		P->Date = NULL;
		temp = P->NextBill;
		P->NextBill = temp->NextBill;
		temp->NextBill = NULL;
		free(temp);
	}

    return EXIT_SUCCESS;
}

int SelectBillProfit(BillPosition Start){
    BillPosition P = Start;
    int ID = 0;
    float profit = 0.0;

    printf("Enter the id of the desired bil:\n");
    scanf("%d", ID);

    while(P != NULL){
        if(P->id == ID){
            printf("%s ID = %d %d/%d/%d\n", P->billname, P->id, P->Date->year, P->Date->month, P->Date->day);
            profit += ProfitBill(P->NextItem);
        }
        P = P->NextBill;
    }
    printf("Profit of chosen bill(Id = %d) is %.2f", ID, profit);

    return EXIT_SUCCESS;
}

int FindItem(BillPosition Start){

    if(Start == NULL){
        printf("Bill list is empty,");
        return EXIT_SUCCESS;
    }

    char *name = (char *)malloc(sizeof(char)*20);
    int i = 0;
    printf("Input name of desired item:\n");
    scanf("%s", name);

    while(*(name+i) != '\0'){
        *(name+i) = tolower(*(name + i));
		i++;
    }

    int found = 0, counter = 0;
    BillPosition P = Start;
    while(P != NULL){

        ItemPosition Q = P->NextItem->Next;
        ItemPosition Beginning = P->NextItem->Next;

        while (Q != NULL) {
			if (strcmp(name, Q->name)==0) {
				found = 1;
				counter++;
				break;
			}
			Q = Q->Next;
		}
        if(found == 1){
            printf("%s ID = %d %d/%d/%d\n", P->billname, P->id, P->Date->year, P->Date->month, P->Date->day);
            Q = Beginning;
            while(Q != NULL){
                printf("%s %.2f %d\n", Q->name, Q->price, Q->amount);
				Q = Q->Next;
            }
            found = 0;
        }
        printf("\n");
        P = P->NextBill;
    }
    if(counter == 0){
        printf("%s was not found in any of the available bills.", name);
    }

    return EXIT_SUCCESS;
}

int TotalProfit(BillPosition Start){
    BillPosition P = Start;
    int totalprofit = 0.0;

    while(P != NULL){
        totalprofit += ProfitBill(P->NextItem);
        P = P->NextBill;
    }
    printf("Total profit accrued is %.2f\n", totalprofit);

    return EXIT_SUCCESS;
}

int SmallestProfitBill(BillPosition Start){

    BillPosition P = Start;
    float min = ProfitBill(P->NextItem);
    int ID = P->id;

    while(P != NULL){
        if(min > ProfitBill(P->NextItem)){
            min = ProfitBill(P->NextItem);
            ID = P->id;
        }
        P = P->NextBill;
    }
    P = Start;
    PrintFilteredBill(P, ID);
    printf("Profit of bill: %.2f\n", min);

    return EXIT_SUCCESS;
}

int LargestProfitBill(BillPosition Start){

    BillPosition P = Start;
    float max = ProfitBill(P->NextItem);
    int ID = P->id;

    while(P != NULL){
        if(max < ProfitBill(P->NextItem)){
            max = ProfitBill(P->NextItem);
            ID = P->id;
        }
        P = P->NextBill;
    }
    P = Start;
    PrintFilteredBill(P, ID);
    printf("Profit of bill: %.2f\n", max);

    return EXIT_SUCCESS;
}

int Menu(){

    printf("Menu:\n");
    printf("|| A - to see all bills || B - to see bill with smallest profit || C - to see bill with largest profit ||\n");
    printf("|| D - to see total profit of all bills || E - to see profit of a select bill || F - to see every bill where item was sold\n");
    printf("|| O - to exit from menu and end program\n");

    return EXIT_SUCCESS;
}

int MenuOrEndProgram(){

    printf("Press Enter to end program, and anything else to return to menu:\n");
    while(getchar() != '\n');

    char x = getchar();
    x = toupper(x);
    switch(x){
        case '\n': return 0; break;
        default: return 1;
    }
}

int ReadBills(BillPosition Start){

    FILE *fp1 = fopen("C:\\Users\\Admin\\OneDrive\\Desktop\\StrukturePodataka25-26\\Vjezbe6\\racuni.txt", "r");
    if(fp1 == NULL){
        printf("FAILED TO READ!"); 
        return EXIT_FAILURE;
    }

    BillPosition P = Start;
    int index = 0;
    char *path = (char *)malloc(100*sizeof(char));
    while(!feof(fp1)){
        BillPosition Q = (BillPosition)malloc(sizeof(Bill));
        Q->Date = malloc(sizeof(Date));
        Q->NextItem = malloc(sizeof(Item));
        Q->NextItem->Next = NULL;
        Q->id = index+1;
        strcpy(Q->billname, "Bill");

        fscanf(fp1, "%s", path);
        ReadItems(Q, Q->NextItem, path);

        if(index>0){
            for(P = Start; P->NextBill != NULL; P = P->NextBill){
                if (Q->Date->year > P->NextBill->Date->year) {
					break;
				}
				else if (Q->Date->year == P->NextBill->Date->year) {
					if (Q->Date->month > P->NextBill->Date->month) {
						break;
					}
					else if (Q->Date->month < P->NextBill->Date->month) {
						P= P->NextBill;
						break;
					}
					else {
						if (Q->Date->day > P->NextBill->Date->day) {
							break;
						}
						else if (Q->Date->day <= P->NextBill->Date->day) {
							P = P->NextBill;
							break;
						}
					}
				}
			}
		}
        Q->NextBill = P->NextBill;
        P->NextBill = Q;
        index++;
    }
    fclose(fp1);
    free(path);

    return EXIT_SUCCESS;
}

int ReadItems(BillPosition P, ItemPosition Start, char *Path){

    FILE *fp2 = fopen(Path, "r");
    if(fp2 == NULL){
        printf("FAILED TO READ!"); 
        return EXIT_FAILURE;
    }
    ItemPosition Q = Start;
    char buffer;

    char *year = (char *)malloc(sizeof(char)*5);
    fscanf(fp2, "%4s", year);
    P->Date->year = atoi(year);
    buffer = fgetc(fp2);

    char *month = (char *)malloc(sizeof(char)*3);
    fscanf(fp2, "%2s", month);
    P->Date->month = atoi(month);
    buffer = fgetc(fp2);

    char *day = (char *)malloc(sizeof(char)*3);
    fscanf(fp2, "%2s", day);
    P->Date->day = atoi(day);

    while(!feof(fp2)){
        ItemPosition QItem = (ItemPosition)malloc(sizeof(Item));
        if(QItem == NULL) return EXIT_FAILURE;
        char *temp = (char *)malloc(sizeof(char)*10);
        
        fscanf(fp2, "%s", temp);
        for(Q = Start; Q->Next != NULL; Q = Q->Next){
            if(strcmp(temp, Q->Next->name)<0) break;
        }
        QItem->Next = Q->Next;
        Q->Next = QItem;

        strcpy(QItem->name, temp);
        fscanf(fp2, "%s", temp);
        QItem->amount = atoi(temp);
        fscanf(fp2, "%s", temp);
        QItem->price = atof(temp);
    }

    free(year);
    free(month);
    free(day);
    fclose(fp2);
    return EXIT_SUCCESS;
}

int Output(BillPosition Start){

    BillPosition P = Start;
    if(P == NULL){
        printf("Empty bill list.");
        return EXIT_SUCCESS;
    }

    while(P != NULL){

        printf("%s ID = %d %d/%d/%d\n", P->billname, P->id, P->Date->year, P->Date->month, P->Date->day);
        ItemPosition Q = P->NextItem->Next;
        while(Q != NULL){
            printf("%s %d %.2f\n", Q->name, Q->amount, Q->price);
            Q = Q->Next;
        }
        printf("\n");
        P = P->NextBill;
    }

    return EXIT_SUCCESS;
}

int PrintFilteredBill(BillPosition P, int id) {
	while (P != NULL) {
		if (id == P->id) {
			printf("%s %d %d/%d/%d\n", P->billname, P->id, P->Date->year, P->Date->month, P->Date->day);
			ItemPosition Q = P->NextItem->Next;
			while (Q != NULL) {
				printf("%s %.2f %d\n", Q->name, Q->price, Q->amount);
				Q = Q->Next;

			}
		}
		P = P->NextBill;
	}
	return 0;
}

int ProfitBill(ItemPosition Start) {
	
	ItemPosition P = Start->Next;
	float profit = 0.0;

	while (P != NULL) {
		profit = profit + P->price*P->amount;
		P = P->Next;
	}
	
	return profit;
}