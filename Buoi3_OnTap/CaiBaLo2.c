#include <stdio.h>
#include <malloc.h>
#include <float.h>

#define MAXN 100

typedef struct Item{
	char name[20];
	int solution, quantity;
	float weight, value, density;
}Item;

typedef struct ItemList{
	Item *data;
	int size;
}ItemList;

void readFromFile(ItemList *it, float *capacity){
	FILE *f = fopen("CaiBaLo2.txt", "r");
	if(f == NULL){
		printf("Loi mo file\n");
		return;
	}
	
	fscanf(f, "%f", capacity);
	int i = 0;
	
	it->data = malloc(sizeof(Item));
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &it->data[i].weight, &it->data[i].value, &it->data[i].quantity, it->data[i].name);
		it->data[i].solution = 0;
		it->data[i].density = it->data[i].value / it->data[i].weight;
		i++;
		it->data = realloc(it->data, sizeof(Item) * (i+1));
	}
	
	it->size = i;
	fclose(f);
}

void printData(ItemList it, float capacity){
	printf("Trong luong cua ba lo: %.2f\n", capacity);
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | Don Gia | So Luong | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	
	float sumValue = 0.0f;
	float sumWeight = 0.0f;
	
	for(int i = 0; i < it.size; ++i){
		sumValue += it.data[i].solution *  it.data[i].value;
		sumWeight += it.data[i].solution *  it.data[i].weight;
		
		printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d    |%6d     |\n", i+1, it.data[i].name, it.data[i].weight, it.data[i].value,it.data[i].density, it.data[i].quantity, it.data[i].solution);
	}
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	printf("Phuong an tim duoc: X = (");
	for(int i = 0; i <= it.size - 2; ++i){
		printf("%d,", it.data[i].solution);
	}
	printf("%d)\n", it.data[0].solution);
	printf("Tong trong luong: %.2f\n", sumWeight);
	printf("Tong gia tri: %.2f\n", sumValue);
}

void swap(Item *a, Item *b){
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(ItemList *it){
	int n = it->size;
	for(int i=0; i<n-1;++i){
		for(int j = n-1;j>i;--j){
			if(it->data[j].density > it->data[i].density){
				swap(&it->data[i], &it->data[j]);
			}
		}
	}
}

float totalValue;
float remainWeight;
float bestValue;
float upperBound;
int solution[MAXN];

#define min(a,b) (a<b) ? a : b

void createRootNode(ItemList it, float capacity){
	totalValue = 0;
	remainWeight = capacity;
	bestValue = FLT_MIN;
	upperBound = remainWeight * it.data[0].density;
}

void updateSolution(ItemList *it){
	if(bestValue < totalValue){
		bestValue = totalValue;
		
		for(int i = 0; i < it->size; ++i){
			it->data[i].solution = solution[i];
		}
	}
}

void BranchAndBound(ItemList *it, int n){
	int maxItems = min((int) (remainWeight / it->data[n].weight), it->data[n].quantity);
	
	for(int i = maxItems; i >=0; --i){
		totalValue += i * it->data[n].value;
		remainWeight -= i * it->data[n].weight;
		
		if(n == it->size - 1){
			upperBound = totalValue;
		}else{
			upperBound = totalValue + remainWeight * it->data[n+1].density;
		}
		
		if(upperBound > bestValue){
			solution[n] = i;
			if(n == it->size - 1){
				updateSolution(it);
			}else{
				BranchAndBound(it, n+1);
			}
		}
		solution[n] = 0;
		totalValue -= i * it->data[n].value;
		remainWeight += i * it->data[n].weight;		
	}
}

int main(){
	ItemList it;
	float capacity;
	readFromFile(&it, &capacity);
	BubbleSort(&it);
	createRootNode(it, capacity);
	BranchAndBound(&it, 0);
	printData(it, capacity);
	return 0;
}
