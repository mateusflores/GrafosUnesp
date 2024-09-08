/*
EXERCICIO 04 - Grafos e Aplicações (Noturno - 2o.sem/2024)

Grupo 5:
    Guilherme Caetano
    Henrique Gomes de Oliveira Sanches
    Leonardo Henrique Cardoso
    Mateus Gomes Flôres
    Thiago Inouye Miyazaki
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <bits/stdc++.h> 

using namespace std;

// esta função será utilizada para atribuirmos
// um peso aleatório para a aresta
int get_random_int(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 99);

    return distr(gen);
}

class Graph { 
public:
    // 
    int* parent;
    int* rank;
    // vetor de vetores de arestas
    vector<vector<int>> edgelist; 
    int qt_nodes;

    Graph(int N, ifstream &f){ 
        this->qt_nodes = N;
        while(!f.eof()){
            int i, j;
            f >> i;
            f >> j;
            // define um peso aleatório
            this->addEdge(i, j, get_random_int());
        }
    }

    // inicializa parent e rank
    void initialize_dsu(int n){
        // guarda os pai dos nós
        parent = new int[n];
        // guarda a profundidade das árvores
        rank = new int[n]; 
  
        for (int i = 0; i < n; i++) {
            // no início - temos n conjuntos
            // e cada nó é líder de seu conjunto
            parent[i] = -1; 
            // profundidade = 1
            rank[i] = 1; 
        } 
    }

    // verifica se o nó pertence a um conjunto
    // e se pertence, retorna seu líder
    int find(int i){ 
        if (parent[i] == -1) 
            return i; 
  
        return parent[i] = find(parent[i]); 
    }

    // faz a união dos conjuntos (subarvores)
    void unite(int u, int v){ 
        int leader1 = find(u); 
        int leader2 = find(v); 
  
        if (leader1 != leader2) {
            /* 
            Otimizações de tamanho da árvore:
            - tenta manter profundidade mínima
            - adiciona a menor subárvore à
            raiz da maior subárvore
            - se for igual, adiciona a segunda
            à primeira e rank[primeira] += 1            
            */

            if (rank[leader1] < rank[leader2]) { 
                parent[leader1] = leader2; 
            } 
            else if (rank[leader1] > rank[leader2]) { 
                parent[leader2] = leader1; 
            } 
            else {
                parent[leader2] = leader1; 
                rank[leader1] += 1; 
            } 
        } 
    }  

    // adiciona aresta à lista de arestas
    void addEdge(int u, int v, int w){ 
        edgelist.push_back({ w, u, v }); 
    } 
  
    void kruskal(){ 
        // std::sort (first, last, comp);
        // compara e ordena a lista pelos pesos
        sort(edgelist.begin(), edgelist.end());
  
        // inicializa parent e rank do union-find
        this->initialize_dsu(qt_nodes);
        int total_cost = 0;

        cout << "\nArestas selecionadas (MST): " << endl;

        for (auto edge : edgelist) {
            int weight = edge[0];   // peso
            int u = edge[1];        // aresta 1
            int v = edge[2];        // aresta 2

            int leaderU = this->find(u);  // representante de U
            int leaderV = this->find(v);  // reoresentante de V
  
            if (leaderU != leaderV){
                this->unite(u, v);
                total_cost = total_cost + weight;
                cout << u << " <---> " << v << " // Peso: " << weight << endl;
            }
        }
        cout << "\nCusto Total da Árvore: " << total_cost << endl;
    }
};

int main(){
    ifstream f("exemplo.dat"); 
    Graph *graph = new Graph(7, f);

    for (auto edge : graph->edgelist){
        cout << "peso: " << edge[0] << " \tu: " << edge[1] << " \tv: " << edge[2] << endl;
    }

    graph->kruskal();
}