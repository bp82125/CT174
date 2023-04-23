#include <stdio.h>
#include <float.h>

#define MAXN 100

typedef struct Edge{
	int u, v;
	float w;
	int visited;
}Edge;

typedef struct Graph{
	Edge A[MAXN][MAXN];
	int n;
}Graph;

void readFromFile(Graph *pG){
	FILE *f = fopen("TSP.txt", "r");
	if(f==NULL){
		printf("Loi mo file\n");
		return;
	}
	
	fscanf(f, "%d", &pG->n);
		for(int i = 0; i < pG->n; ++i){
			for(int j = 0; j < pG->n; ++j){
				float temp;
				fscanf(f, "%f", &temp);
				pG->A[i][j].u = i;
				pG->A[i][j].v = j;
				pG->A[i][j].w = temp;
				pG->A[i][j].visited = 0;	
			}
		}
	fclose(f);
}

void printGraph(Graph G){
	for(int i = 0; i < G.n; ++i){
		for(int j = 0; j < G.n;++j){
			printf("%c%c = %5.2f ", i+97, j+97, G.A[i][j].w);
		}
		printf("\n");
	}
}

float totalValue;
float lowerBound;
float bestValue;
Edge solution[MAXN];
Edge temp[MAXN];

float minValue(Graph G){
	float min = FLT_MAX;
	for(int i = 0; i < G.n; ++i){
		for(int j = 0; j < G.n;++j){
			if(G.A[i][j].w < min && i!=j && !G.A[i][j].visited){
				min = G.A[i][j].w;
			}
		}
	}
	return min;
}

void createRootNode(Graph G){
	totalValue = 0;
	bestValue = FLT_MAX;
}

float checkCycle(int numV, int nextV){
	int hasCycle = 0;
	int i = 0;
	while(i < numV && !hasCycle){
		if(nextV == temp[i].u){
			hasCycle = 1;
		}else{
			i++;
		}
	}
	return hasCycle;
}

void printSolution(Graph G){
	printf("Phuong an cho TSP, su dung Branch And Bound la:\n");
	float sumLength = 0.0f;
	for(int i = 0; i < G.n; ++i){
		sumLength += solution[i].w;
		printf("%c%c = %5.2f\n", solution[i].u + 97, solution[i].v + 97, solution[i].w);
	}
	printf("Duong di: ");
	for(int i = 0; i < G.n - 1; ++i){
		printf("%c -> ", solution[i].u + 97);
	}
	printf("%c -> %c\n", solution[G.n-1].u + 97, solution[G.n-1].v + 97);
	printf("Chieu dai duong di: %.2f\n", sumLength);
}

void updateSolution(Graph G){
	temp[G.n - 1] = G.A[temp[G.n-2].v][temp[0].u];
	totalValue += temp[G.n - 1].w;
	
	if(bestValue > totalValue){
		bestValue = totalValue;
		
		for(int i = 0; i < G.n; ++i){
			solution[i] = temp[i];
		}
	}
	
	totalValue -= temp[G.n - 1].w;
}

void BranchAndBound(Graph G, int numV, int startV){
	for(int nextV = 0; nextV < G.n; ++nextV){
		if(startV != nextV && !G.A[startV][nextV].visited && !checkCycle(numV, nextV)){
			totalValue += G.A[startV][nextV].w;
			lowerBound = totalValue + (G.n - numV - 1) * minValue(G);
			
			if(lowerBound < bestValue){
				temp[numV] = G.A[startV][nextV];
				G.A[startV][nextV].visited = 1;
				G.A[nextV][startV].visited = 1;
				
				if(numV == G.n - 2){
					updateSolution(G);
				}else{
					BranchAndBound(G, numV + 1, nextV);
				}
			}
			
			totalValue -= G.A[startV][nextV].w;
			G.A[startV][nextV].visited = 0;
			G.A[nextV][startV].visited = 0;
		}
	}
}


int main(){
	Graph G;
	readFromFile(&G);
	printGraph(G);
	
	printf("\nHay nhap dinh ban muon xuat phat, tu %c -> %c:\n", 97, 97 + G.n - 1);
	int c;
	scanf("%c", &c);
	createRootNode(G);
	BranchAndBound(G, 0, c-97);
	printSolution(G);
	return 0;
}
