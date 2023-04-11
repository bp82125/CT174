#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) (a < b) ? a : b

typedef struct Item {
	char name[20];
	float weight, value, density;
	int solutionPackages, maxPackages;
} Item;

Item *ReadFromFile(float *maxCapacity, int *numItems) {
	FILE *f;
	f = fopen("CaiBaLo2.txt", "r");

	fscanf(f, "%f", maxCapacity);

	Item *items;
	items = (Item*)malloc(sizeof(Item));

	int i = 0;
	while (!feof(f)) {
		fscanf(f, "%f%f%d", &items[i].weight, &items[i].value, &items[i].maxPackages);
		fgets(items[i].name, 20, f);
		strtok(items[i].name, "\n");
		items[i].solutionPackages = 0;
		items[i].density = items[i].value / items[i].weight;
		i++;
		items = (Item*)realloc(items, sizeof(Item) * (i + 1));
	}

	
	*numItems = i-1; 
	fclose(f);
	return items;
}

void swap(Item *x, Item *y) {
	Item temp = *x;
	*x = *y;
	*y = temp;
}

void PrintFromFile(Item *items, int numItems, float maxCapacity) {
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an Cai Ba Lo 2 su dung thuat toan Branch And Bound nhu sau:\n");
	printf("\nTrong luong cua ba lo = %-9.2f\n", maxCapacity);

	printf("|---|--------------------|---------|---------|----------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T.luong | Gia Tri | So luong | Don Gia | Phuong An |\n");
	printf("|---|--------------------|---------|---------|----------|---------|-----------|\n");

	for (int i = 0; i < numItems; ++i) {
		printf("|%2d |%-20s|%9.2f|%9.2f|%5d     |%9.2f|%6d     |\n",
		       i + 1, items[i].name, items[i].weight, items[i].value,items[i].maxPackages, items[i].density, items[i].solutionPackages);
		TongTL = TongTL + items[i].solutionPackages * items[i].weight;
		TongGT = TongGT + items[i].solutionPackages * items[i].value;
	}
	printf("|---|--------------------|---------|---------|----------|---------|-----------|\n");
	printf("Phuong an theo thu tu giam dan: X(");
	for(int i = 0; i < numItems - 1;++i){
		printf("%d, ", items[i].solutionPackages);
	}
	printf("%d)\n", items[numItems - 1].solutionPackages);
	printf("Tong trong luong = %-9.2f\n", TongTL);
	printf("Tong gia tri = %-9.2f\n", TongGT);
}

void bubbleSort(Item *dsdv, int n){
	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; ++j){
			if(dsdv[i].density < dsdv[j].density){
				swap(&dsdv[i], &dsdv[j]);
			}
		}
	}
}

void createRootNode(float maxWeight, float *currentWeight, float *upperBound, float *tempMaxValue, float *currentValue, float maxDensity) {
	*currentValue = 0.0;
	*currentWeight = maxWeight;
	*upperBound = *currentWeight * maxDensity;
	*tempMaxValue = 0.0;
}

void update_maxValue(float currentValue, float *tempMaxValue, int tempSolution[], Item *items, int numItems){
	if(*tempMaxValue < currentValue){
		*tempMaxValue = currentValue;
		for(int i = 0; i < numItems; ++i){
			items[i].solutionPackages = tempSolution[i];
		}
	}
}

void BranchAndBound(int i, float *currentValue, float *upperBound, float *currentWeight, float *tempMaxValue, int tempSolution[], Item items[], int numItems){
	int maxPackages = min(items[i].maxPackages, *currentWeight/items[i].weight);
	for(int j = maxPackages; j >= 0; --j){
		*currentValue += j * items[i].value;
		*currentWeight -= j * items[i].weight;
		
		if(i == numItems - 1){
			*upperBound = *currentValue;			
		}
		else{
			*upperBound = (*currentValue) + (*currentWeight) * items[i + 1].density;			
		}
		 
		if(*upperBound > *tempMaxValue){
			tempSolution[i] = j;
			if(i == numItems - 1 || *currentWeight == 0){
				update_maxValue(*currentValue, tempMaxValue, tempSolution, items, numItems);
			}else{
				BranchAndBound(i + 1, currentValue, upperBound, currentWeight, tempMaxValue, tempSolution, items, numItems);
			}
		}
	
		tempSolution[i] = 0;
		*currentValue -= j * items[i].value;
		*currentWeight += j * items[i].weight; 
	}
}

int main() {
	float maxWeight;
	int numItems;
	Item *items = ReadFromFile(&maxWeight, &numItems);
	
	bubbleSort(items, numItems);
	
	float upperBound;
	float currentValue;
	float currentWeight;
	float tempMaxValue;
	
	int tempSolution[6];
	
	createRootNode(maxWeight, &currentWeight, &upperBound, &tempMaxValue, &currentValue, items[0].density);
	
	BranchAndBound(0, &currentValue, &upperBound, &currentWeight, &tempMaxValue, tempSolution, items, numItems);
	
	PrintFromFile(items, numItems, maxWeight);
	
	free(items);
	
	return 0;
}

