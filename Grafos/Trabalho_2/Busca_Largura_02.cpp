//Devido a dificuldade, me basiei em um código que vi em uma video-aula no youtube, o nome do canal é Marcos Castro

#include <iostream>
#include <list>
#include <queue> 

using namespace std;

class Grafo{
	int V; 
	list<int> *adj; 

public:
	Grafo(int V); 
	void adicionarAresta(int v1, int v2); 

	
	void bfs(int v);
};

Grafo::Grafo(int V){
	this->V = V; 
	adj = new list<int>[V]; 
}

void Grafo::adicionarAresta(int v1, int v2){
	
	adj[v1-1].push_back(v2-1);
}

void Grafo::bfs(int v){
	queue<int> fila;
	bool visitados[V]; 

	for(int i = 0; i < V; i++)
		visitados[i] = false;

	cout <<  v + 1 << " ";
	visitados[v] = true; 

	while(true){
		list<int>::iterator it;
		for(it = adj[v].begin(); it != adj[v].end(); it++){
			if(!visitados[*it]){
				cout << *it +1 << " ";
				visitados[*it] = true; 
				fila.push(*it); 
			}
		}

		
		if(!fila.empty()){
			v = fila.front(); 
			fila.pop(); 
		}
		else
			break;
	}
}

int main()
{
	int V, arestas, v1, v2, peso;
    bool direcionado;

    cin >> V >> arestas >> peso >> direcionado;

    Grafo grafo(V);

    for(int i = 0; i < arestas; i++){
        cin >> v1 >> v2 >> peso;
        grafo.adicionarAresta(v1, v2);
    }

	grafo.bfs(0);

	return 0;
}