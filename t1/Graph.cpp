#include "Graph.h"
#include <algorithm>

Graph::Graph() {}

Graph::Graph(std::ifstream &f) {
    while(!f.eof()){
        int i, j, w;
        f >> i;
        f >> j;
        f >> w;
        if(!nodeExists(i)){
            addNode(i);
        }
        if(!nodeExists(j)){
            addNode(j);
        }
        addEdge(i, j, w);
    }
}

Graph::~Graph() {
    for (auto& pair : nodes) {
        // deleta todos os items do map
        delete pair.second;
    }
    for (Edge* edge : edges) {
        // deleta todas os edges
        delete edge;
    }
}

Node* Graph::addNode(int id) {
    if (nodeExists(id)) {
        // se o node ja existe, retorna nullptr
        return nullptr;
    }
    Node* node = new Node(id);
    nodes[id] = node;
    return node;
}

// remove o node e edges relacionadas
void Graph::removeNode(int id) {
    if (!nodeExists(id)) {
        return;
    }

    Node* node = nodes[id];

    // Remove all edges connected to this node
    for (Edge* edge : node->getEdges()) {
        removeEdge(edge->getSource()->getId(), edge->getDestination()->getId());
    }

    // Remove the node from the graph
    delete node;
    nodes.erase(id);
}

Node* Graph::getNode(int id) const {
    if (nodeExists(id)) {
        return nodes.at(id);
    }
    return nullptr;
}

// Edge management
Edge* Graph::addEdge(int sourceId, int destinationId, int weight) {
    if (!nodeExists(sourceId) || !nodeExists(destinationId)) {
        return nullptr;  // Source or destination node does not exist
    }
    if (edgeExists(sourceId, destinationId)) {
        return nullptr;  // Edge already exists
    }

    Node* source = nodes[sourceId];
    Node* destination = nodes[destinationId];

    Edge* edge = new Edge(source, destination, weight);
    edges.push_back(edge);

    // Add the edge to the connected nodes
    source->addEdge(edge);
    destination->addEdge(edge);

    return edge;
}

void Graph::removeEdge(int sourceId, int destinationId) {
    if (!edgeExists(sourceId, destinationId)) {
        return;
    }

    // Find the edge and remove it
    edges.erase(std::remove_if(edges.begin(), edges.end(),
        [sourceId, destinationId](Edge* edge) {
            return edge->getSource()->getId() == sourceId &&
                   edge->getDestination()->getId() == destinationId;
        }), edges.end());
}

// verifica se o vertice existe dentro do grafo
bool Graph::nodeExists(int id) const {
    return nodes.find(id) != nodes.end();
}

// verifica se a aresta existe dentro do grafo
bool Graph::edgeExists(int sourceId, int destinationId) const {
    for (Edge* edge : edges) {
        if (edge->getSource()->getId() == sourceId && edge->getDestination()->getId() == destinationId) {
            return true;
        }
    }
    return false;
}

std::vector<Edge*> Graph::getEdges() const {
    return edges;
}

Edge* Graph::getEdge(int sourceId, int destinationId) const {
    for (Edge* edge : edges) {
        if (edge->getSource()->getId() == sourceId && edge->getDestination()->getId() == destinationId) {
            return edge;
        }
    }
    return nullptr;  // Return nullptr if no such edge is found
}

void Graph::printAdjMatrix(){
    // cria quadrada matriz 2d preenchida com zeros
    std::vector<std::vector<int>> adjMatrix(nodes.size(), std::vector<int>(nodes.size(), 0));
    Edge *temp = nullptr;

    for (int i = 0; i < nodes.size(); i++){
        for (int j = i + 1; j < nodes.size(); j++){
            temp = getEdge(i, j);
            adjMatrix[i][j] = temp == nullptr ? 0 : temp->getWeight();
            adjMatrix[j][i] = adjMatrix[i][j];
        }
    }

    for (int i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes.size(); j++){
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}