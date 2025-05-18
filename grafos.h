#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdio.h>  // Para funções de entrada e saída, como printf
#include <stdlib.h> // Para alocação dinâmica de memória, como malloc e free

/*
struct registo_ABP{
int elem;
struct registo * esq;
struct regirsto *dir;
} * ABP;
*/

typedef struct registo2
{ int idVertice;
  struct registo2 * seguinte;
} * Adjacentes;

typedef struct registo1
{int idVertice;   // identificador antena
 char frequencia; // frequencia antena
 int linha;       // localização antena
 int coluna;
 struct registo2 *adjacentes; // lista de adjacentes
 struct registo1 * seguinte;
} * Vertices;

typedef struct registo_Grafo 
{ char frequencia;         // Frequência do grafo
  Vertices registo1;       // Lista de vértices do grafo
  struct registo_Grafo *sequinte; // grafo sequinte
} *Grafos;





// Definição de uma pilha para armazenar os vértices visitados
typedef struct Pilha
{ int id;
  struct Pilha *sequinte;
} NoDaPilha;

typedef NoDaPilha *Pilha;


typedef struct Pilha NoDaFila; // Reutilizando a estrutura do nó

typedef struct FilaBFS {
    NoDaFila *inicio; // Ponteiro para o primeiro nó da fila
    NoDaFila *fim;    // Ponteiro para o último nó da fila
} FilaBFS;

// para a funçao intercecções
typedef struct PontoFlutuante {
  double x;
  double y;
} PontoFlutuante;

void inserirVertice(Vertices *g, int idV, char freq, int l, int c);

void importar_dados(Grafos *grafos);

void inserirAdjacente(Vertices g, int idV1, int idV2);

void listarDados(Vertices g);

void listarGrafos(Grafos grafos);

void liberarGrafo(Vertices *g);

void liberarGrafos(Grafos *grafos);

void listarCaminhos(Vertices grafo, int origem, int destino, int caminho[], int posicao);

int visitado(int caminho[], int posicao, int id);

void profundidade(Grafos grafo, int idVerticeInicial);

Pilha *pop(Pilha *pilha_cabeca);

Pilha push(Pilha *pilha_cabeca, int id);

int top(Pilha pilha_cabeca);

int vazia(Pilha pilha_cabeca);

FilaBFS* criarFila();

int fila_vazia(FilaBFS *q);

void enqueue(FilaBFS *q, int id);

int dequeue(FilaBFS *q);

void liberarFilaBFS(FilaBFS **q_ref);

void largura(Grafos grafo, int idVerticeInicial);

int noSegmentoVertices(Vertices p, Vertices q, Vertices r);

int orientacaoVertices(Vertices p, Vertices q, Vertices r);

int calcularCoordenadasPontoInterseccao(Vertices vA1, Vertices vA2, Vertices vB1, Vertices vB2, PontoFlutuante *pontoDeInterseccao);

int segmentosVerticesSeIntersectam(Vertices vP1, Vertices vQ1, Vertices vP2, Vertices vQ2);

void encontrarInterseccoesSegmentosDetalhado(Grafos todosGrafos, char freqA, char freqB);

#endif