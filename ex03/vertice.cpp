
#include "vertice.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <queue>

/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------
    Funções de vertices
--------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

vertice::vertice(){}
vertice::vertice(int id){
    this->id = id;
}

bool vertice::ehVizinho(vertice *v){
    for (int i=0; i<this->viz.size(); i++){
        if (v==this->viz.at(i)){
            return true;
        }
    }
    return false;
}

/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------
    Funções de grafos
--------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

grafo::grafo(){
    this->N = 0;
    this->V = nullptr;
}

grafo::grafo(int N, ifstream& f){
    this->N = N;
    this->V = new vertice[N];
    while(!f.eof()){
        int i, j;
        f >> i; f >> j;
        this->V[i].id = i;
        this->V[i].viz.push_back(&this->V[j]);
        this->V[j].id = j;
        this->V[j].viz.push_back(&this->V[i]);
    }
}

grafo::~grafo(){
    delete[] this->V;
}

void grafo::imprime(){
    for (int i=0; i<this->N; i++){
        cout << i << " ";
        for (int j=0; j<this->V[i].viz.size(); j++){
            cout << this->V[i].viz[j]->id << " ";
        }
        cout << endl;
    }
}

/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------
    Outras
--------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

bool estaEm(vector<int>& v, int k){
    for (int i=0; i<v.size(); i++){
        if (v[i]==k)
            return true;
    }
    return false;
}

void bp_visit(grafo& G, int raiz, int pai, vector<int>& visitd){
    for (int j=0; j < G[raiz].viz.size(); j++){
        if (G[raiz].viz[j]->id != pai){
            bp_visit(G,G[raiz].viz[j]->id,raiz,visitd);
        }
    }
    visitd.insert(visitd.begin(),raiz);
}

vector<int> bp_ordem(grafo& G){
    vector<int> visitd;
    for (int i=0; i<G.N; i++){
        if (!estaEm(visitd,i)){
            bp_visit(G,i,-1,visitd);
        }
    }
    return visitd;
}

void imprime(vector<int>& visitd){
    for (int i=0; i<visitd.size(); i++){
        cout << visitd[i] << endl;
    }
}

vector<int> busca_em_largura(grafo& G, int raiz, vector<int>& visitd){
    // fila para controlar a busca do algoritmo
    queue<vertice> fila;
    // vetor output para demonstrar a ordem da busca em largura
    vector<int> output_visitados;
    // inicializamos a lista de visitados toda como false
    // visto que ainda não visitamos nenhum vertice
    for (int i = 0; i < G.N; i++){
        visitd[i] = false;
    }

    // marcamos o nó de início como true, ou seja, já visitado
    visitd[raiz] = true;
    // adicionamos à fila para começar a busca pelo nó de origem
    fila.push(G[raiz]);

    /*  
        Passo a passo do algoritmo:

        1. O laço remove um item da fila
        2. Adicionamos o item no vetor da ordem de busca
        3. Vamos iterar sobre todos os vizinhos do item
        4. Caso não tenha sido visitado adicionamos na fila para
        que possamos efetuar busca sobre ele
    */
    while(!fila.empty()){
        vertice v_buff = fila.front();
        fila.pop();
        output_visitados.push_back(v_buff.id);

        for(vertice *v : v_buff.viz){
            if(!visitd[v->id]){
                visitd[v->id] = true;
                fila.push(*v);
            }
        }
    }

    return output_visitados;
}

