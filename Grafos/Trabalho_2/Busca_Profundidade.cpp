#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Grafo{
    int eh_ponderado;
    int num_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};

Grafo *cria_Grafo(int num_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
void buscaProfundidade(Grafo* gr, int ini, int* visitado, int cont);
void buscaProfundidade_Grafo(Grafo* gr, int ini, int* visitado);

int main(){

    Grafo *grafo;
    int num_vertices, num_arestas, origemBusca, peso;
    int grau_max, vertice_saida, vertice_chegada;
    bool direcionado, ponderado;

    cin >> num_vertices >> num_arestas >> direcionado >> origemBusca;

    cin >> grau_max >> ponderado;

    int * visitados = new int[num_vertices];

    grafo = cria_Grafo(num_vertices, grau_max, ponderado);

    for(int i = 0; i < num_arestas; i++){
        cin >> vertice_saida >> vertice_chegada >> peso;
        insereAresta(grafo, vertice_saida, vertice_chegada, direcionado, peso);
    }

    buscaProfundidade_Grafo(grafo, origemBusca, visitados);

    for(int i = 0; i < num_vertices; i++){
        if(i == num_vertices-1){
            cout << visitados[i]+1 << " ";
        }else{
            cout << visitados[i]+1 << " ";
        }
    }

    

    return 0;
}

Grafo *cria_Grafo(int num_vertices, int grau_max, int eh_ponderado){
    Grafo *gr = new Grafo;
    if(gr != NULL){
        gr->num_vertices = num_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = eh_ponderado;
        gr->grau = new int[num_vertices];
        for(int i = 0; i < num_vertices; i++){
            gr->grau[i] = 0;
        }
        gr->arestas = new int*[num_vertices];
        for(int i = 0; i < num_vertices; i++){
            gr->arestas[i] = new int[grau_max];
            if(gr->eh_ponderado){
                gr->pesos = new float*[num_vertices];
                for(int j = 0; j < num_vertices; j++){
                    gr->pesos[j] = new float[grau_max];
                }
            }
        }
    }
    return gr;
}

void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        for(int i = 0; i < gr->num_vertices; i++){
            delete(gr->arestas[i]);
        }
        delete(gr->arestas);

        if (gr->eh_ponderado){
            for(int i = 0; i < gr->num_vertices; i++){
                delete(gr->pesos[i]);
            }
        delete(gr->pesos);
        }
        delete(gr->grau);
        delete(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL){
        return 0;
    }
    if(orig < 0 || orig >= gr->num_vertices){
        return 0;
    }
    if(dest < 0 || dest >= gr->num_vertices){
        return 0;
    }

    gr->arestas[orig][gr->grau[orig]] = dest;

    if(gr->eh_ponderado){
        gr->pesos[orig][gr->grau[orig]] = peso;
    }

    gr->grau[orig]++;

    if(eh_digrafo == 0){
        insereAresta(gr, dest, orig, 1, peso);
    }

    return 1;
}

void buscaProfundidade(Grafo* gr, int ini, int* visitado, int cont){
    visitado[ini] = cont;
    for(int i = 0; i < gr->grau[ini]; i++){
        if(!visitado[gr->arestas[ini][i]]){
            buscaProfundidade(gr, gr->arestas[ini][i], visitado, cont+1);
        }
    }
}
void buscaProfundidade_Grafo(Grafo* gr, int ini, int* visitado){
    int cont = 1;
    for(int i = 0; i < gr->num_vertices; i++){
        visitado[i] = 0;
    }
    buscaProfundidade(gr, ini, visitado, cont);
}
