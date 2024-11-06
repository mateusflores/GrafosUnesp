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
    std::vector<std::vector<int>> adj;          // Lista de adjacencias

public:
    // Utilize este construtor para inicializar um grafo vazio
    Graph();
    // Este construtor pode ser utilizado para gerar um grafo através de um arquivo dado.
    Graph(std::ifstream &f, int qtNodes);
    // Destrutor
    ~Graph();

    /* NODE RELATED */

    // Adiciona um nó ao grafo
    Node* addNode(int id);

    // Remove um nó do grafo
    void removeNode(int id);

    // Retorna o nó desejado
    Node* getNode(int id) const;

    // Retorna true caso o nó exista
    bool nodeExists(int id) const;

    /* EDGE RELATED */

    // Adiciona uma aresta ao grafo
    Edge* addEdge(int sourceId, int destinationId, int weight = 1.0);

    // Remove uma aresta do grafo
    void removeEdge(int sourceId, int destinationId);

    // Retorna a lista de arestas do grafo
    std::vector<Edge*> getEdges() const;

    // Retorna uma aresta específica, definida pelos seus ids source e destination
    Edge* getEdge(int sourceId, int destinationId) const;

    // Retorna true caso a aresta exista
    bool edgeExists(int sourceId, int destinationId) const;

    /* UTILS */

    // Busca em profundidade
    void depthFirstSearch(int v, std::vector<bool> &visited);

    // Verifica se o grafo é conexo (se n for conexo n é euleriano)
    bool verificaGrafoConexo();

    // Verifica se todos os nós possuem grau par
    bool hasEvenDegree();

    // Printa o grafo baseado na lista de adj
    void printGraph();

    // Faz a eulerizacao do grafo
    void eulerize();

    // Algoritmo de hierholzer para encontrar circuitos eulerianos
    std::vector<int> hierholzer();
};

#endif  // GRAPH_H