#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Grafo {
    private:
        int numVertices;
        vector<vector<int>> listaAdjacencia;
        vector<bool> visitados;
    
    public:
        Grafo(int numVertices) {
            this->numVertices = numVertices;
            listaAdjacencia.resize(numVertices);
            visitados.resize(numVertices);
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

        void bfs(int v1) {
            queue<int> fila;
            visitados[v1] = true;
            fila.push(v1);
            
            while(1) {
                if (fila.empty()) {
                    break;
                }
                int removido = fila.front();
                fila.pop();
                char l1 = removido + 'A';
                cout << l1 << " ";
                for(int i : listaAdjacencia[removido]) {
                    if (visitados[i] != true) {
                        fila.push(i);
                        visitados[i] = true;
                    }
                }
            }
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

    cout << "Digite qual vertice quer iniciar a busca em largura:" << endl;
    cin >> l1;
    v1 = l1 - 'A';

    grafo.bfs(v1);
}
