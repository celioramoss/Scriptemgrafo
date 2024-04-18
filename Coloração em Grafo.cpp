#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura para representar um v�rtice
typedef struct {
    int cor;
    int num_cores; // n�mero de cores dispon�veis
    int cores_disponiveis[MAX_VERTICES]; // cores dispon�veis para este v�rtice
} Vertice;

// Fun��o para inicializar um v�rtice
void inicializar_vertice(Vertice *v, int num_cores) {
    v->cor = -1; // cor inicialmente n�o atribu�da
    v->num_cores = num_cores;
    for (int i = 0; i < num_cores; i++) {
        v->cores_disponiveis[i] = 1; // todas as cores est�o inicialmente dispon�veis
    }
}

// Fun��o para adicionar uma aresta entre dois v�rtices
void adicionar_aresta(int grafo[MAX_VERTICES][MAX_VERTICES], int v1, int v2) {
    grafo[v1][v2] = 1;
    grafo[v2][v1] = 1;
}

// Fun��o para verificar se � seguro atribuir uma cor a um v�rtice
int eh_seguro(int cor, int grafo[MAX_VERTICES][MAX_VERTICES], Vertice vertices[], int v, int num_vertices) {
    for (int i = 0; i < num_vertices; i++) {
        if (grafo[v][i] && vertices[i].cor == cor)
            return 0; // a cor est� sendo usada por um vizinho
    }
    return 1; // a cor pode ser usada com seguran�a
}

// Fun��o de colora��o do grafo
void colorir_grafo(int grafo[MAX_VERTICES][MAX_VERTICES], Vertice vertices[], int num_vertices, int num_cores) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_cores; j++) {
            if (eh_seguro(j, grafo, vertices, i, num_vertices)) {
                vertices[i].cor = j; // atribui a cor j ao v�rtice i
                vertices[i].cores_disponiveis[j] = 0; // remove a cor j da lista de cores dispon�veis para i
                break;
            }
        }
    }
}

int main() {
    int num_vertices = 6; // n�mero de v�rtices do grafo
    int num_cores = 3; // n�mero de cores dispon�veis
    int grafo[MAX_VERTICES][MAX_VERTICES] = {0}; // inicializa a matriz de adjac�ncia com zeros
    Vertice vertices[MAX_VERTICES]; // array de v�rtices

    // Inicializa os v�rtices
    for (int i = 0; i < num_vertices; i++) {
        inicializar_vertice(&vertices[i], num_cores);
    }

    // Adiciona as arestas do grafo
    adicionar_aresta(grafo, 0, 1);
    adicionar_aresta(grafo, 0, 2);
    adicionar_aresta(grafo, 1, 2);
    adicionar_aresta(grafo, 1, 3);
    adicionar_aresta(grafo, 2, 3);
    adicionar_aresta(grafo, 3, 4);
    adicionar_aresta(grafo, 4, 5);

    // Colorir o grafo
    colorir_grafo(grafo, vertices, num_vertices, num_cores);

    // Imprime a cor de cada v�rtice
    printf("Cores dos vertices:\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("Vertice %d: Cor %d\n", i, vertices[i].cor);
    }

    return 0;
}

