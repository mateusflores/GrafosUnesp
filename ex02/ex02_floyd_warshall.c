#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void floyd_warshall(int **graph, int qtNodes){
    for(int k = 0; k < qtNodes; k++){
        for(int i = 0; i < qtNodes; i++){
            for(int j = 0; j < qtNodes; j++){
                if (graph[i][j] > graph[i][k] + graph[k][j]){
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int main() {
    int qtNodes;
    printf("Digite o número de nós: ");
    scanf("%d", &qtNodes);
    int **graph = (int **)malloc(qtNodes * sizeof(int *));

    for (int i = 0; i < qtNodes; i++)
        graph[i] = (int *)malloc(qtNodes * sizeof(int));
        
    printf("Digite os pesos das arestas (use 0 para nenhuma conexão):\n");

    for (int i = 0; i < qtNodes; i++) {
        for (int j = 0; j < qtNodes; j++) {
            printf("Peso da aresta entre %d e %d: ", i, j);
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0){
                graph[i][j] = 999999;
            }
            if (i == j){
                graph[i][j] = 0;
            }                
        }
    }

    floyd_warshall(graph, qtNodes);
    
    printf("\n");

    for(int i = 0; i < qtNodes; i++){
        for(int j = 0; j < qtNodes; j++){
            if (graph[i][j] == 999999){
                printf("INF\t");
            }
            else{
                printf("%d\t", graph[i][j]);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < qtNodes; i++){
        free(graph[i]);
    }

    free(graph);
    return 0;
}