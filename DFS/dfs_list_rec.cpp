#include <iostream>
#include <algorithm>
#include <vector>

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
                if (find(listaAdjacencia[v1].begin(), listaAdjacencia[v1].end(), v2) != listaAdjacencia[v1].end()){
                    cout << "Aresta existente." << endl;
                    return;
                }
            }
            listaAdjacencia[v1].push_back(v2);
            listaAdjacencia[v2].push_back(v1);
        }

        void printarGrafo() {
            cout << endl;
            for (int i = 0; i < numVertices; i++) {
                char l1 = i + 'A';
                cout << "Vertice " << l1 << ": ";
                bool seta = false;
                for (int j : listaAdjacencia[i]) {
                    l1 = j + 'A';
                    if (!seta) {
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

        void ordernarGrafo() {
            for(int i = 0; i < numVertices; i++) {
                sort(listaAdjacencia[i].begin(), listaAdjacencia[i].end());
            }
        }

        void dfs(int v1) {
            visitados[v1] = true;
            char l1 = v1 + 'A';
            cout << l1 << ' ';
            for (int i : listaAdjacencia[v1]) {
                if (!visitados[i]) {
                    dfs(i);
                }
            }
        }
};

int main() {
    cout << "Digite a quantidade de vertices presentes no grafo:" << endl;
    int numVertices;
    cin >> numVertices;
    Grafo grafo(numVertices);
    
    cout << "Digite as arestas desse grafo (Ex A B). Digite 1 para sair:" << endl;
    char l1, l2;
    int v1, v2;
    while(1) {
        cin >> l1;
        if (l1 == '1'){
            break;
        }
        cin >> l2;
        v1 = l1 - 'A';
        v2 = l2 - 'A';
        if (v1 < 0 || v2 < 0 || v1 > numVertices - 1 || v2 > numVertices - 1 ) {
            cout << "Aresta invalida." << endl;
        } else {
            grafo.inserirAresta(v1, v2);
        }
    }

    grafo.ordernarGrafo();

    cout << endl << "Printando grafo:" << endl;
    grafo.printarGrafo();

    cout << "Digite qual vertice quer iniciar a busca em profundidade:" << endl;
    cin >> l1;
    v1 = l1 - 'A';
    if (v1 < 0 || v1 > numVertices - 1) {
        cout << "Vertice invalido" << endl;
    } else {
        cout << "Vertices visitados: ";
        grafo.dfs(v1);
    }
}