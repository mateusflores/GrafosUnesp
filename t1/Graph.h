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
    std::unordered_map<int, Node*> nodes;  // Store nodes by their IDs
    std::vector<Edge*> edges;              // Store all edges in the graph
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::vector<int>> distMatrix;

public:
    // Utilize este construtor para inicializar um grafo vazio
    Graph();
    // Este construtor pode ser utilizado para gerar um grafo através de um arquivo dado.
    Graph(std::ifstream &f);
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

    // 
    void erdosRenyi(double prob, int qtNodes);
    void barabasiAlbert(int qtNodes);

    int graphDegreeSum();
};

#endif  // GRAPH_H