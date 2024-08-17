#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>

typedef struct node_t{
    int counter;
} node;

int get_random_num(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 99);

    return distr(gen);
}

void grafo_orientado(std::vector<std::vector<int>>& matriz_adj, int prob){
    for(int i = 0; i < matriz_adj.size(); i++){
        for(int j = 0; j < matriz_adj.size(); j++){
            if (get_random_num() < prob && j != i){
                matriz_adj[i][j] = 1;
            }
        }
    }
}

void grafo_nao_orientado(std::vector<std::vector<int>>& matriz_adj, int prob){
    for (int i = 0; i < matriz_adj.size(); i++){
        for (int j = i + 1; j < matriz_adj.size(); j++){
            if (get_random_num() < prob){
                matriz_adj[i][j] = 1;
                matriz_adj[j][i] = 1;
            }
        }
    }
}

int main(){
    int quantidade_nos, orientado, prob;

    printf("Digite a quantidade de nós: ");
    scanf("%d", &quantidade_nos);

    printf("Digite a probabilidade (valor entre 0 e 100): ");
    scanf("%d", &prob);

    printf("O grafo deve ser orientado? (1 - orientado / 0 - nao orientado): ");
    scanf("%d", &orientado);

    std::vector<std::vector<int>> matriz_adj(quantidade_nos, std::vector<int>(quantidade_nos));

    if(orientado)
        grafo_orientado(matriz_adj, prob);
    else
        grafo_nao_orientado(matriz_adj, prob);

    FILE *f;
    f = fopen("output.txt", "w");

    for(auto row = matriz_adj.begin(); row != matriz_adj.end(); ++row){
        for(auto item = row->begin(); item != row->end(); ++item){
            fprintf(f, "%d ", *(item.base()));
        }
        fprintf(f, "\n");
    }

    fclose(f);

    return 0;
}