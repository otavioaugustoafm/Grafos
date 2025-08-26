#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Grafo {
    private:
        int numVertices;
        vector<vector<int>> listaAdjacencia;
        vector<bool> visitados;
        vector<int> distancia;
        vector<int> antecessor;
    
    public:
        Grafo(int numVertices) {
            this->numVertices = numVertices;
            listaAdjacencia.resize(numVertices);
            visitados.resize(numVertices);
            distancia.resize(numVertices);
            antecessor.resize(numVertices);
        }    

        int getDistancia(int destino) {
            return distancia[destino];
        }

        int printarCaminho(int inicio, int destino) {
            stack<int> pilha;
            while(1) {
                if (destino == inicio) {
                    break;
                }
                pilha.push(destino);
                destino = antecessor[destino];
            }
            bool seta = false;
            pilha.push(inicio);
            while(!pilha.empty()) {
                char l1 = pilha.top() + 'A';
                pilha.pop();
                if(seta != false) {
                    cout << " -> " << l1;
                } else {
                    cout << l1;
                }
                seta = true;
            }
        }

        void inserirAresta(int v1, int v2) {
            for(int i = 0; i < numVertices; i++) {
                if (find(listaAdjacencia[v1].begin(), listaAdjacencia[v1].end(), v2) != listaAdjacencia[v1].end()) {
                    cout << "Aresta repetida." << endl;
                    return;
                }
            }
            listaAdjacencia[v1].push_back(v2);
            listaAdjacencia[v2].push_back(v1);
        }

        void ordernarGrafo() {
            for(int i = 0; i < numVertices; i++) {
                sort(listaAdjacencia[i].begin(), listaAdjacencia[i].end());
            }
        }

        void printarGrafo() {
            cout << endl;
            for(int i = 0; i < numVertices; i++) {
                char l1 = i + 'A';
                cout << "Vertice " << l1 << ": ";
                bool seta = false;
                for (int j : listaAdjacencia[i]) {
                    l1 = j + 'A';
                    if (seta == false) {
                        cout << l1;
                    } else {
                        cout << " -> " << l1;
                    }
                    seta = true;
                }
                cout << endl;
            }
            cout << endl;
        }

        int bfs(int v1, int v2) {
            fill(visitados.begin(), visitados.end(), false);
            fill(distancia.begin(), distancia.end(), -1);
            fill(antecessor.begin(), antecessor.end(), -1);


            queue<int> fila;
            visitados[v1] = true;
            fila.push(v1);
            distancia[v1] = 0;
            
            while(1) {
                if (fila.empty()) {
                    break;
                }
                int removido = fila.front();
                fila.pop();
                for(int i : listaAdjacencia[removido]) {
                    if (visitados[i] != true) {
                        fila.push(i);
                        distancia[i] = distancia[removido] + 1;
                        antecessor[i] = removido;
                        visitados[i] = true;
                    }
                }
            }

            return distancia[v2];
        }
};

int main() {
    cout << "Digite a quantidade de vertices do grafo:" << endl;
    int numVertices;
    cin >> numVertices; 
    Grafo grafo(numVertices);


    cout << "Digite as arestas do grafo (Ex: A B). Digite 1 para sair:" << endl;
    int v1, v2;
    char l1, l2;
    while(1) {
        cin >> l1;
        if (l1 == '1') {
            break;
        }
        cin >> l2;
        v1 = l1 - 'A';
        v2 = l2 - 'A';
        grafo.inserirAresta(v1, v2);
    }

    grafo.ordernarGrafo();

    grafo.printarGrafo();

    cout << "Digite qual vertice quer iniciar a busca do menor caminho:" << endl;
    cin >> l1;
    v1 = l1 - 'A';
    cout << "Digite qual vertice quer terminar a busca do menor caminho:" << endl;
    cin >> l2;
    v2 = l2 - 'A';

    int resultado = grafo.bfs(v1, v2);
    if (resultado == -1) {
        cout << endl << "Sem caminhos para esse vertice." << endl;
    } else {
        int distancia = grafo.getDistancia(v2);
        cout << endl << "Distancia: " << distancia << endl;
    }
    grafo.printarCaminho(v1, v2);
}
