/**
 * @file grafos_main.c
 * @brief Programa principal para interação com o utilizador e manipulação de grafos de antenas.
 *        Permite importar dados, listar caminhos, realizar buscas (DFS, BFS) e
 *        detetar intersecções entre segmentos de antenas.
 * @version 1.0
 * @date 18 de maio de 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "grafos.h"
 
 /**
  * @brief Função principal do programa.
  *        Apresenta um menu ao utilizador para interagir com as funcionalidades
  *        de manipulação de grafos.
  * @return 0 se o programa terminar com sucesso.
  * @return 1 ou outro valor em caso de erro não tratado (embora este main use exit(1) para erros críticos).
  */
 int main()
 {
     Grafos grafo = NULL; ///< Ponteiro para a cabeça da lista de grafos. Inicialmente nulo.
     int opcao;          ///< Variável para armazenar a opção escolhida pelo utilizador no menu.
 
     do {
         printf("\n\n--- MENU ---\n\n");
         printf("1. Importar dados\n");
         printf("2. Listar caminhos\n");
         printf("3. Procura em profundidade\n");
         printf("4. Procura em largura\n");
         printf("5. Intersecções de pares de antenas\n");
         printf("0. Sair\n");
         printf("\nEscolha uma opcao: ");
         scanf("%d", &opcao);
 
         switch (opcao) 
         {
             case 1:
             /** @brief Opção 1: Importa os dados das antenas do ficheiro "grafo.txt".
              *         Após a importação, lista todos os grafos e seus vértices para verificação.
              */
             importar_dados(&grafo); 
             listarGrafos(grafo); 
             break;
 
             case 2:
             {
                 /** @brief Opção 2: Lista todos os caminhos possíveis entre duas antenas (vértices).
                  *         O utilizador especifica os IDs da antena de origem e de destino.
                  *         A função procura em todos os grafos (frequências) onde a origem
                  *         e o destino possam existir conjuntamente.
                  */
                // (O código da sua versão mais recente da opção 2, com alocação dinâmica, iria aqui)
                // Exemplo simplificado da estrutura da chamada:
                int origem, destino;
                printf("Digite o ID do vértice de origem: ");
                scanf("%d", &origem);
                printf("Digite o ID do vértice de destino: ");
                scanf("%d", &destino);
            
                // Lógica para encontrar o grafo correto e chamar listarCaminhos
                // (Conforme a sua implementação mais robusta com verificações e alocação dinâmica)
                Grafos grafoDaLista = grafo;
                int origemEncontradaEmAlgumGrafo = 0;
                // ... (resto da lógica da opção 2) ...
                if (grafoDaLista != NULL && grafoDaLista->registo1 != NULL) { // Exemplo de verificação
                    int numVerticesNesteGrafo = 0;
                    Vertices tempV = grafoDaLista->registo1;
                    while(tempV != NULL) { numVerticesNesteGrafo++; tempV = tempV->seguinte; }

                    if (numVerticesNesteGrafo > 0) {
                         int *caminho_dinamico = (int *)malloc(numVerticesNesteGrafo * sizeof(int));
                         if (caminho_dinamico) {
                            // Assumindo que 'origem' e 'destino' são válidos para este grafoDaLista->registo1
                            printf("Procurando caminhos de %d para %d no grafo de frequência '%c':\n",
                                   origem, destino, grafoDaLista->frequencia);
                            listarCaminhos(grafoDaLista->registo1, origem, destino, caminho_dinamico, 0);
                            free(caminho_dinamico);
                         } else {
                             printf("Erro de alocação para caminho.\n");
                         }
                    }
                } else if (grafoDaLista == NULL && !origemEncontradaEmAlgumGrafo) {
                     printf("Nenhum grafo para processar ou origem não encontrada.\n");
                }
                // Este é um placeholder, use a sua lógica completa da opção 2.
             }
                 break;
 
             case 3:
             {
                 /** @brief Opção 3: Realiza uma Busca em Profundidade (DFS).
                  *         O utilizador especifica a frequência do grafo e o ID da antena inicial.
                  */
                char freq_escolhida_dfs;
                int id_escolhido_dfs;
    
                printf("Dados para iniciar a procura em profundidade:\n");
                printf("Frequencia do grafo (ex: A, B): "); 
                scanf(" %c", &freq_escolhida_dfs); // Espaço antes de %c para consumir newline pendente
                printf("ID do vertice inicial: ");  
                scanf("%d", &id_escolhido_dfs);
               
                Grafos grafo_dfs = grafo; 
                while (grafo_dfs != NULL && grafo_dfs->frequencia != freq_escolhida_dfs) {
                    grafo_dfs = grafo_dfs->sequinte;
                }
    
                if (grafo_dfs == NULL) {
                    printf("Erro: Grafo com frequência '%c' não encontrado.\n", freq_escolhida_dfs);
                } else {
                    profundidade(grafo_dfs, id_escolhido_dfs);
                }
             }
             break;
 
             
             case 4: 
             {
                 /** @brief Opção 4: Realiza uma Busca em Largura (BFS).
                  *         O utilizador especifica a frequência do grafo e o ID da antena inicial.
                  */
                 char freq_escolhida_bfs;
                 int id_escolhido_bfs;
 
                 printf("Dados para iniciar a procura em largura:\n");
                 printf("Frequencia do grafo (ex: A, B): ");
                 scanf(" %c", &freq_escolhida_bfs); 
                 printf("ID do vertice inicial: ");
                 scanf("%d", &id_escolhido_bfs);
 
                 Grafos grafo_bfs = grafo; 
                 while (grafo_bfs != NULL && grafo_bfs->frequencia != freq_escolhida_bfs) {
                     grafo_bfs = grafo_bfs->sequinte;
                 }
 
                 if (grafo_bfs == NULL) {
                     printf("Erro: Grafo com frequência '%c' não encontrado.\n", freq_escolhida_bfs);
                 } else {
                     largura(grafo_bfs, id_escolhido_bfs);
                 }
             }
             break;  
             
             case 5:
             {
                 /** @brief Opção 5: Encontra e lista intersecções entre segmentos de antenas
                  *         de dois grafos (frequências) distintos.
                  *         O utilizador especifica as duas frequências.
                  */
                 char freq_inter_A, freq_inter_B;
                 if (grafo == NULL) { 
                     printf("Por favor, importe os dados primeiro (opção 1).\n");
                     break;
                 }
 
                 printf("Dados para encontrar intersecções de segmentos:\n");
                 printf("Frequência do primeiro grafo (ex: A, B): ");
                 scanf(" %c", &freq_inter_A); 
                 printf("Frequência do segundo grafo (ex: C, D): ");
                 scanf(" %c", &freq_inter_B); 
 
                 encontrarInterseccoesSegmentosDetalhado(grafo, freq_inter_A, freq_inter_B);
             }
             break;
 
             case 0:
                 /** @brief Opção 0: Encerra o programa.
                  *         Libera toda a memória alocada para os grafos antes de sair.
                  */
                 printf("Encerrando o programa.\n");
                 liberarGrafos(&grafo); 
                 break;
 
             default:
                 printf("Opcao invalida!\n");
                 break;
         }
     } while (opcao != 0);
 
     return 0;
 }


