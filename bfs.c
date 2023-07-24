#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

struct Queue {
    int items[MAX_NODES];
    int front;
    int rear;
};

void initializeQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isQueueEmpty(struct Queue* q) {
    if (q->rear == -1)
        return true;
    return false;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX_NODES - 1)
        printf("Queue is full!\n");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q) {
    int item;
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = -1;
            q->rear = -1;
        }
        return item;
    }
}

struct Graph {
    int adjMatrix[MAX_NODES][MAX_NODES];
    int numNodes;
};

void initializeGraph(struct Graph* g, int numNodes) {
    g->numNodes = numNodes;
    for (int i = 1; i <= numNodes; i++) {
        for (int j = 1; j <= numNodes; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(struct Graph* g, int src, int dest) {
    g->adjMatrix[src][dest] = 1;
}

void bfs(struct Graph* g, int startNode) {
    bool visited[MAX_NODES] = { false };

    struct Queue q;
    initializeQueue(&q);

    visited[startNode] = true;
    enqueue(&q, startNode);

    while (!isQueueEmpty(&q)) {
        int current = dequeue(&q);
        printf("%d ", current);

        for (int i = 0; i < g->numNodes; i++) {
            if (g->adjMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
}

int main() {
    struct Graph graph;
    int numNodes, numEdges;
    int src, dest;

    printf("Enter the number of Vertices: ");
    scanf("%d", &numNodes);

    initializeGraph(&graph, numNodes);

    printf("Enter the number of Arcs: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        printf("Enter the source and destination of Arcs %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(&graph, src, dest);
    }

    int startNode;
    printf("Enter the starting Vertices for BFS: ");
    scanf("%d", &startNode);

    printf("BFS traversal : ");
    bfs(&graph, startNode);

    return 0;
}
