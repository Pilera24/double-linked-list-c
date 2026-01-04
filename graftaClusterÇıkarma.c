#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int v;
    struct Node* next;
} Node;

// Add edge to adjacency list (undirected)
void add_edge(Node** adj, int u, int v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->v = v;
    n->next = adj[u];
    adj[u] = n;
}

// DFS to mark component
void dfs(int u, int* visited, Node** adj, int* component, int* idx) {
    visited[u] = 1;
    component[(*idx)++] = u;
    Node* cur = adj[u];
    while (cur) {
        int w = cur->v;
        if (!visited[w]) dfs(w, visited, adj, component, idx);
        cur = cur->next;
    }
}

int main() {

    int n = 5; // number of nodes (0..n-1)
    int edges[][2] = {
        {0,1},
        {1,2},
        {3,4}
    };
    int m = sizeof(edges)/sizeof(edges[0]);

    Node** adj = (Node**)calloc(n, sizeof(Node*));
    for (int i = 0; i < m; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        add_edge(adj, u, v);
        add_edge(adj, v, u);
    }

    int* visited = (int*)calloc(n, sizeof(int));
    int* component = (int*)malloc(n * sizeof(int)); 
    int comp_id = 0;

    printf("Clusters (connected components):\n");

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int idx = 0;
            dfs(i, visited, adj, component, &idx);

            // Print this component
            printf("Component %d: ", comp_id++);
            for (int j = 0; j < idx; ++j) {
                if (j) printf(", ");
                printf("%d", component[j]);
            }
            printf("\n");
        }
    }

    // Cleanup
    for (int i = 0; i < n; ++i) {
        Node* cur = adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adj);
    free(visited);
    free(component);

    return 0;
}
