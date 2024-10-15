#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

class Graph {
private:
    std::unordered_map<int, Node*> nodes;       // Mapeia ids a objetos Node
    std::vector<Edge*> edges;                   // Armazena todas as arestas
    std::vector<std::vector<int>> adjMatrix;    // Matriz de adjacencias
    std::vector<std::vector<int>> distMatrix;   // Matriz de distancias

public:
    // Utilize este construtor para inicializar um grafo vazio
    Graph();
    // Este construtor pode ser utilizado para gerar um grafo através de um arquivo dado.
    Graph(std::ifstream &f);
    // Destrutor
    ~Graph();

    // Adiciona um nó ao grafo
    Node* addNode(int id);

    // Remove um nó do grafo
    void removeNode(int id);

    // Retorna o nó desejado
    Node* getNode(int id) const;

    // Adiciona uma aresta ao grafo
    Edge* addEdge(int sourceId, int destinationId, int weight = 1.0);

    // Remove uma aresta do grafo
    void removeEdge(int sourceId, int destinationId);

    // Retorna a lista de arestas do grafo
    std::vector<Edge*> getEdges() const;

    // Retorna uma aresta específica, definida pelos seus ids source e destination
    Edge* getEdge(int sourceId, int destinationId) const;

    // Inicializa com valor 0 uma matriz quadrada de qtNodes x qtNodes 
    void initializeAdjMatrix(int qtNodes);

    // Gera a matriz de adjacências baseado na lista de arestas
    void generateAdjMatrix();

    // Retorna a matriz de adjacências
    std::vector<std::vector<int>> getAdjMatrix() const;

    // Printa a matriz de adjacência para stdout
    void printAdjMatrix();

    // Retorna true caso o nó exista
    bool nodeExists(int id) const;

    // Retorna true caso a aresta exista
    bool edgeExists(int sourceId, int destinationId) const;

    // Inicializa a matriz de distâncias utilizando como base a matriz de adjacências
    // trocando os zeros por 999999 (valor alto)
    void initializeDistMatrix();

    // Calcula a distância entre todos os nós do grafo
    void floydWarshall();

    // Printa a matriz de adjacência
    void printDistMatrix();

    // Lê a matriz de distâncias e encontra o caminho mais longo
    int findLongestPath();

    // Calcula a média de todas as distâncias da matriz de distâncias
    double calculateMean();

    /*
    Pega todos os nodes registrados no grafo, itera entre todos eles (i x j)
    verificando se deve ser construída uma aresta entre os nós [i][j]. 
    
    A probabilidade de haver uma aresta entre dois nós é dada
    pela variável prob, que será comparada com um gerador de doubles
    aleatórios com range entre 0.0 e 1.0.
    */
    void erdosRenyi(double prob, int qtNodes);

    /*
    int qtNodes : quantidade de nós total ao final da operação

    1. Inicializa um grafo de ER com 20 nós.
    2. Iterar por qtNodes - 20, onde:
        - A cada iteração adicionamos um novo nó ao grafo
        2.1 Iteramos sobre todos os nó existentes no grafo. E a cada iteração:
            - Geramos um valor de probabilidade ALEATÓRIO (PA)
            - Calculamos o PV = grau do nó / somatória de todos os graus
            - Se PA < PV criamos uma aresta entre o novo nó, e o nó da iteração (com peso 1)
    */
    void barabasiAlbert(int qtNodes);

    // Faz uma somatória de todos os graus de cada nó
    int graphDegreeSum();

    // Verifica se o nó u é vizinho de todos os elementos em L
    bool isNeighborOfEveryItem(const std::vector<int>& L, int u);

    // Gera uma lista que contém os vértices que fazem parte da
    // clique maximal
    std::vector<int> cliqueMaximal(int v);
};

#endif  // GRAPH_H