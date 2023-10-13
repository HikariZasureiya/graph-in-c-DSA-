#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct Graph {
    int numNodes;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    bool visited[MAX_NODES];
} Graph;

void initializeGraph(Graph *g, int n) {
    g->numNodes = n;
    for (int i = 0; i < g->numNodes; i++) {
        g->visited[i] = false;
        for (int j = 0; j < g->numNodes; j++) {
            g->adjacencyMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph *g, int u, int v) {
    g->adjacencyMatrix[u][v] = 1;  // Assuming unweighted graph, 1 indicates an edge
    g->adjacencyMatrix[v][u] = 1;  // For undirected graph, add edge in both directions
}

void dfs(Graph *g, int node) {
    g->visited[node] = true;
    printf("%d ", node);

    for (int i = 0; i < g->numNodes; i++) {
        if (g->adjacencyMatrix[node][i] == 1 && !g->visited[i]) {
            dfs(g, i);
        }
    }
}

int main() {
    int n, e;  // n = number of nodes, e = number of edges
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &e);

    Graph graph;
    initializeGraph(&graph, n);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&graph, u, v);
    }

    int startNode;
    printf("Enter the starting node for DFS: ");
    scanf("%d", &startNode);

    printf("DFS traversal starting from node %d:\n", startNode);
    dfs(&graph, startNode);

    return 0;
}
