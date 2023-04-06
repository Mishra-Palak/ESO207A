#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

typedef struct Edge {
    int u, v, weight;
} Edge;

typedef struct Heap {
    int size;
    Edge data[MAX_VERTICES];
} Heap;

Heap* createHeap() {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->size = 0;
    return heap;
}

void insertHeap(Heap* heap, Edge edge) {
    int i = heap->size;
    heap->data[i] = edge;
    heap->size++;
    while (i > 0 && heap->data[(i-1)/2].weight > heap->data[i].weight) {
        Edge temp = heap->data[i];
        heap->data[i] = heap->data[(i-1)/2];
        heap->data[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

Edge removeHeap(Heap* heap) {
    Edge minEdge = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int i = 0;
    while (2*i+1 < heap->size) {
        int child = 2*i+1;
        if (child+1 < heap->size && heap->data[child+1].weight < heap->data[child].weight) {
            child++;
        }
        if (heap->data[i].weight > heap->data[child].weight) {
            Edge temp = heap->data[i];
            heap->data[i] = heap->data[child];
            heap->data[child] = temp;
            i = child;
        } else {
            break;
        }
    }
    return minEdge;
}

void prim(int n, int m, int r, int graph[][3], Edge tree[]) {
    int i, j;
    Heap* heap = createHeap();
    int visited[MAX_VERTICES] = {0};
    visited[0] = 1;
    for (j = 0; j < m; j++) {
        if (graph[j][0] == 0) {
            insertHeap(heap, (Edge) {0, graph[j][1], graph[j][2]});
        }
    }
    i = 0;
    while (i < n-1 && heap->size > 0) {
        Edge minEdge = removeHeap(heap);
        if (visited[minEdge.v]) {
            continue;
        }
        visited[minEdge.v] = 1;
        tree[i++] = minEdge;
        for (j = 0; j < m; j++) {
            if (graph[j][0] == minEdge.v && !visited[graph[j][1]]) {
                insertHeap(heap, (Edge) {graph[j][0], graph[j][1], graph[j][2]});
            } else if (graph[j][1] == minEdge.v && !visited[graph[j][0]]) {
                insertHeap(heap, (Edge) {graph[j][1], graph[j][0], graph[j][2]});
            }
        }
    }
    free(heap);
}

int main() {
    int n, m;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &m);
    int r = 2 + m / n;
    int graph[m][3];
    for (int i = 0; i < m; i++) {
        printf("Enter edge %d: ", i+1);
        int u, v;
        scanf("%d %d %d", &u, &v, &graph[i][2]);
        graph[i][0] = u-1;
        graph[i][1] = v-1;
    }
    Edge tree[MAX_VERTICES-1];
    prim(n, m, r, graph, tree);
    int i;
    for (i = 0; i < n-1; i++) {
        printf("(%d, %d) -> %d\n", tree[i].u+1, tree[i].v+1, tree[i].weight);
    }
    return 0;

}
