#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define min(a,b) ? a : b

typedef struct DoVat {
	char TenDV[20];
	float TL, GT, DG;
	int PA,SL;
} DoVat;

DoVat *ReadFromFile(float *W, int *n) {
	FILE *f;
	f = fopen("CaiBaLo2.txt", "r");

	fscanf(f, "%f", W);

	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));

	int i = 0;
	while (!feof(f)) {
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
		dsdv[i].PA = 0;
		dsdv[i].DG = 0.0;
		i++;
		dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat) * (i + 1));
	}

	
	*n = i-1; 
	fclose(f);
	return dsdv;
}

void swap(DoVat *x, DoVat *y) {
	DoVat temp = *x;
	*x = *y;
	*y = temp;
}

void PrintFromFile(DoVat *dsdv, int n, float W) {
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an Cai Ba Lo 2 su dung thuat toan Greedy can nhu sau:\n");
	printf("\nTrong luong cua ba lo = %-9.2f\n", W);

	printf("|---|--------------------|---------|---------|----------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     | T.luong | Gia Tri | So luong | Don Gia | Phuong An |\n");
	printf("|---|--------------------|---------|---------|----------|---------|-----------|\n");

	for (int i = 0; i < n; ++i) {
		printf("|%2d |%-20s|%9.2f|%9.2f|%5d     |%9.2f|%6d     |\n",
		       i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT,dsdv[i].SL, dsdv[i].DG, dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|--------------------|---------|---------|----------|---------|-----------|\n");
	printf("Phuong an theo thu tu giam dan: X(");
	for(int i = 0; i<n-1;++i){
		printf("%d, ", dsdv[i].PA);
	}
	printf("%d)\n", dsdv[n-1].PA);
	printf("Tong trong luong = %-9.2f\n", TongTL);
	printf("Tong gia tri = %-9.2f\n", TongGT);
}

void bubbleSort(DoVat *dsdv, int n){
	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; ++j){
			if(dsdv[i].DG < dsdv[j].DG){
				swap(&dsdv[i], &dsdv[j]);
			}
		}
	}
}

void greedy(DoVat *dsdv, int n, float W){
	
	for(int i = 0; i < n; ++i){
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
	}
	
	bubbleSort(dsdv, n);
	
	for(int i = 0; i < n; ++i){
		dsdv[i].PA = (int)W/dsdv[i].TL < dsdv[i].SL ? (int)W/dsdv[i].TL : dsdv[i].SL;
		W -= dsdv[i].PA * dsdv[i].TL;
	}
	
}

int main() {
	float W;
	int n;
	DoVat *dsdv = ReadFromFile(&W, &n);
	
	greedy(dsdv, n, W);
	
	PrintFromFile(dsdv, n, W);
}

