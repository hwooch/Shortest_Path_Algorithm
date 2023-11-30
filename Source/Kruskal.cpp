#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 1000
#define MAX_VERTICES 100

//printf("a--b---c"); printf("\n");
//printf("| /��  |"); printf("\n");
//printf("|/   ��|"); printf("\n");
//printf("D------E"); printf("\n");
//printf(" ��   / ��"); printf("\n");
//printf("   ��F ---G "); printf("\n");


// �θ� ���
int parent[MAX_VERTICES];
// �ʱ�ȭ
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// ��Ʈ
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}
// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// ��� a�� ��Ʈ�� ã�´�.
	int root2 = set_find(b);	// ��� b�� ��Ʈ�� ã�´�.
	if (root1 != root2) 	// ���Ѵ�.
		parent[root1] = root2;
}
// ������ ��Ÿ���� ����ü
struct Edge {
	int start, end, weight;
};
typedef struct GraphType {
	int n;	// ������ ����
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;
// �׷��� �ʱ�ȭ
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}
// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType* g, int n)
{
	int edge_accepted = 0;	// ������� ���õ� ������ ��	
	int uset, vset;			// ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;

	set_init(n);				// ���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	int i = 0;
	while (edge_accepted < n - 1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// ���� u�� ���� ��ȣ
		vset = set_find(e.end);		// ���� v�� ���� ��ȣ
		if (uset != vset) {			// ���� ���� ������ �ٸ���
			printf("���� (%c,%c) %d ����\n", e.start + 64, e.end + 64, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
		}
		i++;
	}
}

int main() {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g, 1, 2, 7);
	insert_edge(g, 1, 4, 5);
	insert_edge(g, 2, 3, 8);
	insert_edge(g, 2, 4, 9);
	insert_edge(g, 2, 5, 7);
	insert_edge(g, 3, 5, 5);
	insert_edge(g, 4, 5, 15);
	insert_edge(g, 4, 6, 6);
	insert_edge(g, 5, 6, 8);
	insert_edge(g, 5, 7, 9);
	insert_edge(g, 6, 7, 11);

	int v = 7; // ������ ����
	kruskal(g, v);
	free(g);
}