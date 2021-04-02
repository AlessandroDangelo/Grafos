#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct aresta{
    int v1;
    int v2;
    int peso;
};

class Grafo
{
	int V; 
	list<int> *adj; 

public:
	Grafo(int V); 
	void adicionarAresta(int v1, int v2, bool direcionado); 
    void imprime(int vertices, int arestas, bool direcionado, vector<aresta> pesos);
};


Grafo::Grafo(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Grafo::adicionarAresta(int v1, int v2, bool direcionado)
{
    if (direcionado == 0){
	    adj[v1-1].push_back(v2);
        adj[v2-1].push_back(v1);
    }
    if (direcionado == 1){
        adj[v1-1].push_back(v2);
    }
}

void Grafo :: imprime(int vertices, int arestas, bool direcionado, vector<aresta> pesos){
    if(direcionado == 0){
        cout << vertices << " " << arestas << " " << "NAO DIRECIONADO" << endl;
    }
    if(direcionado == 1){
        cout << vertices << " " << arestas << " " << "DIRECIONADO" << endl;
    }

    int j = 0;

    for(int i = 0; i < vertices; i++) {
        for (list<int>::iterator it = adj[i].begin(); it!= adj[i].end(); it++){
            cout <<  i+1 << " " << *it << " ";
            for(int a = 0; a < arestas; a++){
                if(direcionado == 0){
                    if((pesos[a].v1 == i+1 && pesos[a].v2 == *it) || (pesos[a].v2 == i+1 && pesos[a].v1 == *it)){
                        cout << pesos[a].peso << endl;
                    }
                }
                if(direcionado == 1 && pesos[a].v1 == i+1 && pesos[a].v2 == *it){
                    cout << pesos[a].peso << endl;
                }
            }
            j++;
        }
    }
}


int main(){
    int vertices, arestas, saida, chegada, peso;
    bool direcionado;
    vector <aresta> pesos;
    aresta x;

    cin >> vertices >> arestas >> direcionado;

	
	Grafo grafo(vertices);

	
    for(int i = 0; i < arestas; i++){
        cin >> saida >> chegada >> peso;
	    grafo.adicionarAresta(saida, chegada, direcionado);
        x.v1 = saida;
        x.v2 = chegada;
        x.peso = peso;
        pesos.push_back(x); 
    }

    grafo.imprime(vertices, arestas, direcionado, pesos);

	return 0;
}