#include <stdio.h>

#define MAX_NODES 100

typedef struct {
    int parent[MAX_NODES];
    int rank[MAX_NODES];
} DisjointSet;

// Initialize disjoint set
void makeSet(DisjointSet *ds, int n) {
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;  // Each node is its own parent
        ds->rank[i] = 0;     // Initial rank is 0
    }
}

// Find function with path compression
int find(DisjointSet *ds, int x) {
    if (ds->parent[x] != x) {
        ds->parent[x] = find(ds, ds->parent[x]); // Path compression
    }
    return ds->parent[x];
}

// Union function with rank optimization
void unionSets(DisjointSet *ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);

    if (rootX != rootY) {
        if (ds->rank[rootX] > ds->rank[rootY]) {
            ds->parent[rootY] = rootX;
        } else if (ds->rank[rootX] < ds->rank[rootY]) {
            ds->parent[rootX] = rootY;
        } else {
            ds->parent[rootY] = rootX;
            ds->rank[rootX]++;
        }
    }
}

// Print the disjoint set structure
void printSets(DisjointSet *ds, int n) {
    printf("Element: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", i);
    }
    printf("\nParent : ");
    for (int i = 0; i < n; i++) {
        printf("%d ", ds->parent[i]);
    }
    printf("\n");
}

// Main function to demonstrate union-find operations
int main() {
    int n = 7;
    DisjointSet ds;
    
    makeSet(&ds, n);

    unionSets(&ds, 0, 1);
    unionSets(&ds, 1, 2);
    unionSets(&ds, 3, 4);
    unionSets(&ds, 4, 5);
    unionSets(&ds, 5, 6);
    unionSets(&ds, 2, 6);  // Connecting two sets


    
    printSets(&ds, n);
    printf("Find(6): %d\n", find(&ds, 6));
    printf("Find(3): %d\n", find(&ds, 3));
    printSets(&ds, n);

    return 0;
}
