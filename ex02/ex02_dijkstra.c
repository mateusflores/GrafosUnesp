#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// itera sobre todos os nós e retorna o indice do nó com menor distância em relação a src
int getMinIndex(int dist[], int processedNodes[], int qtNodes) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < qtNodes; v++) {
        if (processedNodes[v] == 0 && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void dijkstra(int **graph, int src, int dist[], int qtNodes) {
    // lista de nós processados
    int processedNodes[qtNodes];

    for (int i = 0; i < qtNodes; i++) {
        dist[i] = INT_MAX;      // distancia maxima
        processedNodes[i] = 0;  // nenhum nó visitado
    }

    dist[src] = 0;

    for (int count = 0; count < qtNodes - 1; count++) {
        // retorna o indice do nó menos distante
        int u = getMinIndex(dist, processedNodes, qtNodes);
        // marca o nó como visitado
        processedNodes[u] = 1;

        // se o nó não foi processado, existe aresta e a distancia for menor, entao atualiza 
        for (int v = 0; v < qtNodes; v++){
            if (!processedNodes[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    int qtNodes;
    printf("Digite o número de nós: ");
    scanf("%d", &qtNodes);
    int **graph = (int **)malloc(qtNodes * sizeof(int *));

    for (int i = 0; i < qtNodes; i++){
        graph[i] = (int *)malloc(qtNodes * sizeof(int));
    }
        
    printf("Digite os pesos das arestas (use 0 para nenhuma conexão):\n");

    for (int i = 0; i < qtNodes; i++) {
        for (int j = 0; j < qtNodes; j++) {
            printf("Peso da aresta entre %d e %d: ", i, j);
            scanf("%d", &graph[i][j]);
        }
    }

    int src;
    printf("Digite o nó de início: ");
    scanf("%d", &src);

    int dist[qtNodes];
    dijkstra(graph, src, dist, qtNodes);
    printf("Vértice \t Distância da origem\n");

    for (int i = 0; i < qtNodes; i++){
        printf("%d \t\t %d\n", i, dist[i]);
    }

    for (int i = 0; i < qtNodes; i++){
        free(graph[i]);
    }
    
    free(graph);
    return 0;
}