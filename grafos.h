#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdio.h>  // Para funções de entrada e saída, como printf
#include <stdlib.h> // Para alocação dinâmica de memória, como malloc e free



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

typedef struct registo_Grafo {
    char frequencia;         // Frequência do grafo
    Vertices registo1;       // Lista de vértices do grafo
    struct registo_Grafo *sequinte; // grafo sequinte
} *Grafos;

void inserirVertice(Vertices *g, int idV, char freq, int l, int c);

void importar_dados(Grafos *grafos);

void inserirAdjacente(Vertices g, int idV1, int idV2);

void listarDados(Vertices g);

void listarGrafos(Grafos grafos);

void liberarGrafo(Vertices *g);

void liberarGrafos(Grafos *grafos);

#endif