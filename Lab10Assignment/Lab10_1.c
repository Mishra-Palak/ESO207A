#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000
#define MAX_EDGES 100000

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

int parent[MAX_NODES];
int rank[MAX_NODES];

void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find_set(int x) {
    int root = x;

    while (parent[root] != root) {
        root = parent[root];
    }

    while (x != root) {
        int next = parent[x];
        parent[x] = root;
        x = next;
    }

    return root;
}


void union_set(int x, int y) {
    int px = find_set(x);
    int py = find_set(y);

    if (rank[px] > rank[py]) {
        parent[py] = px;
    } else {
        parent[px] = py;
        if (rank[px] == rank[py]) {
            rank[py]++;
        }
    }
}

int cmpfunc(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void kruskal(Edge* edges, int n, int m) {
    int edge_count = 0;
    int index = 0;
    Edge result[MAX_NODES];

    make_set(n);

    qsort(edges, m, sizeof(Edge), cmpfunc);

    while (edge_count < n - 1 && index < m) {
        Edge next_edge = edges[index++];

        int x = find_set(next_edge.src);
        int y = find_set(next_edge.dest);

        if (x != y) {
            result[edge_count++] = next_edge;
            union_set(x, y);
        }
    }

    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < edge_count; i++) {
        printf("(%d, %d) -> %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

int main() {
    int n, m;
    Edge edges[MAX_EDGES];

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &m);

    printf("Enter the edges as source, destination, weight:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    kruskal(edges, n, m);

    return 0;
}
