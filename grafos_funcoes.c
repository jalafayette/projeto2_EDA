#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

/**
 * @brief Importa dados de um arquivo e preenche a lista ligada de vértices e suas listas de adjacências.
 * @param g Ponteiro para a lista ligada de vértices.
 */

 // Inserção de um novo vertice
void inserirVertice(Vertices *g, int idV, char freq, int l, int c) {
    Vertices novo = (Vertices)malloc(sizeof(struct registo1));
    if (novo == NULL) {
        printf("Erro: Falha na alocação de memória para o vértice.\n");
        exit(1);
    }
    novo->idVertice = idV;
    novo->frequencia = freq;
    novo->linha = l;
    novo->coluna = c;
    novo->adjacentes = NULL; // Inicializa a lista de adjacências como vazia
    novo->seguinte = *g;    // Adiciona o novo vértice ao início da lista
    *g = novo;              // Atualiza o ponteiro da lista
}

// Inserir a aresta idV1<->idV2
void inserirAdjacente(Vertices g, int idV1, int idV2) {
    Vertices aux = g; // aux de auxiliar
    while (aux != NULL) {
        if (aux->idVertice == idV1) {
            Adjacentes novo = (Adjacentes)malloc(sizeof(struct registo2));
            novo->idVertice = idV2;
            novo->seguinte = aux->adjacentes;
            aux->adjacentes = novo;
        }
        if (aux->idVertice == idV2) {
            Adjacentes novo = (Adjacentes)malloc(sizeof(struct registo2));
            novo->idVertice = idV1;
            novo->seguinte = aux->adjacentes;
            aux->adjacentes = novo;
        }
        aux = aux->seguinte;
    }
}

void importar_dados(Grafos *grafos) 
{
    FILE *arquivo = fopen("grafo.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo 'grafo.txt' para carregamento de dados.\n");
        return;
    }

    int idVertice = 0; // Identificador único para cada vértice
    int linha = 0;     // Coordenada Y
    char linha_buffer[256]; // Buffer para armazenar cada linha do arquivo

    printf("\nImportando dados das antenas...\n");

    // Ler o arquivo linha por linha
    while (fgets(linha_buffer, sizeof(linha_buffer), arquivo)) 
    {
        int coluna = 0; // Coordenada X
        int linha_comprimento = strlen(linha_buffer);

        // Remover o caractere de nova linha ('\n') no final da linha, se existir
        if (linha_buffer[linha_comprimento - 1] == '\n') 
        {
            linha_buffer[linha_comprimento - 1] = '\0';
            linha_comprimento--;
        }

        // Processar cada caractere da linha
        for (int i = 0; i < linha_comprimento; i++) 
        {
            char freq = linha_buffer[i];
            if (freq != '.') // Se não for um espaço vazio
            { 
                // Buscar ou criar o grafo correspondente à frequência
                Grafos grafoAtual = *grafos;
                while (grafoAtual != NULL && grafoAtual->frequencia != freq) {
                    grafoAtual = grafoAtual->sequinte;
                }

                if (grafoAtual == NULL) {
                    // Criar um novo grafo para a frequência
                    Grafos novoGrafo = (Grafos)malloc(sizeof(struct registo_Grafo));
                    if (novoGrafo == NULL) {
                        printf("Erro: Falha na alocação de memória para o grafo.\n");
                        exit(1);
                    }
                    novoGrafo->frequencia = freq;
                    novoGrafo->registo1 = NULL;
                    novoGrafo->sequinte = *grafos;
                    *grafos = novoGrafo;
                    grafoAtual = novoGrafo;
                }

                // Inserir o vértice no grafo correspondente
                inserirVertice(&(grafoAtual->registo1), idVertice, freq, linha, coluna);

                // Interligar o novo vértice com todos os outros vértices do mesmo grafo
                Vertices aux = grafoAtual->registo1;
                while (aux != NULL) {
                    if (aux->idVertice != idVertice) {
                        inserirAdjacente(grafoAtual->registo1, idVertice, aux->idVertice);
                    }
                    aux = aux->seguinte;
                }

                idVertice++;
            }
            coluna++;
        }
        linha++;
    }

    fclose(arquivo);
    printf("\nImportação concluída.\n");

    return;
}

void listarDados(Vertices g) {
    while (g != NULL) {
        printf("%d %c (%d, %d) [", g->idVertice, g->frequencia, g->linha, g->coluna);
        Adjacentes aux = g->adjacentes;
        while (aux != NULL) {
            printf("%d ", aux->idVertice);
            aux = aux->seguinte;
        }
        printf("]\n");
        g = g->seguinte;
    }
}

void listarGrafos(Grafos grafos) {
    while (grafos != NULL) {
        printf("\nGrafo da frequência '%c':\n", grafos->frequencia);
        listarDados(grafos->registo1);
        grafos = grafos->sequinte;
    }
}

void liberarGrafo(Vertices *g) 
{
  while (*g != NULL) {
      Vertices temp = *g;
      Adjacentes adj = temp->adjacentes;
      while (adj != NULL) {
          Adjacentes tempAdj = adj;
          adj = adj->seguinte;
          free(tempAdj);
      }
      *g = temp->seguinte;
      free(temp);
  }
}

void liberarGrafos(Grafos *grafos) {
    while (*grafos != NULL) {
        Grafos temp = *grafos;
        liberarGrafo(&(temp->registo1));
        *grafos = temp->sequinte;
        free(temp);
    }
}

/*
void listarcaminhosAUx(Adjacentes G[], int origem, int destino, int sequencia[], int posicao, int pesoTOtal)
{
  int i;
  Adjacentes aux;
  sequencia[posicao] = origem; 
  if (origem==destino)
  {
    for(i=0; i<posicao; i++) printf ("%d ", sequencia[i]); //escrita de um caminho
    printf("%d (%d)\n", destino, pesoTOtal);
    {
      printf("%d ", sequencia[i]);
    }
    else
    {
      aux = G[origem].Adjacentes;
      while (aux != NULL)
      {
        if (!visitado(sequencia, posicao, aux->id))
        {
          listarcaminhosAUx(G, aux->idVertice, destino, sequencia, posicao+1, pesoTOtal + aux->peso);
        }
        aux = aux->seguinte;
      }
    }
  }

}
*/

/*
visitado(sequencia, posicao, aux->id)
{
  int i;
  for (i=0; i<posicao; i++)
  {
    if (sequencia[i] == aux->id)
      return 1;
  }
  return 0;
}
*/

/*
void profundidade(Adjacentes Grafos[], int nodo)
{
  int visitados[VERTICES], i, v;
  Pilha s = NULL; 
  Adjacentes aux;
  
  for(i=0; i<VERTICES; i++) visitados[i]=0; // 0 = não visitado, 1 = visitado
  
  if (visitados[nodo]==0)
  {
    s = push(s, nodo);
    visitados[nodo]=1;
    
    while (!vazia(s))
    {
      v = top(s);
      s = pop(s);
      aux = Grafo[v];
      while(aux!=NULL)
      {
        if(nodo== aux->id)
        {
          listarPilha(s);
          return(1);
        }
        if (visitados[aux->id]==0)
        {
          s = push(s, aux->id);
          visitados[aux->id]=1;
        }
      }
    }
  } 
}
*/