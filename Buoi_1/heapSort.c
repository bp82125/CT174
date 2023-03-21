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

void pushDown(RecordType arr[], int first, int last){
	int r = first;  // first lan luot la cac nut trong, last la nut cuoi cung
	while(r <= (last-1)/2){ // lap trong khi r van con la nhung nut trong
		if(last == 2*r + 1){ // truong hop r la nut trong co 1 la - n chan
			if(arr[r].key < arr[last].key) // neu nho hon thi hoan doi, sau do ket thuc thu tuc pushDown
					swap(&arr[r], &arr[last]);
			r = last;
		}else if(arr[r].key < arr[2*r + 1].key && arr[2*r + 1].key >= arr[2*r + 2].key){ // truong hop nut trong co con la nut trong
			swap(&arr[r], &arr[2*r + 1]); // khoa nut con trai >= khoa nut con phai
			r = 2*r + 1; // doi gia tri va lan luot xet pushDown tiep nut con vua hoan doi
		}else if(arr[r].key < arr[2*r + 2].key){ // truong hop nut trong co con la nut trong
			swap(&arr[r], &arr[2*r + 2]); // khoa nut con phai > khoa nut con trai
			r = 2*r + 2;// doi gia tri va lan luot xet pushDown tiep nut con vua hoan doi
		}else{
			r = last; // neu nut dang xet thoa tat ca dieu kien thi bo qua thu tuc pushDown
		}
	}
}

void HeapSort(RecordType arr[], int n){ //heapsort voi mang co n phan tu
	for(int i = (n-2)/2; i >= 0; --i){ // lan luot pushDown cac nut trong
		pushDown(arr, i, n-1);
	}
	for(int i = n - 1; i >= 2; --i){
		swap(&arr[0], &arr[i]);
		pushDown(arr, 0, i - 1);
	}
	swap(&arr[0], &arr[1]);
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
	HeapSort(arr, n);
	
	printf("Sau khi sap xep:\n");
	
	print_list(arr, n);
	
	return 0;
}
