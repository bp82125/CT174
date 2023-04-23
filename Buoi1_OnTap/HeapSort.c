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
	
	*n=i;
	fclose(f);
}

void printData(recordtype arr[], int n){
	printf("Key | Otherfields\n");
	
	for(int i = 0; i<n;++i){
		printf("%3d | %8.2f\n", arr[i].key, arr[i].otherfields);
	}
}

void pushDown(recordtype arr[], keytype first, keytype last){
	int r = first;
	while(r <= (last-1)/2){
		int left = r*2 + 1;
		int right = r*2 + 2;	
		if(left == last){
			if(arr[r].key < arr[left].key){
				swap(&arr[r], &arr[left]);
			}
			r = last;
		}else if(arr[r].key < arr[left].key && arr[left].key >= arr[right].key){
			swap(&arr[r], &arr[left]);
			r = left;
		}else if(arr[r].key < arr[right].key && arr[left].key < arr[right].key){
			swap(&arr[r], &arr[right]);
			r = right;
		}else {
			r = last;
		}
	}
}

void HeapSort(recordtype arr[], int n){
	for(int i = (n-2)/2; i >= 0; --i){
		pushDown(arr, i, n-1);
	}
	for(int i = n - 1; i >= 2; --i){
		swap(&arr[0], &arr[i]);
		pushDown(arr, 0, i-1);
	}
	swap(&arr[0], &arr[1]);
}

int main(){
	recordtype arr[100];
	int n;
	printf("Thuat toan Heap Sort:\n");
	readFromFile(arr, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(arr, n);
	printf("Du lieu sau khi sap xep:\n");
	HeapSort(arr, n);
	printData(arr, n);
	return 0;
}
