#include <stdio.h>
#include <stdlib.h>

// Basit bir ADJACENCY LİST yapısından CSR'a dönüşüm
// Graf undirected olarak kabul edilir (kenarlar çift yönlü).

typedef struct Node {
    int v;
    struct Node* next;
} Node;

// adjacency list başlat
Node** create_graph(int n) {
    Node** adj = (Node**)calloc(n, sizeof(Node*));
    return adj;
}

// kenar ekle (undirected)
void add_edge(Node** adj, int u, int v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->v = v;
    n->next = adj[u];
    adj[u] = n;
}

// CSR yapısı
typedef struct {
    int* row_ptr;   // n+1 uzunluğunda
    int* col_ind;   // kenar sütun indeksleri
    int* val;       // değerler (bu durumda 1'ler)
    int nnz;        // non-zeros
} CSR;

// CSR'ı oluştur: adjacency list'ten
CSR* convert_to_csr(Node** adj, int n) {
    // İlk pass: nnz say
    int nnz = 0;
    for (int i = 0; i < n; ++i) {
        Node* cur = adj[i];
        while (cur) {
            nnz++;
            cur = cur->next;
        }
    }

    CSR* csr = (CSR*)malloc(sizeof(CSR));
    csr->nnz = nnz;
    csr->row_ptr = (int*)malloc((n + 1) * sizeof(int));
    csr->col_ind = (int*)malloc(nnz * sizeof(int));
    csr->val = (int*)malloc(nnz * sizeof(int));

    // İkinci pass: row_ptr ve col_ind doldur
    int idx = 0;
    csr->row_ptr[0] = 0;
    for (int i = 0; i < n; ++i) {
        Node* cur = adj[i];
        while (cur) {
            csr->col_ind[idx] = cur->v;
            csr->val[idx] = 1; // adjacency için 1
            idx++;
            cur = cur->next;
        }
        csr->row_ptr[i + 1] = idx;
    }

    return csr;
}

// CSR'ı yazdır
void print_csr(CSR* csr, int n) {
    printf("CSR representation:\n");
    printf("row_ptr: ");
    for (int i = 0; i <= n; ++i) printf("%d ", csr->row_ptr[i]);
    printf("\ncol_ind: ");
    for (int i = 0; i < csr->nnz; ++i) printf("%d ", csr->col_ind[i]);
    printf("\nval:     ");
    for (int i = 0; i < csr->nnz; ++i) printf("%d ", csr->val[i]);
    printf("\n");
}

// Temizlik
void free_graph(Node** adj, int n) {
    for (int i = 0; i < n; ++i) {
        Node* cur = adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(adj);
}

void free_csr(CSR* csr) {
    free(csr->row_ptr);
    free(csr->col_ind);
    free(csr->val);
    free(csr);
}

int main() {
    // Örnek graf: 5 düğüm, kenar listesi
    // edges: (0,1), (0,4), (1,2), (2,3)
    int n = 5;
    int edges[][2] = {
        {0,1},
        {0,4},
        {1,2},
        {2,3}
    };
    int m = sizeof(edges)/sizeof(edges[0]);

    Node** adj = create_graph(n);
    for (int i = 0; i < m; ++i) {
        int u = edges[i][0], v = edges[i][1];
        add_edge(adj, u, v);
        add_edge(adj, v, u); // undirected
    }

    CSR* csr = convert_to_csr(adj, n);
    print_csr(csr, n);

    // temizle
    free_graph(adj, n);
    free_csr(csr);

    return 0;
}
