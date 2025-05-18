/**
 * @file main.c
 * @brief Programa principal para manipulação de antenas e efeitos nefastos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

/**
 * @brief Função principal do programa.
 */
int main()
{
    Grafos grafo = NULL;
    int opcao;

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
            
            importar_dados(&grafo); // Importa os dados do arquivo e preenche a lista ligada
            listarGrafos(grafo); // Exibe os dados importados
            break;

            case 2:
            
            int origem, destino;
            printf("Digite o ID do vértice de origem: ");
            scanf("%d", &origem);
            printf("Digite o ID do vértice de destino: ");
            scanf("%d", &destino);
        

            // Procura o grafo correspondente
            Grafos grafoAtual = grafo;
            while (grafoAtual != NULL) 
            {
                Vertices verticeAtual = grafoAtual->registo1;
                while (verticeAtual != NULL) 
                {
                    if (verticeAtual->idVertice == origem) 
                    {
                        printf("Caminhos de %d para %d:\n", origem, destino);
                        int caminho[100]; // Array para armazenar o caminho atual
                        listarCaminhos(grafoAtual->registo1, origem, destino, caminho, 0);
                        break;
                    }
                    verticeAtual = verticeAtual->seguinte;
                }
                grafoAtual = grafoAtual->sequinte;
            }
                break;

            case 3:


            // Adicionar chaves para criar um escopo local para as variáveis
            char freq_escolhida;
            int id_escolhido;

            printf("Dados para iniciar a procura em profundidade:\n");

            printf("\nFrequencia do grafo (ex: A, 0): "); scanf(" %c", &freq_escolhida);
            

            printf("\nID do vertice inicial: ");  scanf("%d", &id_escolhido);
           

            // Encontrar o grafo com a frequência especificada
            Grafos grafo_freq_esp = grafo; // 'grafo' é a cabeça da lista de todos os grafos
            while (grafo_freq_esp != NULL && grafo_freq_esp->frequencia != freq_escolhida) {
                grafo_freq_esp = grafo_freq_esp->sequinte;
            }

            if (grafo_freq_esp == NULL) {
                printf("Erro: Grafo com frequência '%c' não encontrado.\n", freq_escolhida);
            } else {
                // Chamar a função profundidade com o grafo correto e o ID inicial escolhido
                profundidade(grafo_freq_esp, id_escolhido);
            }
            break;

            
            case 4: // Novo case para a busca em largura
            {
                char freq_escolhida;
                int id_escolhido;

                printf("Dados para iniciar a procura em largura:\n");

                printf("\nFrequencia do grafo (ex: A, 0): ");
                scanf(" %c", &freq_escolhida); 

                printf("\nID do vertice inicial: ");
                scanf("%d", &id_escolhido);

                // Encontrar o grafo com a frequência especificada
                Grafos grafo_esp = grafo; // 'grafo' é a cabeça da lista de todos os grafos
                while (grafo_esp != NULL && grafo_esp->frequencia != freq_escolhida) {
                    grafo_esp = grafo_esp->sequinte;
                }

                if (grafo_esp == NULL) {
                    printf("Erro: Grafo com frequência '%c' não encontrado.\n", freq_escolhida);
                } else {
                    // Chamar a função largura com o grafo correto e o ID inicial escolhido
                    largura(grafo_esp, id_escolhido);
                }
                break;
            }  
            
            
            case 5:
            {
                char freq_inter_A, freq_inter_B;
                if (grafo == NULL) { // 'grafo' é a cabeça da lista de todos os grafos
                    printf("Por favor, importe os dados primeiro (opção 1).\n");
                    break;
                }

                printf("Dados para encontrar intersecções de segmentos:\n");
                printf("Frequência do primeiro grafo (ex: A, 0): ");
                scanf(" %c", &freq_inter_A); // Espaço antes de %c para consumir newlines

                printf("Frequência do segundo grafo (ex: B, 1): ");
                scanf(" %c", &freq_inter_B); // Espaço antes de %c

                encontrarInterseccoesSegmentosDetalhado(grafo, freq_inter_A, freq_inter_B);
                break;
            }

           

            case 0:
                printf("Encerrando o programa.\n");
                liberarGrafos(&grafo); // Libera a memória alocada para os grafos
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}



