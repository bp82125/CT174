#include <stdio.h>
#include <malloc.h>

typedef struct Item{
	char name[20];
	int solution, quantity;
	int weight, value;
}Item;

typedef struct ItemList{
	Item *data;
	int size;
}ItemList;

typedef int Table[50][100];

void readFromFile(ItemList *it, int *capacity){
	FILE *f = fopen("CaiBaLo2.txt", "r");
	if(f == NULL){
		printf("Loi mo file\n");
		return;
	}
	
	fscanf(f, "%d", capacity);
	int i = 0;
	it->data = malloc(sizeof(Item));
	while(!feof(f)){
		fscanf(f, "%d%d%d%[^\n]", &it->data[i].weight, &it->data[i].value, &it->data[i].quantity, it->data[i].name);
		it->data[i].solution = 0;
		i++;
		it->data = realloc(it->data, sizeof(Item) * (i+1));
	}
	
	it->size = i;
	fclose(f);
}

void printData(ItemList it, int capacity){
	int sumWeight = 0;
	int sumValue = 0;
	printf("Trong luong cua ba lo: %d\n", capacity);
	printf("|---|--------------------|---------|---------|----------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | So luong | Phuong An |\n");
	printf("|---|--------------------|---------|---------|----------|-----------|\n");
	
	for(int i = 0; i < it.size; ++i){
		sumWeight += it.data[i].weight * it.data[i].solution;
		sumValue += it.data[i].value * it.data[i].solution;
		printf("|%2d |%-20s|%5d    |%5d    |%6d    |%6d     |\n", i+1,it.data[i].name, it.data[i].weight, it.data[i].value,it.data[i].quantity ,it.data[i].solution);
	}
	printf("|---|--------------------|---------|---------|----------|-----------|\n");
	printf("Tong trong luong cua ba lo: %d\n", sumWeight);
	printf("Tong gia tri cua ba lo: %d\n", sumValue);	
}

Table X, F;
#define min(a,b) (a<b) ? a : b

void createTable(ItemList it, float capacity){
	for(int V = 0; V <= capacity; ++V){
		X[0][V] = min(V / it.data[0].weight,  it.data[0].quantity);
		F[0][V] = X[0][V] * it.data[0].value;
	}
	
	for(int k = 1; k < it.size; ++k){
		for(int V = 0;  V <= capacity; ++V){
			int max = F[k-1][V];
			int x = 0;
			int maxItems = min(V / it.data[k].weight, it.data[k].quantity);
			for(int i = maxItems; i >= 1; --i){
				int f = F[k-1][V - i*it.data[k].weight] + i*it.data[k].value;
				if(max < f){
					max = f;
					x = i;
				}
			}
			F[k][V] = max;
			X[k][V] = x;
		}
	}
}

void lookUpTable(ItemList it, int capacity){
	int weight = capacity;
	for(int k = it.size -1; k >= 0; --k){
		it.data[k].solution = X[k][weight];
		weight -= it.data[k].solution * it.data[k].weight;
	}
}

void printTable(ItemList it, int capacity){
	for(int k = 0; k < it.size; ++k){
		for(int V = 0; V <= capacity; ++V){
			printf("%d %2d| ", X[k][V], F[k][V]);
		}
		printf("\n");
	}
}

int main(){
	ItemList it;
	int capacity;
	readFromFile(&it, &capacity);
	createTable(it, capacity);
	lookUpTable(it, capacity);
	printTable(it, capacity);
	printData(it, capacity);
	return 0;
}
