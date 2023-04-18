#include <stdio.h>

#define MAXN 100

typedef int keytype;
typedef float othertype;

typedef struct recordType{
	keytype key;
	othertype otherfields;
}recordType;

typedef struct List{
	recordType data[MAXN];
	int size;
}List;

void readFromFile(List *pL){
	FILE *f = fopen("data.txt", "r");
	
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%f", &pL->data[i].key, &pL->data[i].otherfields);
		i++;
	}
	pL->size = --i;
	fclose(f);
}

void printList(List L){
	printf("|-----|-------------|\n");
	printf("| Key | Otherfields |\n");
	printf("|-----|-------------|\n");
	
	for(int i = 0;  i < L.size; ++i){
		printf("| %3d | %8.2f    |\n", L.data[i].key, L.data[i].otherfields);
	}
	printf("|-----|-------------|\n");
}

void swap(recordType *a, recordType *b){
	recordType temp = *a;
	*a = *b;
	*b = temp;
}

void pushDown(List *pL, int first, int last){
	int current = first;
	int left = current * 2 + 1;
	int right = current * 2 + 2;
	
	if(left < last && pL->data[current].key > pL->data[left].key){
		current = left;
	}
	
	if(right < last && pL->data[current].key > pL->data[right].key){
		current = right;
	}
	
	if(current != first){
		swap(&pL->data[first], &pL->data[current]);
		pushDown(pL, current, last);
	}
}

void heapSort(List *pL){
	int n = pL->size;
	for(int i = (n - 2)/2; i >= 0; --i){
		pushDown(pL, i, n-1);
	}
	for(int i = n - 1; i >= 0; --i){
		swap(&pL->data[0], &pL->data[i]);
		pushDown(pL, 0, i - 1);
	}
	swap(&pL->data[0], &pL->data[1]);
}

int main(){
	List L;
	readFromFile(&L);
	printf("Thuat toan Heap Sort:\n");
	printf("Du lieu truoc khi sap xep:\n");
	printList(L);
	printf("Du lieu sau khi sap xep:\n");
	heapSort(&L);
	printList(L);
	return 0;
}


