#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define min(a,b) (a < b) ? a : b

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
		printf("Loi mo File\n");
		return;
	}
	
	fscanf(f, "%f", capacity);
	
	int i = 0;
	it->data = (Item*)malloc(sizeof(Item));
	
	while(!feof(f)){
		fscanf(f, "%f%f%d", &it->data[i].weight, &it->data[i].value, &it->data[i].quantity);
		fgets(it->data[i].name, 20, f);
		strtok(it->data[i].name, "\n");
		
		it->data[i].density = it->data[i].value / it->data[i].weight;
		it->data[i].solution = 0;
		i++;
		it->data = realloc(it->data, sizeof(Item) * (i+1));
	}
	
	it->size = i;
	fclose(f);
}

void printData(ItemList it, float capacity){
	printf("Trong luong cua ba lo: %.2f\n", capacity);
	printf("Phuong an Cai Ba Lo 2, su dung thuat toan Greedy:\n");
	
	float sumWeight = 0.0f;
	float sumValue = 0.0f;
	
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T Luong | Gia Tri | Don gia | So luong | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	for(int i = 0; i < it.size; ++i){
		sumWeight += it.data[i].weight * it.data[i].solution;
		sumValue += it.data[i].value * it.data[i].solution;
		
		printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d    |%6d     |\n", (i+1), it.data[i].name, it.data[i].weight, it.data[i].value, it.data[i].density, 
		it.data[i].quantity, it.data[i].solution);
	}
	printf("|---|--------------------|---------|---------|---------|----------|-----------|\n");
	printf("Phuong an tim duoc: X = (");
	for(int i = 0; i < it.size -1;++i){
		printf("%d, ", it.data[i].solution);
	}
	printf("%d)\n", it.data[it.size - 1].solution);
	printf("Tong trong luong: %.2f\n", sumWeight);
	printf("Tong gia tri: %.2f\n", sumValue);
}

void swap(Item *a, Item *b){
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(ItemList *it){
	for(int i = 0; i < it->size - 2; ++i){
		for(int j = it->size - 1; j > i; --j){
			if(it->data[j].density > it->data[i].density){
				swap(&it->data[j], &it->data[i]);
			}
		}
	}
}

void Greedy(ItemList *it, float capacity){
	for(int i = 0; i < it->size; ++i){
		it->data[i].solution = min(it->data[i].quantity, capacity / it->data[i].weight);
		capacity -= it->data[i].solution * it->data[i].weight;
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

