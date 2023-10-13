#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max 100

typedef struct {
    int items[max];
    int front;
    int rear;
} Queue;


typedef struct {
    int vertices;
    int** adjacency_matrix;
} Graph;


Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}


bool isEmpty(Queue* queue) {
    return queue->front == -1;
}


void enqueue(Queue* queue, int value) {
    if (queue->rear == max - 1) {
        printf("Queue is full\n");
    } else {
        if (queue->front == -1) {
            queue->front = 0;
        }
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}


int dequeue(Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}


Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;


    graph->adjacency_matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_matrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjacency_matrix[i][j] = 0;
        }
    }

    return graph;
}


void addEdge(Graph* graph, int start, int end) {
    graph->adjacency_matrix[start][end] = 1;
    graph->adjacency_matrix[end][start] = 1; 
}


void bfs(Graph* graph, int startVertex) {
    Queue* queue = createQueue();
    bool visited[max] = {false};

    printf("BFS traversal starting from vertex %d:\n", startVertex);

    visited[startVertex] = true;
    printf("%d ", startVertex);
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjacency_matrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                printf("%d ", i);
                enqueue(queue, i);
            }
        }
    }

    free(queue);
}

int main() {
    int vertices;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    printf("Add edges: \n");
    int e, u, v;
    printf("Enter the number of edges: ");
    scanf("%d", &e);
    for (int j = 0; j < e; j++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int startVertex;
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);
    bfs(graph, startVertex);

    for (int i = 0; i < vertices; i++) {
        free(graph->adjacency_matrix[i]);
    }
    free(graph->adjacency_matrix);
    free(graph);

    return 0;
}
