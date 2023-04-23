#include <stdio.h>
#include <malloc.h>

typedef int keytype;
typedef float othertype;

typedef struct recordType{
	keytype key;
	othertype otherfields;	
}recordType;

void readFromFile(recordType arr[], int *n){
	FILE *f = fopen("data.txt", "r");
	if(f == NULL){
		printf("Loi mo file\n");
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

void printList(recordType arr[], int n){
	printf("|-----|-------------|\n");
	printf("| Key | Otherfields |\n");
	printf("|-----|-------------|\n");
	
	for(int i=0;i<n;++i){
		printf("|%3d  | %8.2f    |\n", arr[i].key, arr[i].otherfields);
	}
	printf("|-----|-------------|\n");
}

void swap(recordType *a, recordType *b){
	recordType temp = *a;
	*a = *b;
	*b = temp;
}

void SelectionSort(recordType arr[], int n){
	for(int i = 0; i <= n - 2; ++i){
		int min = arr[i].key;
		int idx = i;
		for(int j = i + 1; j <= n-1;++j){
			if(arr[j].key < min){
				min = arr[j].key;
				idx = j;
			}
		}
		swap(&arr[i], &arr[idx]);
	}
}

int main(){
	recordType arr[100];
	int n;
	printf("Thuat toan Selection Sort:\n");
	readFromFile(arr, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printList(arr, n);
	SelectionSort(arr, n);
	printf("Du lieu sau khi sap xep:\n");
	printList(arr, n);
	
	
	return 0;
}


