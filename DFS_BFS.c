#include <stdio.h>
#include <stdlib.h>

// -------------------- Graph (adjacency list) --------------------

typedef struct Node {
    int v;
    struct Node* next;
} Node;

// adjacency list'i başlat
Node** create_graph(int n) {
    Node** adj = (Node**)calloc(n, sizeof(Node*));
    return adj;
}

// kenar ekle (çift yönlü)
void add_edge(Node** adj, int u, int v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->v = v;
    n->next = adj[u];
    adj[u] = n;
}

// -------------------- DFS --------------------
void dfs_visit(int u, int* visited, Node** adj, int* comp, int* idx) {
    visited[u] = 1;
    comp[(*idx)++] = u;

    Node* cur = adj[u];
    while (cur) {
        int w = cur->v;
        if (!visited[w]) dfs_visit(w, visited, adj, comp, idx);
        cur = cur->next;
    }
}

// -------------------- BFS --------------------
typedef struct Queue {
    int* data;
    int front, back, cap;
} Queue;

Queue* q_create(int cap) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(cap * sizeof(int));
    q->front = 0;
    q->back = 0;
    q->cap = cap;
    return q;
}
int q_empty(Queue* q) { return q->front == q->back; }
void q_push(Queue* q, int x) { q->data[q->back++] = x; }
int q_pop(Queue* q) { return q->data[q->front++]; }
void q_free(Queue* q) { free(q->data); free(q); }

// BFS temelinde bir bileşeni keşfeder
void bfs_visit(int start, int* visited, Node** adj, int* comp, int* idx) {
    Queue* q = q_create(1000); // kapasite ihtiyaca göre artırılabilir
    visited[start] = 1;
    q_push(q, start);

    while (!q_empty(q)) {
        int u = q_pop(q);
        comp[(*idx)++] = u;

        Node* cur = adj[u];
        while (cur) {
            int w = cur->v;
            if (!visited[w]) {
                visited[w] = 1;
                q_push(q, w);
            }
            cur = cur->next;
        }
    }
    q_free(q);
}

// -------------------- Ana --------------------
int main() {
    // Örnek graf: edges = { {0,1}, {1,2}, {3,4} } -> iki bileşen: {0,1,2} ve {3,4}
    int n = 5;
    int edges[][2] = {
        {0,1},
        {1,2},
        {3,4}
    };
    int m = sizeof(edges)/sizeof(edges[0]);

    Node** adj = create_graph(n);
    for (int i = 0; i < m; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        add_edge(adj, u, v);
        add_edge(adj, v, u); // eş yönlü
    }

    // DFS ile bağlı bileşenler
    int* visited_dfs = (int*)calloc(n, sizeof(int));
    int* component = (int*)malloc(n * sizeof(int));
    int idx;

    printf("DFS ile bağlı bileşenler:\n");
    int comp_id = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited_dfs[i]) {
            idx = 0;
            dfs_visit(i, visited_dfs, adj, component, &idx);

            printf("Component %d (DFS): ", comp_id++);
            for (int j = 0; j < idx; ++j) {
                if (j) printf(", ");
                printf("%d", component[j]);
            }
            printf("\n");
        }
    }

    // BFS ile bağlı bileşenler
    int* visited_bfs = (int*)calloc(n, sizeof(int));
    printf("\nBFS ile bağlı bileşenler:\n");
    comp_id = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited_bfs[i]) {
            idx = 0;
            bfs_visit(i, visited_bfs, adj, component, &idx);

            printf("Component %d (BFS): ", comp_id++);
            for (int j = 0; j < idx; ++j) {
                if (j) printf(", ");
                printf("%d", component[j]);
            }
            printf("\n");
        }
    }

    // Temizlik
    for (int i = 0; i < n; ++i) {
        Node* cur = adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adj);
    free(visited_dfs);
    free(visited_bfs);
    free(component);

    return 0;
}
