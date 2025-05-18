#ifndef GRAFOS_H
#define GRAFOS_H

/**
 * @file grafos.h
 * @brief Ficheiro de cabeçalho para as estruturas de dados e protótipos de funções
 *        relacionadas com a manipulação de grafos de antenas.
 * @version 1.0
 * @date 18 de maio de 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Estruturas de Dados ---

/**
 * @struct registo2
 * @brief Estrutura para representar um nó na lista de adjacências de um vértice.
 *        Indica um vértice que é adjacente ao vértice "pai".
 */
typedef struct registo2 {
    int idVertice;          ///< Identificador do vértice adjacente.
    struct registo2 *seguinte; ///< Ponteiro para o próximo nó na lista de adjacências.
} * Adjacentes;

/**
 * @struct registo1
 * @brief Estrutura para representar um vértice (antena) no grafo.
 *        Contém informações sobre a antena e a lista das suas adjacências.
 */
typedef struct registo1 {
    int idVertice;          ///< Identificador único do vértice/antena.
    char frequencia;        ///< Frequência de ressonância da antena.
    int linha;              ///< Coordenada linha da antena na grelha.
    int coluna;             ///< Coordenada coluna da antena na grelha.
    Adjacentes adjacentes;  ///< Ponteiro para a lista de vértices adjacentes.
    struct registo1 *seguinte; ///< Ponteiro para o próximo vértice na lista de vértices do mesmo grafo/frequência.
} * Vertices;

/**
 * @struct registo_Grafo
 * @brief Estrutura para representar um grafo, agrupando antenas de uma mesma frequência.
 *        Cada grafo corresponde a uma frequência específica e contém uma lista de vértices (antenas)
 *        que operam nessa frequência.
 */
typedef struct registo_Grafo {
    char frequencia;        ///< Frequência de ressonância associada a este grafo.
    Vertices registo1;      ///< Ponteiro para a lista de vértices (antenas) pertencentes a este grafo.
    struct registo_Grafo *sequinte; ///< Ponteiro para o próximo grafo na lista de grafos (para diferentes frequências).
} * Grafos;


/**
 * @struct NoDaPilha
 * @brief Estrutura para representar um nó numa pilha.
 *        Usado para implementar a pilha necessária para a Busca em Profundidade (DFS).
 */
typedef struct NoDaPilha {
    int id;                 ///< Identificador (geralmente de um vértice) armazenado no nó da pilha.
    struct NoDaPilha *sequinte; ///< Ponteiro para o próximo nó na pilha (o nó abaixo).
} NoDaPilha;

/**
 * @typedef Pilha
 * @brief Define Pilha como um ponteiro para NoDaPilha, representando o topo da pilha.
 */
typedef NoDaPilha* Pilha;


/**
 * @struct NoDaFila
 * @brief Estrutura para representar um nó numa fila.
 *        Usado para implementar a fila necessária para a Busca em Largura (BFS).
 * @note Esta estrutura é idêntica a NoDaPilha e poderia ser reutilizada ou generalizada.
 */
typedef struct NoDaFila {
    int id;                 ///< Identificador (geralmente de um vértice) armazenado no nó da fila.
    struct NoDaFila *sequinte; ///< Ponteiro para o próximo nó na fila.
} NoDaFila;

/**
 * @struct FilaBFS
 * @brief Estrutura para representar uma fila, contendo ponteiros para o início e o fim.
 *        Usada para a Busca em Largura (BFS).
 */
typedef struct FilaBFS {
    NoDaFila *inicio;       ///< Ponteiro para o primeiro nó da fila.
    NoDaFila *fim;          ///< Ponteiro para o último nó da fila.
} FilaBFS;

/**
 * @struct PontoFlutuante
 * @brief Estrutura para representar um ponto com coordenadas de vírgula flutuante (x, y).
 *        Usada para armazenar as coordenadas de um ponto de intersecção entre segmentos.
 */
typedef struct PontoFlutuante {
    double x;               ///< Coordenada x do ponto.
    double y;               ///< Coordenada y do ponto.
} PontoFlutuante;


// --- Protótipos das Funções ---

// Funções de Manipulação de Grafos e Vértices
void inserirVertice(Vertices *g, int idV, char freq, int l, int c);
void inserirAdjacente(Vertices g, int idV1, int idV2);
void importar_dados(Grafos *grafos);
void listarDados(Vertices g);
void listarGrafos(Grafos gLista);
void liberarGrafo(Vertices *g);
void liberarGrafos(Grafos *gLista);

// Funções de Busca e Caminhos
int visitado(int caminho[], int posicao, int id);
void listarCaminhos(Vertices listaVertices, int origem, int destino, int caminho[], int indiceCaminho);

// Funções de Pilha (para DFS)
Pilha *pop(Pilha *pilha_cabeca);
Pilha push(Pilha *pilha_cabeca, int id);
int top(Pilha pilha_cabeca);
int vazia(Pilha pilha_cabeca);
void profundidade(Grafos grafo, int idVerticeInicial);

// Funções de Fila (para BFS)
FilaBFS* criarFila();
int fila_vazia(FilaBFS *q);
void enqueue(FilaBFS *q, int id);
int dequeue(FilaBFS *q);
void liberarFilaBFS(FilaBFS **q_ref);
void largura(Grafos grafo, int idVerticeInicial);

// Funções para Deteção de Intersecções
int orientacaoVertices(Vertices p, Vertices q, Vertices r);
int noSegmentoVertices(Vertices p, Vertices q, Vertices r);
int calcularCoordenadasPontoInterseccao(Vertices vA1, Vertices vA2, Vertices vB1, Vertices vB2, PontoFlutuante *pontoDeInterseccao);
int segmentosVerticesSeIntersectam(Vertices vP1, Vertices vQ1, Vertices vP2, Vertices vQ2);
void encontrarInterseccoesSegmentosDetalhado(Grafos todosGrafos, char freqA, char freqB);

#endif