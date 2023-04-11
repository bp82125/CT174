#include <stdio.h>

typedef struct Edge{
	int start, end;
	float length;
}Edge;

typedef struct Graph{
	Edge edges[100];
	int n, m;
	float size;
}Graph;

void init_graph(Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	pG->size = 0.0;
}

void init_forest(int parent[], int n){
	for(int i = 0; i < n; ++i){
		parent[i] = i;
	}
}

int findRoot(int parent[], int u){
	if(u == parent[u]){
		return u;
	}
	return findRoot(parent, parent[u]);
}

int chuTrinh(int r_dau, int r_cuoi){
	return r_dau == r_cuoi;
}

void update_forest(int parent[], int r1, int r2){
	parent[r2] = r1; 
}

void readFromFile(Graph *pG){
	FILE *f;
	
	f = fopen("tsp_greedy.txt", "r");
	int n;
	fscanf(f, "%d", &n);
	
	int k = 0;
	float temp;
	for(int i = 0; i < n; ++i){
		for(int j = i; j < n; ++j){

			if(i == j) for(int t = 0; t<=j;++t) fscanf(f, "%f", &temp);
			else{
				fscanf(f, "%f", &temp);	
				pG->edges[k].start = i;
				pG->edges[k].end = j;
				pG->edges[k].length = temp;
				k++;	
			}
		}
	}
	
	fclose(f);
	pG->n = n;
	pG->m = k;
	pG->size = 0.0;
}

void print_edge(Graph G){
	for(int i = 0; i < G.m; ++i){
		printf("%3d | %c%c = %8.2f\n", i+1, G.edges[i].start + 97, G.edges[i].end + 97, G.edges[i].length);
	}
	if(G.size != 0.0) 
		printf("Tong do dai cac canh = %5.2f\n", G.size);
}

void swap(Edge *a, Edge *b){
	Edge temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(Graph *pG){
	for(int i = 0; i < pG->m - 1; ++i){
		for(int j = pG->m - 1; j > i; --j){
			if(pG->edges[i].length > pG->edges[j].length){
				swap(&pG->edges[i], &pG->edges[j]);
			}
		}
	}
}

int dinhcap3(Graph G, Edge new){
	int count_start = 1;
	int count_end = 1;
	
	for(int i = 0; i < G.m; ++i){
		if(G.edges[i].start == new.start || G.edges[i].end == new.start){
			count_start++;
		}
		
		if(G.edges[i].start == new.end || G.edges[i].end == new.end){
			count_end++;
		}
	}
	
	return count_start >= 3 || count_end >= 3;
}

void Greedy(Graph G, Graph *Res, int parent[]){
	init_graph(Res, G.n);
	
	init_forest(parent, G.n);
	
	
	int root_start, root_end;
	
	int i;
	for(i = 0; i < G.m && Res->m < G.n - 1; ++i){
		root_start = findRoot(parent, G.edges[i].start);
		root_end = findRoot(parent, G.edges[i].end);
		
		if(!dinhcap3(*Res, G.edges[i]) && !chuTrinh(root_start, root_end)){
			Res->edges[Res->m] = G.edges[i];
			Res->m++;
			Res->size += G.edges[i].length;
			update_forest(parent, root_start, root_end);
		}
	}
	
	for(; i < G.m; ++i){
		root_start = findRoot(parent, G.edges[i].start);
		root_end = findRoot(parent, G.edges[i].end);
		if(!dinhcap3(*Res, G.edges[i]) && chuTrinh(root_start, root_end)){
			Res->edges[Res->m] = G.edges[i];
			Res->m++;
			Res->size += G.edges[i].length;
			break;
		}
		
	}
}

void print_path(Graph G){
	
	int mark[G.n];
	
	for(int i = 0; i < G.n; ++i){
		mark[i] = 0;
	}

	int start = G.edges[0].start;
	int end = G.edges[0].end;
	
	mark[0] = 1;
	
	printf("Chu trinh: ");
	printf("%c -> ", start + 97);
	printf("%c -> ", end + 97);
	
	int count = 2;
	while(count < G.n){
		for(int e = 0; e < G.n; ++e){
			if(!mark[e]){
				if(end == G.edges[e].start || end == G.edges[e].end){
					end = G.edges[e].start + G.edges[e].end - end;
					printf("%c -> ", end + 97);
					mark[e] = 1;
					break;
				}
			}
		}
		count++;
	}
	
	printf("%c\n", start + 97);
}

int main(){
	printf("Phuong an TSP dung thuat toan Greedy:\n");
	
	Graph G;
	readFromFile(&G);
	
	printf("Danh sach cac canh cua do thi:\n");
	print_edge(G);
	
	printf("Danh sach cac canh cua do thi sau khi sap xep:\n");
	bubbleSort(&G);
	print_edge(G);
	
	printf("PHUONG AN:\n");
	Graph Res;
	
	int parent[G.n];
	
	Greedy(G, &Res, parent);
	
	print_edge(Res);
	
	print_path(Res);
	
	return 0;
}
