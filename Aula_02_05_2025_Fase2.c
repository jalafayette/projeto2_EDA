#include <stdio.h>
#include <stdlib.h>

// Fase 2

typedef struct registo2
{
   int idVertice;
  struct registo2 * seguinte;

} * Adjacentes;


typedef struct registo1
{
  int idVertice;   // identificador antena
 char frequencia; // frequencia antena
 int linha;       // localização antena
 int coluna;
 Adjacentes adjacentes; // antenas adjacentes
 struct registo1 * seguinte;

} * Vertices;


// Inserção de um novo vertice
Vertices inserirVertice(Vertices g, int idV, char freq, int l, int c)
{
  Vertices novo = (Vertices) malloc(sizeof(struct registo1));
 novo->idVertice = idV;
 novo->frequencia = freq;
 novo->linha = l;
 novo->coluna = c;
 novo->adjacentes = NULL;
 novo->seguinte = g;
 return(novo);
}

// Inserir a aresta idV1<->idV2
void inserirAdjacente(Vertices g, int idV1, int idV2)
{
  Vertices aux = g;
 while (aux!=NULL)
 {if (aux->idVertice == idV1)
	 {Adjacentes novo = (Adjacentes) malloc(sizeof(struct registo2));
	  novo->idVertice = idV2;
	  novo->seguinte = aux->adjacentes;
	  aux->adjacentes = novo;
	 }
  if (aux->idVertice == idV2)
	 {Adjacentes novo = (Adjacentes) malloc(sizeof(struct registo2));
	  novo->idVertice = idV1;
	  novo->seguinte = aux->adjacentes;
	  aux->adjacentes = novo;
	 }
  aux=aux->seguinte;
 }
}


void listarDados(Vertices g)
{
  while (g!=NULL)
 {printf("%d %c %d %d [", g->idVertice, g->frequencia, g->linha, g->coluna);
  Adjacentes aux = g->adjacentes; 
  while (aux!=NULL)
  {printf("%d ", aux->idVertice);
   aux = aux->seguinte;
  }
  printf("]\n");
  g = g->seguinte;
 }
}

int main()
{
  Vertices grafo = NULL;

 grafo = inserirVertice(grafo, 1, 'A', 2, 4);
 grafo = inserirVertice(grafo, 2, 'A', 5, 3);
 grafo = inserirVertice(grafo, 3, 'A', 1, 4);
 grafo = inserirVertice(grafo, 4, 'A', 5, 4);
 inserirAdjacente(grafo,1,2);
 inserirAdjacente(grafo,2,3);
 inserirAdjacente(grafo,1,3);
 inserirAdjacente(grafo,3,4);
 inserirAdjacente(grafo,1,4);
 inserirAdjacente(grafo,4,2);
 listarDados(grafo);
 return(0);
}
