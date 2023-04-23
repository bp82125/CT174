#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <float.h>

#define MAXN 100


typedef struct Item{
	char name[20];
	int solution;
	float weight, value, density;
}Item;

typedef struct ItemList{
	Item *data;
	int size;
}ItemList;

void readFromFile(ItemList *it, float *capacity){
	FILE *f = fopen("CaiBaLo1.txt", "r");
	if(f == NULL){
		printf("Loi mo file\n");
		return;
	}
	
	fscanf(f, "%f", capacity);
	int i = 0;
	
	it->data = malloc(sizeof(Item));
	while(!feof(f)){
		fscanf(f, "%f%f", &it->data[i].weight, &it->data[i].value);
		fgets(it->data[i].name, 30, f);
		strtok(it->data[i].name, "\n");
		it->data[i].density = it->data[i].value / it->data[i].weight;
		it->data[i].solution = 0;
		i++;
		it->data = realloc(it->data, sizeof(Item) * (i + 1));
	}
	
	it->size = i;
	fclose(f);
}

void printData(ItemList it, float capacity){
	printf("Trong luong cua ba lo: %.2f\n", capacity);
	
	float sumWeight = 0.0f;
	float sumValue = 0.0f;
	
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | Don Gia | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	
	for(int i = 0; i < it.size; ++i){
		sumWeight += it.data[i].weight * it.data[i].solution;
		sumValue += it.data[i].solution * it.data[i].value;
		printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d     |\n", i+1 ,it.data[i].name, it.data[i].weight, it.data[i].value, it.data[i].density, it.data[i].solution);
	}
	
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	printf("Phuong an tim duoc: X = (");
	for(int i=0;i<it.size-1;++i){
		printf("%d,", it.data[i].solution);
	}
	printf("%d)\n", it.data[it.size-1].solution);
	printf("Tong trong luong cua ba lo: %.2f\n", sumWeight);
	printf("Tong gia tri cua ba lo: %.2f\n", sumValue);
}

void swap(Item *a, Item *b){
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(ItemList *it){
	for(int i = 0; i < it->size - 1; ++i){
		for(int j = it->size - 1; j > i; --j){
			if(it->data[j].density > it->data[i].density){
				swap(&it->data[i], &it->data[j]);
			}
		}
	}
}

float totalValue;
float totalWeight;
float upperBound;
float bestValue;
int currentSolution[MAXN];

void createRootNode(ItemList it, float capacity){
	totalValue = 0;
	totalWeight = capacity;
	upperBound = capacity * it.data[0].density;
	bestValue = FLT_MIN;
}

void updateSolution(ItemList *it){
	if(totalValue > bestValue){
		bestValue = totalValue;
		
		for(int i = 0; i < it->size; ++i){
			it->data[i].solution = currentSolution[i];
		}
	}
}

void BranchAndBound(ItemList *it, int currentItem){
	int maxItem = (int) (totalWeight / it->data[currentItem].weight);
	
	for(int i = maxItem; i >= 0; --i){
		totalValue += i * it->data[currentItem].value;
		totalWeight -= i * it->data[currentItem].weight;
		
		if(currentItem == it->size - 1){
			upperBound = totalValue;
		}else{
			upperBound = totalValue + totalWeight * it->data[currentItem + 1].density;
		}
		
		if(upperBound > bestValue){
			currentSolution[currentItem] = i;
			if(currentItem == it->size - 1 || totalWeight == 0){
				updateSolution(it);
			}else{
				BranchAndBound(it, currentItem + 1);
			}
		}
		currentSolution[currentItem] = 0;
		totalValue -= i * it->data[currentItem].value;
		totalWeight += i * it->data[currentItem].weight;
	}
}

int main(void){
	ItemList it;
	float capacity;
	readFromFile(&it, &capacity);
	BubbleSort(&it);
	createRootNode(it, capacity);
	BranchAndBound(&it, 0);
	printData(it, capacity);
	return 0;
}
