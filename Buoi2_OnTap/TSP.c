#include <stdio.h>

#define MAXN 100

typedef struct Edge{
	int u, v;
	float w;
}Edge;

typedef struct Graph{
	Edge edges[MAXN];
	int n, m;
	float length;
}Graph;

void readFromFile(Graph *pG){
	FILE *f = fopen("TSP.txt", "r");
	if (f == NULL){
		printf("Loi mo file:\n");
		return;
	}
	
	fscanf(f, "%d", &pG->n);
	int n = pG->n;
	
	
	int k = 0;
	for(int i = 0; i < n; ++i){
		for(int j = i; j < n; ++j){
			float temp;
			if(i == j) for(int t = 0; t <= j; ++t){
				fscanf(f, "%f", &temp);	
			}
			else {
				fscanf(f, "%f", &temp);
				pG->edges[k].u = i;
				pG->edges[k].v = j;
				pG->edges[k].w = temp;
				k++;
			}
		}
	}
	pG->m = k;
	pG->length = 0.0f;
	fclose(f);
}

void printData(Graph G){
	for(int e = 0; e < G.m; ++e){
		printf("%c%c = %.2f\n", G.edges[e].u + 97, G.edges[e].v + 97, G.edges[e].w);
	}
}

void swap(Edge *a, Edge *b){
	Edge temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(Graph *pG){
	for(int i = 0; i <= pG->m - 2; i++){
		for(int j = pG->m - 1; j > i; --j){
			if(pG->edges[j].w < pG->edges[i].w){
				swap(&pG->edges[j], &pG->edges[i]);
			}
		}
	}
}

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	pG->length = 0.0f;
}

void init_forest(int parent[], int n){
	for(int i = 0; i < n; ++i){
		parent[i] = i;
	}
}

int findRoot(int parent[], int n, int u){
	while(u != parent[u]){
		u = parent[u];
	}
	return parent[u];
}

int dinhcap3(Edge e, Graph Res){
	int count_u = 1;
	int count_v = 1;
	
	for(int i = 0; i < Res.m; ++i){
		if(Res.edges[i].u == e.u || Res.edges[i].v == e.u){
			count_u++;
		}
		if(Res.edges[i].u == e.v || Res.edges[i].v == e.v){
			count_v++;
		}
	}
	
	return count_u >= 3 || count_v >= 3;
}

int chuTrinh(int root_u, int root_v){
	return root_u == root_v;
}

void update_forest(int parent[], int root_u, int root_v){
	parent[root_v] = root_u;
}

void Greedy(Graph G, Graph *Res, int parent[]){
	init_graph(Res, G.n);
	init_forest(parent, G.n);
	int e;
	for(e = 0; e < G.m && Res->m < G.n - 1; ++e){
		int root_u = findRoot(parent, G.n, G.edges[e].u);
		int root_v = findRoot(parent, G.n, G.edges[e].v);
		
		if(!dinhcap3(G.edges[e], *Res) && !chuTrinh(root_u, root_v)){
			Res->edges[Res->m] = G.edges[e];
			Res->m++;
			Res->length += G.edges[e].w;
			update_forest(parent, root_u, root_v);
		}
	}
	
	for(; e < G.m; ++e){
		int root_u = findRoot(parent, G.n, G.edges[e].u);
		int root_v = findRoot(parent, G.n, G.edges[e].v);
		
		if(!dinhcap3(G.edges[e], *Res) && chuTrinh(root_u, root_v)){
			Res->edges[Res->m] = G.edges[e];
			Res->m++;
			Res->length += G.edges[e].w;
			update_forest(parent, root_u, root_v);
			break;
		}
	}
}

int main(){
	Graph G;
	readFromFile(&G);
	printf("Phuong an TSP su dung Greedy:\n");
	printf("Danh sach cac canh da sap xep:\n");
	printData(G);
	BubbleSort(&G);
	Graph Res;
	int parent[G.n + 1];
	Greedy(G, &Res, parent);
	printf("\nPhuong an tim duoc:\n");
	printData(Res);
	printf("\nTong chieu dai: %.2f\n", Res.length);
	return 0;
}
