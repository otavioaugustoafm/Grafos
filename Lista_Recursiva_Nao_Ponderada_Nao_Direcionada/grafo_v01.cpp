#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stack>    

class Grafo {
    private:
        int qntVertices;
        std::vector<std::vector<int>> listaAdj;
        std::vector<bool> visitado;

    public:
        Grafo(int qntVertices) {
            this->qntVertices = qntVertices;
            listaAdj.resize(qntVertices);
            visitado.resize(qntVertices);
        }

        void adicionarAresta(int v1, int v2) {
            if (v1 < 1 || v2 < 1 || v1 > qntVertices || v2 > qntVertices) {
                std::cout << "Vertice invalido: Negativo, inexistente ou maior que o limite." << std::endl;
                return;
            }
            v1--; v2--;
            auto busca = std::find(listaAdj[v1].begin(), listaAdj[v1].end(), v2);
            if (busca != listaAdj[v1].end()) {
                std::cout << "Aresta ja existente..." << std::endl;
                return;
            }
            listaAdj[v1].push_back(v2);
            listaAdj[v2].push_back(v1);
        }

        void printarGrafo() {
            for (int i = 0; i < listaAdj.size(); i++) {
                std::cout << "Vertice " << i + 1 << ": ";
                bool seta = true;
                for (int j : listaAdj[i]) {
                    if (!seta) {
                        std::cout << " -> ";
                    }
                    std::cout << j + 1;
                    seta = false;
                }
                std::cout << std::endl;
            }
        }
        
        void ordenarVetor() {
            for (auto& vizinhos : listaAdj) {
                std::sort(vizinhos.begin(), vizinhos.end());
            }
        }

        void dfs_chamada() {
            std::fill(visitado.begin(), visitado.end(), false);
            std::cout << "Digite o vertice de inicio da Busca por Profundidade:" << std::endl;
            char letra = ' ';
            std::cin >> letra;
            int vertice = letra - 'A';
            dfs_recursivo(vertice);
            std::cout << std::endl;
        }

        void dfs_recursivo(int vertice) {
            visitado[vertice] = true;
            char letra = vertice + 'A';
            std::cout << letra << " ";

            for (int vizinho : listaAdj[vertice]) {
                if(!visitado[vizinho]) {
                    dfs_recursivo(vizinho);
                }
            }
        }
};

int main() {
    std::stack<int> pilha;
    int qntVertices = 0, v1 = 0, v2 = 0; 
    char l1 = ' ', l2 = ' ';

    std::cout << "Digite a quantidade de vertices do grafo:" << std::endl;
    std::cin >> qntVertices;
    Grafo grafo(qntVertices);

    std::cout << "Digite as arestas do grafo (Ex: A B):\nPare com 1." << std::endl;
    while(1) {
        std::cin >> l1;
        if (l1 == '1') {
            break;
        }
        std::cin >> l2;
        v1 = l1 - 'A' + 1;
        v2 = l2 - 'A' + 1;
        grafo.adicionarAresta(v1, v2);
    }

    grafo.ordenarVetor();

    grafo.printarGrafo();

    grafo.dfs_chamada();
    }