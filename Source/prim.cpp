#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 1000
#define MAX_VERTICES 100



//prim 알고리즘의 구조체
typedef struct GraphType {
	int n;
	int weight[7][7];
}GraphType;

int distance[7];
int selected[7];

//방문하지 않은 정점중에서 가장 가까운 정점 리턴
int get_min_vertex(int n) {
	int v = 0, i;

	for (i = 0; i < n; i++) {
		if (!selected[i]) { // 방문하지 않았다면
			v = i; //v 선택
			break;
		}
	}

	for (i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v])) {
			//방문하지 않았고 정점v보다 더 작은 거리를 가진 정점이있다면 교체
			v = i;
		}
	}
	return v;
}

void prim(GraphType* g, int start) {
	int i, u, v;

	for (int u = 0; u < g->n; u++) {
		distance[u] = INF;
		selected[u] = 0;
	}
	distance[start] = 0;

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE; // 방문

		if (distance[u] == INF) {
			return;
		}

		printf("정점 %c 추가\n", u + 65);

		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
				}
			}
		}
	}
}
int main() {
	GraphType g = { 7,
		{   {0,7,INF,5,INF,INF,INF},
			{7,0,8,9,7,INF,INF},
			{INF,8,0,INF,5,INF,INF},
			{5,9,INF,0,15,6,INF},
			{INF,7,5,15,0,8,9},
			{INF,INF,INF,6,8,0,11},
			{INF,INF,INF,INF,9,11,0}
		}
	};
	prim(&g, 0);
}