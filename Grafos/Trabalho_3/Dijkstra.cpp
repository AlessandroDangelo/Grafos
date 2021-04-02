#include <iostream>
#include <vector> 

using namespace std;

struct aresta{
    int origem;
    int destino;
    int peso;
};

struct vertice{
    vector <int> caminho;
    int peso;
    bool visitado;
    vector <aresta> arestas;
};

struct grafo{
    int num_vertices;
    vector <vertice> vertices;
};

void dijkstra(grafo*, int);

int main(){
    int quant_vertices, quant_arestas, ponto_partida, v1, v2, peso;
    bool direcionado;

    cin >> quant_vertices >> quant_arestas >> direcionado >> ponto_partida;

    grafo* x = new grafo;
    aresta y;
    vertice* z = new vertice;

    x->num_vertices = quant_vertices;

    //insere as arestas em um vertice auxiliar
    for(int i = 0; i < quant_arestas; i++){
        if(direcionado == 1){
            cin >> v1 >> v2 >> peso;
            y.origem = v1;
            y.destino = v2;
            y.peso = peso;
            z->arestas.push_back(y);
            //como o grafo eh direcionado temos que adicionar uma aresta que vai do destino para a origem tbm
            y.origem = v2;
            y.destino = v1;
            y.peso = peso;
            z->arestas.push_back(y);
        }else{
            cin >> v1 >> v2 >> peso;
            y.origem = v1;
            y.destino = v2;
            y.peso = peso;
            z->arestas.push_back(y);
        }
    }

    vertice nulo;
    nulo.visitado = 0;
    nulo.peso = 0;
    
    //insere as arestas pertencentes a cada vertice dentro da estrutura grafo criada e inicializa a variavel visitado como não visitado
    for(int i = 0; i < quant_vertices; i++){
        x->vertices.push_back(nulo);   
        for(int j = 0; j < z->arestas.size(); j++){
            if(z->arestas[j].origem == i + 1){
                x->vertices[i].arestas.push_back(z->arestas[j]);
            }
        }
    }

    int novoVizinho;

    //inicializando o caminho do ponto de origem para nao dar problema na verificacao 
    x->vertices[ponto_partida -1].caminho.push_back(ponto_partida -1);
    x->vertices[ponto_partida -1].visitado = 1;

    //Do ponto de origem, passa em todos os vertices vizinhos e atualiza caminho, visitado e peso.
    for(int i = 0; i < x->vertices[ponto_partida - 1].arestas.size(); i++){
        x->vertices[x->vertices[ponto_partida -1].arestas[i].destino - 1].peso = x->vertices[ponto_partida -1].peso + x->vertices[ponto_partida -1].arestas[i].peso;
        //ATUALIZAR  AQUI PARA RECEBER O MESMO CAMINHO QUE O VERTICE NA POSICAO i 
        x->vertices[x->vertices[ponto_partida -1].arestas[i].destino - 1].caminho.push_back(ponto_partida -1);
    }

    //Acha o o menor vizinho nao visitado
    for(int i = 0; i < x->vertices[ponto_partida -1].arestas.size(); i++){
        if(x->vertices[x->vertices[ponto_partida -1].arestas[i].destino - 1].visitado == 0){
            novoVizinho = x->vertices[ponto_partida -1].arestas[i].destino - 1;
            break;
        }
    }
    
    dijkstra(x, novoVizinho);        

    //Imprime
    for(int i = 0; i < quant_vertices; i++){
        if(i+1 != ponto_partida){
            cout << i+1 << " " << "(" << x->vertices[i].peso << ") : ";
            for(int j = 0; j < x->vertices[i].caminho.size(); j++){
                if(j == x->vertices[i].caminho.size() - 1){
                    cout << x->vertices[i].caminho[j] + 1 << " " << i + 1;
                }else{
                    cout << x->vertices[i].caminho[j] + 1 << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}

void dijkstra(grafo* x, int menorVizinhoNaoVisitado){
    int novoVizinho = menorVizinhoNaoVisitado;
    int verifica = 0;
    x->vertices[menorVizinhoNaoVisitado].visitado = 1;
    for(int j = 0; j < x->vertices[menorVizinhoNaoVisitado].arestas.size(); j++){
        //para a primeira iteracao, atualiza o caminho e o peso do destino da aresta 
        //para as demais realiza o preenchimento de peso e caminho para um vertice que nao eh ligado com o ponto de origem
        if(x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].caminho.size() == 0){
            x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].peso = x->vertices[menorVizinhoNaoVisitado].peso + x->vertices[menorVizinhoNaoVisitado].arestas[j].peso;
            //ATUALIZAR  AQUI PARA RECEBER O MESMO CAMINHO QUE O VERTICE NA POSICAO i 
            x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].caminho = x->vertices[menorVizinhoNaoVisitado].caminho;
            x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].caminho.push_back(menorVizinhoNaoVisitado);
        //para as demais iteracoes
        }else{
            //verifica se o peso do vertice + o peso do destino da aresta eh menor que o peso do vertice de destino
            if(x->vertices[menorVizinhoNaoVisitado].peso + x->vertices[menorVizinhoNaoVisitado].arestas[j].peso < x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].peso){
                 x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].peso = x->vertices[menorVizinhoNaoVisitado].peso + x->vertices[menorVizinhoNaoVisitado].arestas[j].peso;
                //ATUALIZAR  AQUI PARA RECEBER O MESMO CAMINHO QUE O VERTICE NA POSICAO i 
                x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].caminho = x->vertices[menorVizinhoNaoVisitado].caminho;
                x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[j].destino - 1].caminho.push_back(menorVizinhoNaoVisitado);
            }
        } 
    }

    for(int i = 0; i < x->vertices[menorVizinhoNaoVisitado].arestas.size(); i++){
        if(x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[i].destino - 1].visitado == 0){
            novoVizinho = x->vertices[menorVizinhoNaoVisitado].arestas[i].destino - 1;
            break;
        }
        if(x->vertices[x->vertices[menorVizinhoNaoVisitado].arestas[i].destino - 1].visitado == 1){
            verifica = verifica + 1;
        }
    }
    if(verifica == x->vertices[menorVizinhoNaoVisitado].arestas.size()){
        return;
    }else{
        dijkstra(x, novoVizinho);
    }
}