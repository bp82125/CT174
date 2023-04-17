#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item{
	char name[20];
	int weight, value, solution;
}Item;

typedef struct ItemList{
	Item *items;
	int size;
}ItemList;

typedef int Table[50][100];

void readFromFile(ItemList *it, int *W){
	FILE *f = fopen("CaiBaLo1.txt", "r");
	
	if (f == NULL) {
		printf("Error opening file\n");
		exit(1);
	}
	
	fscanf(f, "%d", W);
	
	it->items = malloc(sizeof(Item));
	
	int n = 0;
	while(!feof(f)){
		fscanf(f, "%d%d", &it->items[n].weight, &it->items[n].value);
		fgets(it->items[n].name, 20, f);
		strtok(it->items[n].name, "\n");
		it->items[n].solution = 0;
		n++;
		it->items = (Item*)realloc(it->items, sizeof(Item) * (n+1));
	}
	
	it->size = n;
	
	fclose(f);
}

void createTable(ItemList it, int W, Table X, Table F){
	for(int V = 0; V <= W; ++V){
		X[0][V] = V / it.items[0].weight;
		F[0][V] = X[0][V] * it.items[0].value;
	}
	
	for(int k = 1; k < it.size; ++k){
		for(int V = 0; V <= W; ++V){
			int Xmax = 0;
			int Fmax = F[k-1][V];
			
			int quantity =  V / it.items[k].weight;
			
			for(int xk = quantity; xk >= 1; --xk){
				if(F[k-1][V - xk *  it.items[k].weight] + xk * it.items[k].value > Fmax){
					Fmax = F[k-1][V - xk *  it.items[k].weight] + xk * it.items[k].value;
					Xmax = xk;
				}
			}
			
			X[k][V] = Xmax;
			F[k][V] = Fmax;
		}
	}
}

void lookUpTable(ItemList *it, int W, Table X, Table F){
	int V = W;
	for(int i = it->size - 1; i >= 0; --i){
		it->items[i].solution = X[i][V];
		V -= X[i][V] * it->items[i].weight;
	}
}

void printTable(ItemList it, int W, Table X, Table F){
	for(int k = 0; k < it.size; ++k){
		for(int V = 0; V <= W; ++V){
			printf("%d %2d| ", X[k][V], F[k][V]);
		}
		printf("\n");
	}
}

void printItemList(ItemList it){
	printf("|---|--------------------|---------|---------|-----------|\n");
	printf("|STT|     Ten do vat     | T Luong | Gia Tri | Phuong an |\n");
	printf("|---|--------------------|---------|---------|-----------|\n");
	
	
	int totalWeight = 0;
	int totalValue = 0;
	
	for(int i = 0; i < it.size; ++i){
		printf("|%2d |%-20s|%5d    |%5d    |%6d     |\n", (i + 1), it.items[i].name ,it.items[i].weight, it.items[i].value, it.items[i].solution);
		totalWeight += it.items[i].solution * it.items[i].weight;
		totalValue += it.items[i].solution * it.items[i].value;
	}
	printf("|---|--------------------|---------|---------|-----------|\n");
	printf("Phuong an X = (");
	for(int i = 0; i < it.size - 1; ++i){
		printf("%d, ", it.items[i].solution);
	}
	
	printf("%d)\n", it.items[it.size-1].solution);
	
	printf("Tong trong luong = %d\n", totalWeight);
	printf("Tong gia tri = %d\n", totalValue);
}

int main(void){
	ItemList it;
	int W;
	
	readFromFile(&it, &W);
	
//	for(int i = 0; i < it.size; ++i){
//		printf("%d %d %s\n", it.items[i].weight, it.items[i].value, it.items[i].name);
//	}
	Table X, F;
	createTable(it, W, X, F);
	printTable(it, W, X, F);
	lookUpTable(&it, W, X, F);
	
	printf("\nPhuong an cho bai toan Cai Ba Lo 1, su dung Dynamic Programming la:\n\n");
	
	printItemList(it);
	
	return 0;
}
