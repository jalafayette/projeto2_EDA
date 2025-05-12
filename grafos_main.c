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
    Vertices grafo = NULL;
     int opcao;
 
    do 
    {
      printf("\n--- MENU ---\n");
      printf("1. Importar dados\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);
 
      switch (opcao) 
      {
        case 1:
        Grafos grafo = NULL; // Inicializa a lista ligada (grafo) de vértice(s)
        importar_dados(&grafo); // Importa os dados do arquivo e preenche a lista ligada
        printf("Dados importados com sucesso!\n");
        printf("Lista de antenas:\n");
        printf("ID / Frequencia / Linha / Coluna / Adjacentes\n");
        printf("------------------------------------------\n");
        listarGrafos(grafo); // Exibe os dados importados
        
        break;
             
            
        case 0:

        printf("Encerrando o programa.\n");
        liberarGrafos(&grafo); // Libera a memória alocada para os grafos
        exit(0);

        break;
        

        default:
        
        printf("Opcao invalida!\n");
        
        break;

      }
    } while (opcao != 0);  
    
  return 0;  
 }
  
    


