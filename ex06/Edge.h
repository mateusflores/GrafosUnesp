/*
    A implementação do código da aresta leva em consideração
    arestas direcionadas e com peso.
    Contudo, para o trabalho 1 da disciplina, vamos considerar:
    - Edge(u, v) == Edge(v, u) - ou seja, grafo ñ direcionado
    - Todas as arestas possuem peso igual a 1
*/

#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

// Forward declaration - deste modo a classe Edge é capaz
// de fazer referência à classe Node
class Node;

class Edge {
private:
    Node* source;
    Node* destination;
    // a implementação permite definirmos um peso arbitrário, 
    // mas para o trabalho definimos o peso padrão = 1 unidade
    int weight;

public:
    // Construtor da classe Edge
    Edge(Node* source, Node* destination, int weight = 1);

    // Retorna o nó source
    Node* getSource() const;

     // Retorna o nó destination
    Node* getDestination() const;

    // Retorna o peso da aresta
    int getWeight() const;          

    // Define o peso da aresta
    void setWeight(int newWeight);

    /*
        O C++ permite fazermos o overload dos operadores definindo
        o comportamento esperado das comparações.

        Isto é interessante para definirmos Edge(u, v) == Edge(v, u).

        Além disso, como a classe Node possui uma estrutura de dados
        "Set<Edge>", temos que obrigatoriamente implementar a lógica
        de comparação na classe Edge, visto que o container "Set"
        utiliza esta lógica. Deve-se notar que esta obrigação é devido
        ao fato de Edge ser uma classe custom - se fosse int ou double,
        não seria necessário.
    */
    bool operator==(const Edge& other) const;
    bool operator<(const Edge& other) const;
};

#endif  // EDGE_H
