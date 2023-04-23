#include <stdio.h>

typedef int keytype ;
typedef float othertype;

typedef struct recordType{
	keytype key;
	othertype otherfields;
}recordType;

void swap(recordType *a, recordType *b){
	recordType temp = *a;
	*a = *b;
	*b = temp;
}

void readFromFile(recordType arr[], int *n){
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

void printData(recordType arr[], int n){
	printf("|-----|-------------|\n");
	printf("| Key | Otherfields |\n");
	printf("|-----|-------------|\n");
	
	for(int i =0; i<n;++i){
		printf("| %3d |%8.2f     |\n", arr[i].key, arr[i].otherfields);
	}
	printf("|-----|-------------|\n");
	
}

void InsertionSort(recordType arr[], int n){
	for(int i = 1; i <= n - 1; ++i){
		int j = i;
		while(j > 0 && arr[j].key < arr[j-1].key){
			swap(&arr[j], &arr[j-1]);
			j--;
		}	
	}
}

int main(){
	recordType arr[100];
	int n;
	printf("Thuat toan Insertion Sort:\n");
	readFromFile(arr, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(arr, n);
	InsertionSort(arr, n);
	printf("Du lieu sau khi sap xep:\n");
	printData(arr, n);
	return 0;
}
