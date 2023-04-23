#include <stdio.h>
#include <float.h>

#define MAXN 100

typedef struct Edge {
	int start, end;
	float length;
	int visited;
} Edge;

typedef struct Graph {
	Edge A[MAXN][MAXN]; //ma tran trong so, ung voi A[i][j] se co mot Edge, voi start = i, end = j, length va vistied
	int n;
} Graph;

void read_file(char file_name[], Graph *pG) {
	int i, j;
	FILE *f;
	f = fopen(file_name, "r");
	if (f == NULL) {
		printf("Loi mo file!!!\n");
		return;
	}

	fscanf(f, "%d", &pG->n); // Doc so dinh cua do thi n

	for (i = 0; i < pG->n; i++) {
		for (j = 0; j < pG->n; j++) {
			float temp;
			fscanf(f, "%f", &temp);
			pG->A[i][j].length = temp;
			pG->A[i][j].start = i;
			pG->A[i][j].end = j;
			pG->A[i][j].visited = 0;;
		}
	}
	fclose(f);
}

void in_ma_tran(Graph G) {
	int i, j;
	printf("\nMa tran TRONG SO cua do thi\n");
	for (i = 0; i < G.n; i++) {
		for (j = 0; j < G.n; j++)
			printf(" %c%c =%5.2f  ", G.A[i][j].start + 97, G.A[i][j].end + 97, G.A[i][j].length);
		printf("\n");
	}
}

//Ham tim do dai nho nhat cua tat ca cac canh chua xet
float minLength(Graph *pG){
	float min = FLT_MAX;
	for(int i = 0; i < pG->n; ++i){
		for(int j = 0; j < pG->n; ++j){
			if(i!=j && pG->A[i][j].length < min && !pG->A[i][j].visited){
				min = pG->A[i][j].length;
			}
		}
	}
	return min;
}

float totalValue; //Tong gia tri
float lowerBound; //Can duoi
float best_dist; // Gia tri nho nhat tam thoi
Edge current[MAXN]; //Mang luu tu thu tu cac canh tam thoi
Edge solution[MAXN]; //Mang luu tru thu tu cac canh dap an

//Tim can duoi theo cong thuc: CT = (n - soDinhDaDuocChon) * gtri canh chua xet nho nhat hien tai
float findLowerBound(Graph G, int numVertices){
	return totalValue + (G.n - numVertices) * minLength(&G);
}

//Kiem tra khi them mot dinh vao co tao chu trinh
int checkCycle(int numVertices,int nextVertex){
	int hasCycle = 0;
	int i = 0;
	//numVertices luu tru so dinh da duoc chon
	while(i < numVertices && !hasCycle){
		if(nextVertex == current[i].start){ //Kiem tra dinh da duoc them co xuat hien o dau moi canh chua
			hasCycle = 1;
		}else{
			i++;
		}
	}
	return hasCycle;
}


void updateSolution(Graph G){
	current[G.n - 1] = G.A[current[G.n - 2].end][current[0].start]; //Canh cuoi co start la end cua canh truoc va end la start cua canh dau tien
	totalValue += current[G.n - 1].length;
	
	if(best_dist > totalValue){
		best_dist = totalValue;
		for(int i = 0; i < G.n; ++i){
			solution[i] = current[i];
		}
	}
	totalValue -= current[G.n - 1].length; //quan trong la phai tru ra, ko se sai ket qua
	
}

void BranchAndBound(Graph G, int numVertices, int startVertex){
	for(int j = 0; j < G.n; ++j){
		if(startVertex != j && !G.A[startVertex][j].visited && !checkCycle(numVertices, j)){
			totalValue += G.A[startVertex][j].length;
			lowerBound = findLowerBound(G, numVertices + 1);
			
			if(lowerBound < best_dist){
				current[numVertices] = G.A[startVertex][j];
				G.A[startVertex][j].visited = 1;
				G.A[j][startVertex].visited = 1;
				
				if(numVertices == G.n - 2){ //Net da tat ca cac dinh
					updateSolution(G);
				}else{
					BranchAndBound(G, numVertices + 1, j);
				}
			}
			
			totalValue -= G.A[startVertex][j].length;
			G.A[startVertex][j].visited = 0;
			G.A[j][startVertex].visited = 0;
		}
	}
}

void reset(Graph G){
	for(int i = 0; i < G.n; ++i){
		for(int j = 0; j < G.n; ++j){
			G.A[i][j].visited = 0;
		}
	}
}

void printSolution(int maxVertices){
	float sum = 0.0;
	printf("Phuong an tim duoc:\n");
	
	for(int i = 0; i < maxVertices; ++i){
		printf("%c%c = %f\n", solution[i].start + 97, solution[i].end + 97, solution[i].length);
	}
	
	for(int i = 0; i < maxVertices; ++i){
		sum += solution[i].length;
		printf("%c -> ", solution[i].start + 97);
	}
	
	printf("%c\n", solution[0].start + 97);
	printf("Tong do dai chu trinh: %f\n", sum);
}

int main() {
	Graph G;

	read_file("data.txt", &G);

	printf("%d", G.n);

	in_ma_tran(G);

	totalValue = 0.0;
	best_dist = FLT_MAX;
	lowerBound = 0.0;
	
	printf("Hay chon diem xuat phat, tu %c -> %c: ", 0+97, G.n - 1 + 97);
	char c; 
	scanf("%c", &c);
	
	BranchAndBound(G, 0, (int)(c - 97));
	
	printSolution(G.n);
	
	return 0;

}
