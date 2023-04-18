#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <float.h>

#define MAXN 30

typedef struct Item{
	char name[20];
	float weight, value, density;
	int solution;
}Item;

typedef struct ItemList{
	Item *data;
	int size;
}ItemList;

void readFromFile(ItemList *it, float *capacity){
	FILE *f = fopen("CaiBaLo3.txt", "r");
	
	fscanf(f, "%f", capacity);
	
	it->data = malloc(sizeof(Item));
	
	int i = 0;
	
	while(!feof(f)){
		fscanf(f, "%f%f", &it->data[i].weight, &it->data[i].value);
		fgets(it->data[i].name, 20, f);
		strtok(it->data[i].name, "\n");
		
		it->data[i].density = it->data[i].value / it->data[i].weight;
		it->data[i].solution = 0;
		i++;
		it->data = realloc(it->data, sizeof(Item) * (i + 1));
	}
	
	it->size = --i;
	fclose(f);
}

void printList(ItemList it, float capacity){
	printf("\nPhuong an Cai Ba lo 3 dung thuat toan NHANH CAN nhu sau:\n");
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | Don Gia | So luong | Phuong An |\n");
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	
	float sumWeight = 0;
	float sumValue = 0;
	
	for(int i = 0; i < it.size; ++i){
		sumWeight += it.data[i].weight * it.data[i].solution;
		sumValue += it.data[i].value * it.data[i].solution;
		printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d    |%6d     |\n", i+1, it.data[i].name ,it.data[i].weight, it.data[i].value, it.data[i].density, 1, it.data[i].solution);
	}
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	
	printf("Phuong an tim duoc: X = (");
	for(int i = 0; i < it.size - 1;++i){
		printf("%d, ", it.data[i].solution);
	}
	
	printf("%d)\n", it.data[it.size - 1].solution);
	printf("Trong luong cua ba lo = %.2f\n", capacity);	
	printf("Tong gia tri = %.2f\n", sumValue);
	printf("Tong trong luong = %.2f\n", sumWeight);
}

void swap(Item *a, Item *b){
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(ItemList *it){
	for(int i = 0; i < it->size - 1; ++i){
		for(int j = it->size - 1; j > i; --j){
			if(it->data[j].density > it->data[i].density){;
				swap(&it->data[j], &it->data[i]);
			}
		}
	}	
}

float upperBound;
float totalValue;
float totalWeight;
float bestValue;
int current[MAXN];

#define min(a,b) (a < b) ? a : b

void createRootNode(ItemList it, int capacity){
	totalValue = 0;
	totalWeight = capacity;
	upperBound = totalValue + it.data[0].density * capacity;
	bestValue = FLT_MIN;
}

void updateBestValue(ItemList *it){
	if(bestValue < totalValue){
		bestValue = totalValue;
	}
	
	for(int i = 0; i < it->size; ++i){
		it->data[i].solution = current[i];
	}
}

void BranchAndBound(ItemList *it, int numItems){
	int maxItems = min((int) (totalWeight / it->data[numItems].weight), 1);
	
	for(int j = maxItems; j >= 0; --j){
		totalValue += maxItems * it->data[numItems].value;
		totalWeight -= maxItems * it->data[numItems].weight;
		
		if(numItems == it->size - 1){
			upperBound = totalValue; 
		}else{
			upperBound = totalValue + totalWeight * it->data[numItems + 1].density;
		}
		
		if(upperBound > bestValue){
			current[numItems] = j;
			if(numItems == it->size - 1){
				updateBestValue(it);
			}else{
				BranchAndBound(it, numItems + 1);
			}
		}
		
		current[numItems] = 0;
		totalValue -= maxItems * it->data[numItems].value;
		totalWeight += maxItems * it->data[numItems].weight;	
	}
}

int main(){
	ItemList it;
	float capacity;
	readFromFile(&it, &capacity);
	
	BubbleSort(&it);
	
	createRootNode(it, capacity);
	BranchAndBound(&it, 0);
	
	printList(it, capacity);
	return 0;
}
