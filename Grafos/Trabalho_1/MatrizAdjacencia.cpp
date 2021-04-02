#include <iostream>

using namespace std;

void ImprimeMatriz (int**, int);

int** CriaMatrizDinamica (int);

void PreencheMatriz (int**, int**, int, bool);

void ImprimeMatriz (int**, int**, int, int, bool);

struct Grafo{
    int vertice_saida;
    int vertice_chegada;
    int peso;
    bool verificacao;

};


int main (){

    int vertices, arestas, peso;
    bool direcionado;

    cin >> vertices >> arestas >> direcionado;

    int** MatrizAdjacencias = CriaMatrizDinamica(vertices);

    int** MatrizPesos = CriaMatrizDinamica(vertices);

    PreencheMatriz(MatrizAdjacencias, MatrizPesos, arestas, direcionado);

    ImprimeMatriz(MatrizAdjacencias, MatrizPesos, vertices, arestas, direcionado);

    return 0;
}

void ImprimeMatriz (int** MatrizAdjacencias, int vertices){
    for (int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            cout << MatrizAdjacencias[i][j] << " ";
        }
        cout << endl;
    }
}

int** CriaMatrizDinamica (int tamanho){

    int** matriz = new int*[tamanho];

    for (int i = 0; i < tamanho; ++i){
        matriz[i] = new int[tamanho];
    }
    

    for (int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

void  PreencheMatriz (int** matriz, int** pesos, int arestas, bool direcionado){
    int saida, chegada, peso;

    if(direcionado == 0){
        for(int i = 0; i < arestas; i++){
            cin >> saida >> chegada >> peso;
            matriz[saida-1][chegada-1] = 1;
            matriz[chegada-1][saida-1] = 1;
            pesos[saida-1][chegada-1] = peso;
            pesos[chegada-1][saida-1] = peso;
        }
    }
    if (direcionado == 1){
       for(int i = 0; i < arestas; i++){
            cin >> saida >> chegada >> peso;
            matriz[saida-1][chegada-1] = 1;
            pesos[saida-1][chegada-1] = peso;
        } 
    }
}

void ImprimeMatriz (int** matriz, int** pesos, int vertices, int arestas, bool direcionado){
    if(direcionado == 0){
        cout << vertices << " " << arestas << " " << "NAO DIRECIONADO" << endl;
        for (int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(matriz[i][j] != 0){
                cout << i+1 << " " << j+1 <<  " " << pesos[i][j] << endl;
                }
            }
        }
    }
    if (direcionado == 1){
        cout << vertices << " " << arestas << "DIRECIONADO" << endl;
        for (int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(matriz[i][j] != 0){
                cout << i+1 << " " << j+1 << " " << pesos[i][j] << endl;
                }
            }
        }
    }
}