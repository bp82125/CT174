#include <stdio.h>
#include <string.h>
#include <malloc.h>

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
		fgets(it->data[i].name, 20, f);
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
	printf("Phuong cai Cai Ba Lo 1, su dung thuat toan Greedy:\n");
	printf("Trong luong cua Ba Lo: %.2f\n", capacity);
	
	float sumWeight = 0.0f;
	float sumValue = 0.0f;
	
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | Don Gia | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	for(int i = 0; i < it.size; ++i){
		sumWeight += it.data[i].weight * it.data[i].solution;
		sumValue += it.data[i].value * it.data[i].solution;
		printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d     |\n", (i + 1), it.data[i].name, it.data[i].weight, it.data[i].value, it.data[i].density, it.data[i].solution);
	}
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	printf("Phuong an tim duoc: X = (");
	for(int i = 0; i < it.size - 1; ++i){
		printf("%d, ", it.data[i].solution);
	}
	printf("%d)\n", it.data[it.size-1].solution);
	printf("Tong gia tri: %.2f\n", sumValue);
	printf("Tong trong luong: %.2f\n", sumWeight);	
}

void swap(Item *a, Item *b){
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(ItemList *it){
	for(int i = 0; i <= it->size - 2; ++i){
		for(int j = it->size - 1; j > i; --j){
			if(it->data[j].density > it->data[i].density){
				swap(&it->data[j], &it->data[i]);
			}
		}
	}
}

void Greedy(ItemList *it, float capacity){
	int n = it->size;
	
	for(int i = 0; i < n; ++i){
		it->data[i].solution = capacity / it->data[i].weight;
		capacity -= it->data[i].weight * it->data[i].solution;
	}
}

int main(){
	ItemList it;
	float capacity;
	
	readFromFile(&it, &capacity);
	BubbleSort(&it);
	Greedy(&it, capacity);
	printData(it, capacity);
	
	return 0;
}
