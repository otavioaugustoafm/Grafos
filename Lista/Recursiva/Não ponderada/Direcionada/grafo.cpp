#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Grafo {
    public:
        int numVertices;
        vector<vector<int>> listaAdjacencia;
        vector<bool> visitados;

        Grafo(int numVertices) {
            this->numVertices = numVertices;
            listaAdjacencia.resize(numVertices);
            visitados.resize(numVertices);
        }

        void inserirArestas() {
            char l1 = ' ', l2 = ' ';
            int v1 = 0, v2 = 0;
            cout << "Digite as arestas que deseja inserir (Ex: A B). Digite 1 para terminar:" << endl;
            while(1) {
                cin >> l1;
                if (l1 == '1') {
                    break;
                }
                cin >> l2;
                v1 = l1 - 'A'; v2 = l2 - 'A';
                auto busca = find(listaAdjacencia[v1].begin(), listaAdjacencia[v1].end(), v2);
                if (busca != listaAdjacencia[v1].end()) {
                    cout << "Aresta existente." << endl;
                    return;
                }
                listaAdjacencia[v1].push_back(v2);
            }
            cout << "Arestas inseridas." << endl;
        }

        void printarGrafo() {
            for (int i = 0; i < numVertices; i++) {
                sort(listaAdjacencia[i].begin(), listaAdjacencia[i].end());
            }
            for (int i = 0; i < numVertices; i++) {
                char l1 = i + 'A';
                cout << "Vertice " << l1 << ": ";
                bool seta = true;
                for (int j : listaAdjacencia[i]) {
                    if (!seta == true) {
                        cout << " ->";
                    }
                    l1 = j + 'A';
                    cout << " " << l1;
                    seta = false;
                }
                cout << endl;
            }
        }

        void dfs(int v1) {
            visitados[v1] = true;
            char l1 = v1 + 'A';
            cout << l1 << " ";
            
            for (int i : listaAdjacencia[v1]) {
                if(!visitados[i]) {
                    dfs(i);
                }
            }
        }
};

int main() {
    cout << "Digite a quantidade de vertices do grafo:" << endl;
    int numVertices = 0;
    cin >> numVertices;
    Grafo grafo(numVertices);
    grafo.inserirArestas();
    grafo.printarGrafo();
    cout << "Digite o vertice de inicio para a Busca de Profundidade:" << endl;
    char l1 = ' ';
    cin >> l1;
    int v1 = l1 - 'A';
    cout << v1;
    grafo.dfs(v1);
}