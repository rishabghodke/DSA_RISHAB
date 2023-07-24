#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

struct Stack {
    int items[MAX_NODES];
    int top;
};

void initializeStack(struct Stack* s) {
    s->top = -1;
}

bool isStackEmpty(struct Stack* s) {
    if (s->top == -1)
        return true;
    return false;
}

void push(struct Stack* s, int value) {
    if (s->top == MAX_NODES - 1)
        printf("Stack is full!\n");
    else {
        s->top++;
        s->items[s->top] = value;
    }
}

int pop(struct Stack* s) {
    int item;
    if (isStackEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    } else {
        item = s->items[s->top];
        s->top--;
        return item;
    }
}

struct Graph {
    int adjMatrix[MAX_NODES][MAX_NODES];
    int numNodes;
};

void initializeGraph(struct Graph* g, int numNodes) {
    g->numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(struct Graph* g, int src, int dest) {
    g->adjMatrix[src][dest] = 1;
    g->adjMatrix[dest][src] = 1;
}

void dfs(struct Graph* g, int startNode) {
    bool visited[MAX_NODES] = { false };

    struct Stack s;
    initializeStack(&s);

    visited[startNode] = true;
    push(&s, startNode);

    while (!isStackEmpty(&s)) {
        int current = pop(&s);
        printf("%d ", current);

        for (int i = 0; i < g->numNodes; i++) {
            if (g->adjMatrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                push(&s, i);
            }
        }
    }
}

int main() {
    struct Graph graph;
    int numNodes, numEdges;
    int src, dest;

    printf("Enter the number of nodes : ");
    scanf("%d", &numNodes);

    initializeGraph(&graph, numNodes);

    printf("Enter the number of edges : ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        printf("Enter the source and destination of edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(&graph, src, dest);
    }

    int startNode;
    printf("Enter the starting node: ");
    scanf("%d", &startNode);

    printf("DFS traversal : ");
    dfs(&graph, startNode);

    return 0;
}
