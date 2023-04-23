#include <stdio.h>

typedef int keytype;
typedef float othertype;

typedef struct recordtype{
	keytype key;
	othertype otherfields;	
}recordtype;

void swap(recordtype *a, recordtype *b){
	recordtype temp = *a;
	*a = *b;
	*b = temp;
}

void readFromFile(recordtype arr[], int *n){
	FILE *f = fopen("data.txt", "r");
	if(f == NULL){
		printf("Loi mo file!\n");
		return;
	}
	
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%f", &arr[i].key, &arr[i].otherfields);
		i++;
	}
	*n = i;
	fclose(f);
}

void printData(recordtype arr[], int n){
	printf("|-----|-------------|\n");
	printf("| Key | OtherFields |\n");
	printf("|-----|-------------|\n");
	
	for(int i = 0; i < n; ++i){
		printf("| %3d | %8.2f    |\n", arr[i].key, arr[i].otherfields);
	}
	printf("|-----|-------------|\n");
}

void BubbleSort(recordtype arr[], int n){
	for(int i = 0; i <= n-2; ++i){
		for(int j = n - 1; j >= i; --j){
			if(arr[i].key > arr[j].key){
				swap(&arr[i], &arr[j]);
			}
		}
	}
}

int main(){
	recordtype arr[100];
	int n;
	printf("Thuat toan Bubble Sort:\n");
	readFromFile(arr, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(arr, n);
	BubbleSort(arr, n);
	printf("Du lieu sau khi sap xep:\n");
	printData(arr, n);
	return 0;
}
