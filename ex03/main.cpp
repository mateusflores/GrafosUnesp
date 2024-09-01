#include "vertice.h"
#include <iostream>
using namespace std;

int main(){

    ifstream f("exemplo.dat");
    grafo G(7,f);
    G.imprime();

    vector<int> vistd(G.N);
    vistd = busca_em_largura(G, G.V[0].id, vistd);
    cout << endl;
    imprime(vistd);
    return 0;
}