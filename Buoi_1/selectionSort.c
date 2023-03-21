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

void SelectionSort(RecordType data[], int size){
	for(int i = 0; i < size - 1; ++i){
		int min = data[i].key;
		int min_idx = i;
		
		for(int j = i + 1; j<size;++j){
			if(data[j].key < min){
				min = data[j].key;
				min_idx = j;
			}
		}
		
		if(min_idx != i){
			swap(&data[i], &data[min_idx]);
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
	
	printf("Thuat toan Selection Sort\n");
	
	printf("Truoc khi sap xep:\n");
	
	print_list(arr, n);
	
	//Thuat toan sap xep
	SelectionSort(arr, n);
	
	printf("Sau khi sap xep:\n");
	
	print_list(arr, n);
	
	return 0;
}
