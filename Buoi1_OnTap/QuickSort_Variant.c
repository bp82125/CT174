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
	
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%f", &arr[i].key, &arr[i].otherfields);
		i++;
	}
	*n = i;
	fclose(f);
}

void printData(recordtype arr[], int n){
	printf("----|------------\n");
	printf("Key | Otherfields\n");
	printf("----|------------\n");
	
	for(int i = 0; i < n; ++i){
		printf("%3d | %8.2f\n", arr[i].key, arr[i].otherfields);
	}
	
	printf("----|------------\n");
}

int findPivot(recordtype arr[], int start, int end){
	int pivotIndex = start + 1;
	while(pivotIndex <= end && arr[pivotIndex].key == arr[start].key) pivotIndex++;
	
	if(pivotIndex > end) return -1;
	if(arr[pivotIndex].key < arr[start].key) return pivotIndex;
	return start;
}

int partition(recordtype arr[], int start, int end, keytype pivot){
	int L = start;
	int R = end;
	
	while(L <= R){
		while(arr[L].key <= pivot) L++;
		while(arr[R].key > pivot) R--;
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
	printf("Thuat toan Quick Sort bien the:\n");
	readFromFile(arr, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(arr, n);
	
	printf("Du lieu truoc khi sap xep:\n");
	printData(arr, n);
	QuickSort(arr, 0, n-1);
	printf("Du lieu sau khi sap xep:\n");
	printData(arr, n);
	return 0;
}
