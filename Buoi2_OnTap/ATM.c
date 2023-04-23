#include <stdio.h>
#include <string.h>

typedef struct money{
	long value;
	char name[30];
	int solution;
}money;

void readFromFile(money arr[], int *n){
	FILE *f = fopen("ATM.txt", "r");
	if(f == NULL){
		printf("Loi mo file\n");
		return;
	}
	
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%ld", &arr[i].value);
		fgets(arr[i].name, 30, f);
		strtok(arr[i].name, "\n");
		i++;
		arr[i].solution = 0;
	}
	
	*n = i;
	fclose(f);
}

void swap(money *a, money *b){
	money temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(money arr[], int n){
	for(int i = 0; i <= n - 2; ++i){
		for(int j = n-1; j > i; --j){
			if(arr[j].value > arr[i].value){
				swap(&arr[j], &arr[i]);
			}
		}
	}
}

void Greedy(money arr[], int n, int M){
	for(int i = 0; i < n; ++i){
		if(M == 0) break;
		
		int res = M / arr[i].value;
		arr[i].solution = res;
		M -= res * arr[i].value;
	}
}

void printData(money arr[], int n){
	int count = 0;
	printf("|-----|---------|----------------------|-----------|\n");
	printf("| STT | Gia Tri |       Menh gia       | Phuong an |\n");
	printf("|-----|---------|----------------------|-----------|\n");
	for(int i = 0; i < n; ++i){
		count += arr[i].solution;
		printf("| %3d | %7d |%20s  | %5d     |\n", (i+1), arr[i].value, arr[i].name, arr[i].solution);
	}
	printf("|-----|---------|----------------------|-----------|\n");
	printf("Tong to tien: %d\n", count);
}

int main(){
	money arr[10];
	int n;
	readFromFile(arr, &n);
	BubbleSort(arr, n);
	
	long M;
	printf("Hay nhap vao so tien can rut:\n");
	scanf("%ld", &M);
	
	Greedy(arr, n, M);
	printf("Phuong an bai toan ATM su dung thuat toan Greedy\n");
	printData(arr, n);
	
	return 0;
}
