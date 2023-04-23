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
	printf("| Key | Otherfields |\n");
	printf("|-----|-------------|\n");
	
	for(int i = 0; i < n; ++i){
		printf("| %3d | %8.2f    |\n", arr[i].key, arr[i].otherfields);
	}
	
	printf("|-----|-------------|\n");
}

keytype findPivot(recordtype arr[], keytype start, keytype end){
	int k = start + 1;
	keytype firstkey = arr[start].key;
	while(k <= end && arr[k].key == firstkey) k++;
	
	if(k > end) return -1;
	if(arr[k].key > firstkey) return k;
	return start;
}

int partition(recordtype arr[], int start, int end, keytype pivot){
	int L = start;
	int R = end;
	
	while(L <= R){
		while(arr[L].key < pivot) L++;
		while(arr[R].key >= pivot) R--;
		if(L < R) swap(&arr[L], &arr[R]);
	}
	
	return L;
}

void QuickSort(recordtype arr[], int start, int end){
	int pivotIndex = findPivot(arr, start, end);
	
	if(pivotIndex != -1){
		keytype pivot = arr[pivotIndex].key;
		int k = partition(arr, start, end, pivot);
		QuickSort(arr, start, k-1);
		QuickSort(arr, k, end);
	}
}

int main(){
	recordtype arr[100];
	int n;
	printf("Thuat toan Quick Sort:\n");
	readFromFile(arr, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(arr, n);
	QuickSort(arr, 0, n-1);
	printf("Du lieu sau khi sap xep:\n");
	printData(arr, n);
	
	return 0;
}
