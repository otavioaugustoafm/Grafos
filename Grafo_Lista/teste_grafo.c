#include <stdio.h>
#include <stdlib.h>

typedef struct Vizinho {
    int vertice;
    struct Vizinho* proximo; // Lista de vizinhos de um vértice
} Vizinho;

typedef struct Grafo {
    int numVertices;
    Vizinho** vertices; // Cada posição da lista responde aos vizinhos do vértice i
    int* visitado;
} Grafo;

Vizinho* criarVizinho(int vertice) {
    Vizinho* vizinho = malloc(sizeof(Vizinho));

    // Inicia o vizinho como NULL, pois ele se remete ao nó cabeça da fila
    vizinho->vertice = vertice;
    vizinho->proximo = NULL;

    return vizinho;
}

Grafo* criarGrafo(int qntVertices) {
    Grafo* grafo = malloc(sizeof(Grafo)); 

    grafo->numVertices = qntVertices;

    // Aloca a lista de vértices
    grafo->vertices = malloc(qntVertices * sizeof(Vizinho*)); 

    // Aloca a lista de marcadores de vértices  
    grafo->visitado = malloc(qntVertices * sizeof(int));

    // Inicializa cada lista de adjacência como vazia e marcados como não visitados
    for (int i = 0; i < qntVertices; i++) {
        grafo->vertices[i] = NULL;
        grafo->visitado[i] = 0;
    }

    return grafo;
}

int arestaExiste(Grafo* grafo, int v1, int v2) {
    Vizinho* temp = grafo->vertices[v1];
    while (temp != NULL) {
        if (temp->vertice == v2) {
            return 1;
        }
        temp = temp->proximo;
    }
    return 0;
}

void adicionarAresta(Grafo* grafo, int v1, int v2) {
    v1 -= 1;
    v2 -= 1;
    if (arestaExiste(grafo, v1, v2) == 1 || arestaExiste(grafo, v2, v1) == 1) {
        printf("Aresta ja existente...\n");
        return;
    }

    Vizinho* vizinho = criarVizinho(v2);
    vizinho->proximo = grafo->vertices[v1];
    grafo->vertices[v1] = vizinho;

    vizinho = criarVizinho(v1);
    vizinho->proximo = grafo->vertices[v2];
    grafo->vertices[v2] = vizinho;
}

int main() {
    int qntVertices = 0;
    printf("Digite a quantidade de vertices:\n");
    scanf("%d", &qntVertices);
    Grafo* grafo = criarGrafo(qntVertices);
    int v1 = 0, v2 = 0;
    printf("Digite os vertices que serao adicionados arestas (Ex: 1 2):\n\nDigite -1 para parar de inserir:\n");
    while(1) {
        scanf("%d", &v1);
        if (v1 < 0 || v2 < 0) {
            break;
        }
        scanf("%d", &v2);
        adicionarAresta(grafo, v1, v2);
    }
    
    for(int i = 0; i < qntVertices; i++) {
        Vizinho* temp = grafo->vertices[i];
        
        printf("Vertice %d: ", i + 1);
        while(temp != NULL) {
            printf("-> %d ", temp->vertice + 1);
            temp = temp->proximo;
        }
        printf("\n");
    }
}