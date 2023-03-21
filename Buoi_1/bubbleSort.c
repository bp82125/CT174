#include <stdio.h>

typedef struct RecordType{
	int key;
	float value;
}RecordType;

void swap(RecordType *a, RecordType *b){
	RecordType temp = *a;
	*a = *b;
	*b = temp;
}

void print_list(RecordType arr[], int size){
	for(int n = 0; n < size; ++n){
		printf("%d %f\n", arr[n].key, arr[n].value);
	}
}

void BubbleSort(RecordType arr[], int size){
	for(int i = 0; i< size - 1; ++i){
		for(int j = size - 1; j > i ; --j){
			if(arr[j].key < arr[j - 1].key){
				swap(&arr[j], &arr[j-1]);
			}
		}
	}
}

int main(void){
	RecordType arr[20];
	
	freopen("data.txt", "r", stdin);
	
	int n = 0;
	while(2 == scanf("%d%f", &arr[n].key, &arr[n].value)){
		n++;
	}
	
	printf("Thuat toan\n");
	
	printf("Truoc khi sap xep:\n");
	
	print_list(arr, n);
	
	//Thuat toan sap xep
	BubbleSort(arr, n);
	
	printf("Sau khi sap xep:\n");
	
	print_list(arr, n);
	
	return 0;
}
