#include "Graph.h"
#include <algorithm>
#include <ctime>
#include <random>
#include <unordered_set>
#include <stack>

double getRandomProb(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0.0, 1.0);

    return distr(gen);
}

Graph::Graph() {}

Graph::Graph(std::ifstream &f, int qtNodes) : adj(qtNodes) {   
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
/*
void Graph::removeNode(int id) {
    if (!nodeExists(id)) {
        return;
    }

    Node* node = nodes[id];

    for (Edge* edge : node->getEdges()) {
        removeEdge(edge->getSource()->getId(), edge->getDestination()->getId());
    }

    // Remove o nó do grafo e destrói o objeto
    delete node;
    nodes.erase(id);
}
*/

Node* Graph::getNode(int id) const {
    if (nodeExists(id)) {
        return nodes.at(id);
    }
    return nullptr;
}

Edge* Graph::addEdge(int sourceId, int destinationId, int weight) {
    // Os dois nós devem existir para podermos prosseguir
    if (!nodeExists(sourceId) || !nodeExists(destinationId)) {
        return nullptr;
    }
    // Não deve adicionar a aresta caso já exista
    if (edgeExists(sourceId, destinationId)) {
        return nullptr;
    }

    // Pega os nós da lista de nós
    Node* source = nodes[sourceId];
    Node* destination = nodes[destinationId];

    // Cria a aresta e adiciona à lista de arestas
    Edge* edge = new Edge(source, destination, weight);
    edges.push_back(edge);

    // Adiciona a aresta aos nós relacionados para contabilizar a vizinhança
    source->addEdge(edge);
    destination->addEdge(edge);

    // adiciona cada um nó na vizinhança do outro
    source->addNeighbor(destination->getId());
    destination->addNeighbor(source->getId());

    // Adiciona tambem na lista de adjacencias
    adj[sourceId].push_back(destinationId);
    adj[destinationId].push_back(sourceId);

    return edge;
}

void Graph::removeEdge(int sourceId, int destinationId) {
    if (!edgeExists(sourceId, destinationId)) {
        return;
    }

    // encontra a aresta e a remove
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
    return nullptr;  // Retorna nullptr se nao encontrou nada
}

// busca em profundidade - recursiva
void Graph::depthFirstSearch(int v, std::vector<bool> &visited) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            depthFirstSearch(u, visited);
        }
    }
}

// verifica se o grafo é conexo
bool Graph::verificaGrafoConexo() {
    int qtNodes = nodes.size();

    // inicializa um vetor de tamanho qtNodes com todos valores == false
    std::vector<bool> visited(qtNodes, false);
    int start = -1;

    // encontrar um nó que tenha aresta
    for (int i = 0; i < qtNodes; i++) {
        // se a lista de adj para determinado nó n for vazia achamos um nó com aresta
        if (!adj[i].empty()) {
            start = i;
            break;
        }
    }

    // efetua busca em profundidade iniciando pelo nó encontado anteriormente
    depthFirstSearch(start, visited);

    // verifica se todos os vértices com arestas foram visitados
    for (int i = 0; i < qtNodes; i++) {
        // se tem um nó que n foi visitado e n tem aresta, o grafo n é conexo
        if (!visited[i] && !adj[i].empty()) {
            return false;
        }
    }
    return true;
}

bool Graph::hasEvenDegree(){
    int qtNodes = nodes.size();

    // Se para qualquer nó o grau for ímpar, então o grafo ñ é euleriano
    for (int i = 0; i < qtNodes; i++) {
        if (adj[i].size() % 2 != 0) {
            return false;
        }
    }
    return true;
}

void Graph::printGraph(){
    std::cout << "Grafo (lista de adjacência):" << std::endl;
    for (int u = 0; u < nodes.size(); u++) {
        std::cout << u << ": ";
        for (int v : adj[u]) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}


void Graph::eulerize() {
    std::vector<int> nodesImpares;
    
    // Pega todos os nós de grau ímpar
    for (int i = 0; i < nodes.size(); i++) {
        // pega apena qts impares
        if (adj[i].size() % 2 != 0) {
            nodesImpares.push_back(i);
        }
    }

    // Adiciona arestas para tornar os graus pares (pareia vértices de grau ímpar)
    for (size_t i = 0; i < nodesImpares.size(); i += 2) {
        int u = nodesImpares[i];
        int v = nodesImpares[i + 1];
        addEdge(u, v, 1);
    }

    printGraph();
}

std::vector<int> Graph::hierholzer(){
    // armazena a ordem do caminho do circuito euleriano
    std::vector<int> circuit;

    // verifica se o grafo é euleriano, uma das condições para a execução do algo. de hierholzer
    if (!verificaGrafoConexo() || !hasEvenDegree()) {
        std::cout << "Grafo não é euleriano. Tentando eulerizar..." << std::endl;
        eulerize();

        // existem situacoes em que a eulerizacao não é possível (não é possível tornar todos os graus pares)
        if (!verificaGrafoConexo() || !hasEvenDegree()) {
            std::cout << "Eulerização falhou. Grafo ainda não é euleriano." << std::endl;
            return circuit;
        }
    }
    
    /* se a exec chegou até aqui, entao o grafo é euleriano */

    // faz uma cópia da lista de adj usando map para acesso direto
    // assim podemos modificar sem alterar o grafo original
    std::unordered_map<int, std::unordered_set<int>> tempAdj;
    for (int u = 0; u < nodes.size(); u++) {
        for (int v : adj[u]) {
            tempAdj[u].insert(v);
        }
    }

    // inicia a busca pelo nó zero e utiliza um stack, similar ao dfs (busca em profundidade)
    std::stack<int> currentPath;
    currentPath.push(0);
    int currentNode = 0;

    // como o grafo é euleriano, podemos sair de qualquer nó e voltar a ele e obteremos o
    // circuito euleriano, entao basta percorrermos o grafo de modo a similar à busca em profundidade
    // evitando percorrer arestas já investigadas, e colocando na pilha os nós percorridos
    // (note que a ordem de percurso é invertida)
    while (!currentPath.empty()) {
        // vamos fazer um percurso 
        if (!tempAdj[currentNode].empty()) {
            currentPath.push(currentNode);
            int nextVertex = *tempAdj[currentNode].begin();
            tempAdj[currentNode].erase(nextVertex);
            tempAdj[nextVertex].erase(currentNode);
            currentNode = nextVertex;
        } else {
            circuit.push_back(currentNode);
            currentNode = currentPath.top();
            currentPath.pop();
        }
    }

    return circuit;
}
