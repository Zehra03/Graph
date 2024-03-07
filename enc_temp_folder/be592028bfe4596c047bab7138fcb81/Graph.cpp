#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Grafik yapısı
typedef struct Graph {
    int V;          // Düğüm sayısı
    int** adj;      // Bitişiklik listelerini içeren bir diziye işaretçi
} Graph;

// V düğümlü bir graf oluşturmak için fonksiyon
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;

    // Her düğümün bitişiklik listesini başlangıçta boş olarak başlat
    graph->adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = NULL;
    }

    return graph;
}

// Yönsüz bir graf için kenar eklemek için fonksiyon
void addEdge(Graph* graph, int src, int dest) {
    // src'den dest'e bir kenar ekle
    graph->adj[src] = (int*)realloc(graph->adj[src], 2 * sizeof(int));
    graph->adj[src][0] = dest;

    // Grafik yönsüz olduğundan, dest'ten src'ye de bir kenar ekleyin
    graph->adj[dest] = (int*)realloc(graph->adj[dest], 2 * sizeof(int));
    graph->adj[dest][0] = src;
}

// BFS algoritması
void BFS(Graph* graph, int start) {
    // Ziyaret edilen düğümleri takip etmek için bir dizi oluştur
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
    }

    // BFS sırasını takip etmek için bir kuyruk oluştur
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    // Başlangıç düğümünü kuyruğa ekle ve ziyaret edildi olarak işaretle
    queue[rear++] = start;
    visited[start] = true;

    printf("BFS Traversal: ");
    // Kuyruk boş olana kadar devam et
    while (front < rear) {
        // Kuyruktan bir düğümü çıkar ve yazdır
        int current = queue[front++];
        printf("%d ", current);

        // Bu düğümün komşularını kontrol et
        for (int i = 0; i < 2; i++) {
            int neighbor = graph->adj[current][i];
            if (!visited[neighbor]) {
                // Ziyaret edilmemiş komşuları kuyruğa ekle ve ziyaret edildi olarak işaretle
                queue[rear++] = neighbor;
                visited[neighbor] = true;
            }
        }
    }

    // Belleği serbest bırak
    free(visited);
    free(queue);
}

// DFS algoritması (yardımcı fonksiyon)
void DFSUtil(Graph* graph, int current, bool* visited) {
    // Şu anki düğümü ziyaret et ve yazdır
    printf("%d ", current);
    visited[current] = true;

    // Şu anki düğümün komşularını kontrol et
    for (int i = 0; i < 2; i++) {
        int neighbor = graph->adj[current][i];
        if (!visited[neighbor]) {
            // Ziyaret edilmemiş komşuları DFS ile keşfet
            DFSUtil(graph, neighbor, visited);
        }
    }
}

// DFS algoritması
void DFS(Graph* graph, int start) {
    // Ziyaret edilen düğümleri takip etmek için bir dizi oluştur
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; i++) {
        visited[i] = false;
    }

    printf("DFS Traversal: ");
    // DFSUtil fonksiyonunu çağırarak DFS başlat
    DFSUtil(graph, start, visited);

    // Belleği serbest bırak
    free(visited);
}

int main() {
    int V = 6; // Düğüm sayısı
    Graph* graph = createGraph(V);

    // Grafik kenarlarını ekleyin
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 4);

    // Başlangıç düğümü 0 olan BFS ve DFS taraması yapın
    BFS(graph, 0);
    printf("\n");
    DFS(graph, 0);

    // Grafik belleğini serbest bırak
    for (int i = 0; i < V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);

    return 0;
}
