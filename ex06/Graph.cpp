#include "Graph.h"
#include <algorithm>
#include <random>

double getRandomProb(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0.0, 1.0);

    return distr(gen);
}

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

void Graph::initializeAdjMatrix(int qtNodes){
    adjMatrix = std::vector<std::vector<int>>(qtNodes, std::vector<int>(qtNodes, 0));
}

void Graph::generateAdjMatrix(){    
    Edge *temp = nullptr;

    for (int i = 0; i < nodes.size(); i++){
        for (int j = i + 1; j < nodes.size(); j++){
            temp = getEdge(i, j);
            adjMatrix[i][j] = temp == nullptr ? 0 : temp->getWeight();
            adjMatrix[j][i] = adjMatrix[i][j];
        }
    }    
}

std::vector<std::vector<int>> Graph::getAdjMatrix() const {
    return adjMatrix;
}

void Graph::printAdjMatrix(){
    for (int i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes.size(); j++){
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::initializeDistMatrix(){
    distMatrix = std::vector<std::vector<int>>(nodes.size(), std::vector<int>(nodes.size(), 0));
    for (int i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes.size(); j++){
            distMatrix[i][j] = adjMatrix[i][j];
        }
    }
    for (int i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes.size(); j++){
            if(distMatrix[i][j] == 0){
                distMatrix[i][j] = 999999;
            }
            if (i == j){
                distMatrix[i][j] = 0;
            }                
        }
    }
}

void Graph::floydWarshall(){
    for(int k = 0; k < nodes.size(); k++){
        for(int i = 0; i < nodes.size(); i++){
            for(int j = 0; j < nodes.size(); j++){
                if (distMatrix[i][j] > distMatrix[i][k] + distMatrix[k][j]){
                    distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
                }
            }
        }
    }
}

void Graph::printDistMatrix(){
    for (int i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes.size(); j++){
            if(distMatrix[i][j] == 999999){
                std::cout << "INF." << "\t";
            }
            else{
                std::cout << distMatrix[i][j] << "\t";
            }            
        }
        std::cout << std::endl;
    }
}

int Graph::findLongestPath(){
    int longest = 0;
    for(int i = 0; i < nodes.size(); i++){
        for (int j = 0; j < nodes.size(); j++){
            if (distMatrix[i][j] > longest && distMatrix[i][j] != 999999){
                longest = distMatrix[i][j];
            }
        }
    }
    return longest;
}

double Graph::calculateMean(){
    int numberOfEdges = edges.size();
    int weightsSum = 0;
    for(int i = 0; i < nodes.size(); i++){
        for (int j = i + 1; j < nodes.size(); j++){
            if (distMatrix[i][j] != 999999){
                weightsSum += distMatrix[i][j];
            }
        }
    }
    return weightsSum / static_cast<double>(numberOfEdges);
}

void Graph::erdosRenyi(double prob, int qtNodes){
    Node* ni;
    Node* nj;
    Edge* tempEdge;
    for (int i = 0; i < qtNodes; i++){
        for (int j = i + 1; j < qtNodes; j++){
            if (getRandomProb() < prob){
                // Pega o endereço dos nodes
                ni = getNode(i);
                nj = getNode(j);

                // Adiciona uma aresta entre os nodes
                tempEdge = addEdge(i, j, 1);

                // Registra as arestas no set de cada node
                ni->addEdge(tempEdge);
                nj->addEdge(tempEdge);

                // Atualiza a matriz de adjacencias
                adjMatrix[i][j] = 1;
                adjMatrix[j][i] = 1;
            }
        }
    }
}

int Graph::graphDegreeSum(){
    int result = 0;
    for(auto map : nodes){
        result += map.second->getEdges().size();
    }
    return result;
}

/*
1. Inicializar um grafo de ER com 20 nós
2. Adiciona um nó por vez:
    - A cada vez que a gente for adicionar um nó, calcular um valor aleatório de probabilidade (pa).
    - E calcular pv.
    pv = (grau do nó v) / (soma dos graus de todos os nós do grafo)
    
    if (pa < pv) -> adicionar uma aresta ao nó v
    
    for (u : remainingNodes) remainingNodes -> 90 - 20 = 70
        createNode(u)
        for (v : graph)
            calcula prob aleatoria pa
            calcula pv
            if (pv < pa)
                aresta(u, v)
*/
void Graph::barabasiAlbert(int qtNodes){
    // ER -> 0 ... 19 (20 nodes)
    double prob;        // probabilidade (grau do nó / somatória dos graus de todos os nós)

    // pointers placeholders
    Edge* tempEdge;
    Node* temp1;
    Node* temp2;
    for(int i = 20; i < qtNodes; i++){        
        Node *newNode = addNode(i);     // novo nó sendo adicionado nesta iteração
        for(auto existingNode : nodes){
            // calcula PV (grau do nó / somatória dos graus de todos os nós)
            prob = existingNode.second->getEdges().size() / static_cast<double>(graphDegreeSum());
            /*
            // Descomentar para aumentar a probabilidade, aumentando a quantidade de arestas
            if (prob * 10.0 < 1.0){
                prob = prob * 10;
            }
            */
            std::cout << prob << std::endl;
            if(getRandomProb() < prob){
                // adiciona a aresta(u, v) ao grafo
                tempEdge = addEdge(i, existingNode.second->getId(), 1);

                temp1 = getNode(i);             // temp1 = u
                temp2 = existingNode.second;    // temp2 = v
                                                // mantem registro da vizinhanca
                temp1->addEdge(tempEdge);       // u.adicionaAresta(u, v)
                temp2->addEdge(tempEdge);       // v.adicionaAresta(u, v)

                // atualiza a matriz de adjacencias
                adjMatrix[i][existingNode.second->getId()] = 1;
                adjMatrix[existingNode.second->getId()][i] = 1;
                
                std::cout << i << " - " << existingNode.second->getId() << std::endl;
            }
        }
    }
}

bool Graph::isNeighborOfEveryItem(const std::vector<int>& L, int u) {
    for (int v : L) {
        if (adjMatrix[u][v] == 0) {
            return false;
        }
    }
    return true;
}

// Algoritmo CliqueMaximal
std::vector<int> Graph::cliqueMaximal(int v) {
    // Lista para armazenar a clique maximal
    std::vector<int> L;
    // Insere o vértice 'v' em 'L' - vertice inicial
    L.push_back(v);
    // Contador para verificar se ainda há vértices para adicionar
    int c = 1;
    
    while (c > 0) {
        // Restart contador
        c = 0;
        
        // Itera sobre todos os vértices do grafo
        for (int u = 0; u < adjMatrix.size(); u++) {
            // Se u ainda ñ está em L e é vizinho de todos os itens de L
            if (find(L.begin(), L.end(), u) == L.end() && isNeighborOfEveryItem(L, u)) {
                // Adiciona 'u' à lista de vértices da clique
                L.push_back(u); 
                c++; // Incrementa o contador
            }
        }
    }
    
    // Retorna a lista de vertices que compoem a clique maximal
    return L;
}