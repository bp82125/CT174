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

int findPivot(RecordType arr[], int bot, int top){
	int k = bot + 1;
	int firstKey = arr[bot].key;
	
	while(k <= top && arr[k].key == firstKey){
		k++;
	}
	
	if(k > top) return -1; //truong hop khong tim duoc phan tu khac nhau thu 2
	if(arr[k].key > firstKey) return bot; 
	return k; 
}

int partition(RecordType arr[], int bot, int top, int pivot){
	int L = bot;
	int R = top;
	
	while(L <= R){
		while(arr[L].key <= pivot) L++;
		while(arr[R].key > pivot) R--;
		if(L < R) swap(&arr[L], &arr[R]);
	}
	
	return L;
}

void QuickSort(RecordType arr[], int bot, int top){
	int pivot;
	int pivotIndex = findPivot(arr, bot , top); 
	
	if(pivotIndex != -1){
		pivot = arr[pivotIndex].key;
		int k = partition(arr, bot, top, pivot);
		QuickSort(arr, bot, k - 1);
		QuickSort(arr, k, top);
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
	QuickSort(arr, 0, n - 1);
	
	printf("Sau khi sap xep:\n");
	
	print_list(arr, n);
	
	return 0;
}
