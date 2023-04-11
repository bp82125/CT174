#include <stdio.h>

#define MAXN 100

typedef struct Edge {
	int start, end;
	float length;
	int visited;
} Edge;

typedef struct Graph {
	Edge A[MAXN][MAXN];
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

int main() {
	Graph G;

	read_file("data.txt", &G);

	printf("%d", G.n);

	in_ma_tran(G);

	return 0;

}
