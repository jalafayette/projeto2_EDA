#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

/**
 * @brief Importa dados de um arquivo e preenche a lista ligada de vértices e suas listas de adjacências.
 * @param g Ponteiro para a lista ligada de vértices.
 */

 // Inserção de um novo vertice
void inserirVertice(Vertices *g, int idV, char freq, int l, int c) 
{
    Vertices novo = (Vertices)malloc(sizeof(struct registo1));
    if (novo == NULL) 
    {
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
void inserirAdjacente(Vertices g, int idV1, int idV2) 
{
    Vertices aux = g; // aux de auxiliar
    while (aux != NULL) 
    {
        if (aux->idVertice == idV1) 
        {
            Adjacentes novo = (Adjacentes)malloc(sizeof(struct registo2));
            novo->idVertice = idV2;
            novo->seguinte = aux->adjacentes;
            aux->adjacentes = novo;
        }
        if (aux->idVertice == idV2) 
        {
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
    if (!arquivo) 
    {
        printf("Erro ao abrir o arquivo 'grafo.txt' para carregamento de dados.\n");
        return;
    }

    int idVertice = 0; // Identificador único para cada vértice
    int linha = 0;     // Coordenada Y
    char linha_buffer[256]; // Buffer para armazenar cada linha do arquivo

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
                    if (aux->idVertice != idVertice) 
                    {
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

void listarDados(Vertices g) 
{
    while (g != NULL) 
    {
        printf("%d %c (%d, %d) [", g->idVertice, g->frequencia, g->linha, g->coluna);
        Adjacentes aux = g->adjacentes;
        while (aux != NULL) 
        {
            printf("%d ", aux->idVertice);
            aux = aux->seguinte;
        }
        printf("]\n");
        g = g->seguinte;
    }
}

void listarGrafos(Grafos grafos) 
{
    while (grafos != NULL) 
    {
        printf("\n\nGrafo da frequência '%c':\n\n", grafos->frequencia);
        printf("ID / Frequência / Localização (linha, coluna) / Adjacentes\n");
        listarDados(grafos->registo1);
        grafos = grafos->sequinte;
    }
}

void liberarGrafo(Vertices *g) 
{
  while (*g != NULL) 
  {
      Vertices temp = *g;
      Adjacentes adj = temp->adjacentes;
      while (adj != NULL) 
      {
          Adjacentes tempAdj = adj;
          adj = adj->seguinte;
          free(tempAdj);
      }
      *g = temp->seguinte;
      free(temp);
  }
}

void liberarGrafos(Grafos *grafos) 
{
    while (*grafos != NULL) 
    {
        Grafos temp = *grafos;
        liberarGrafo(&(temp->registo1));
        *grafos = temp->sequinte;
        free(temp);
    }
}

void listarCaminhos(Vertices grafo, int origem, int destino, int caminho[], int posicao) 
{
    // Verifica se os vértices de origem e destino pertencem ao mesmo grafo
    Vertices atual = grafo;
    int origemEncontrada = 0, destinoEncontrado = 0;

    while (atual != NULL) 
    {
        if (atual->idVertice == origem) 
        {
            origemEncontrada = 1;
        }
        if (atual->idVertice == destino) 
        {
            destinoEncontrado = 1;
        }
        atual = atual->seguinte;
    }

    if (!origemEncontrada || !destinoEncontrado) 
    {
        printf("Os vértices %d e %d pertencem a grafos diferentes ou não existem no mesmo grafo.\n", origem, destino);
        printf("Não há caminhos possíveis entre eles.\n");
        return;
    }

    // Adiciona o vértice atual ao caminho
    caminho[posicao] = origem;
    posicao++;

    if (origem == destino) 
    {
        // Se o vértice atual for o destino, imprime o caminho
        for (int i = 0; i < posicao; i++) 
        {
            if (i > 0) printf("->");
            printf("%d", caminho[i]);
        }
        printf("\n");
        return;
    }

    // Procura o vértice atual no grafo
    atual = grafo;
    while (atual != NULL && atual->idVertice != origem) 
    {
        atual = atual->seguinte;
    }

    if (atual == NULL) 
    {
        // Se o vértice não for encontrado, retorna
        return;
    }

    // Percorre os vértices adjacentes
    Adjacentes adj = atual->adjacentes;
    while (adj != NULL) 
    {
        // Usa a função visitado para verificar se o vértice já foi visitado
        if (!visitado(caminho, posicao, adj->idVertice)) 
        {
            // Chama recursivamente para o próximo vértice
            listarCaminhos(grafo, adj->idVertice, destino, caminho, posicao);
        }

        adj = adj->seguinte;
    }
}

// Função que verifica se um vértice já foi visitado
// parametros: caminho[] - array de vértices visitados
//            posicao - inteiro que guarda posição atual no array
//            id - id do vértice a ser verificado
int visitado(int caminho[], int posicao, int id) 
{
    for (int i = 0; i < posicao; i++) 
    {
        if (caminho[i] == id) 
        {
            return 1; // O vértice já foi visitado
        }
    }
    return 0; // O vértice ainda não foi visitado
}

// Função para remover um elemento à pilha
// pilha_cabeca é um ponteiro para a cabeça da pilha (NoDaPilha**)
// Retorna o novo topo da pilha (NoDaPilha*)
Pilha *pop(Pilha *pilha_cabeca) 
{
    if (pilha_cabeca == NULL || *pilha_cabeca == NULL) // Verifica se o ponteiro para a cabeça é NULL ou se a pilha está vazia
    {
        printf("Erro: A pilha está vazia.\n");
        return NULL;
    } 
    NoDaPilha *no_liberar = *pilha_cabeca;
    *pilha_cabeca = no_liberar->sequinte;
    free(no_liberar);
    return pilha_cabeca;
}

// Função para adicionar um elemento à pilha
// parametros: pilha_cabeca é um ponteiro para a cabeça da pilha (NoDaPilha**)
// Retorna o novo topo da pilha (NoDaPilha*)
Pilha push(Pilha *pilha_cabeca, int id) 
{
    NoDaPilha *novo_no = (NoDaPilha *)malloc(sizeof(NoDaPilha));
    if (novo_no == NULL) 
    {
        printf("Erro: Falha na alocação de memória para a pilha.\n");
        exit(1);
    }
    
    novo_no->id = id; 
    novo_no->sequinte = *pilha_cabeca; // O 'sequinte' do novo nó é o topo antigo
    *pilha_cabeca = novo_no; // Atualiza a cabeça da pilha para ser o novo nó
    
    return *pilha_cabeca;
}

// Função que retorna o elemento do topo da pilha
int top(Pilha pilha_cabeca) 
{
    if (pilha_cabeca == NULL) 
    {
        printf("Erro: A pilha está vazia.\n");
        return -1; // Retorna um valor de erro, ou lida com o erro de outra forma
    }
    return pilha_cabeca->id;
}

// Função que verifica se a pilha está vazia
int vazia(Pilha pilha_cabeca) 
{
    return (pilha_cabeca == NULL);
}

// ... (código anterior, como a função vazia) ...

/**
 * @brief Realiza uma Busca em Profundidade (DFS) em um grafo a partir de um vértice inicial.
 * 
 * @param grafo O grafo (conjunto de antenas e suas conexões) no qual a busca será realizada.
 * @param idVerticeInicial O ID da antena (vértice) de onde a busca deve começar.
 * 
 * ### Como Funciona a Busca em Profundidade (DFS) - De Forma Simples
 * 
 * Imagina que você está num labirinto e quer explorar todos os caminhos a partir de um ponto de partida.
 * A Busca em Profundidade (DFS, do inglês "Depth First Search") é uma maneira de fazer isso.
 * 
 * **O que são essas palavras esquisitas?**
 *   - **Grafo:** Pense no nosso conjunto de antenas. Cada antena é um "ponto" e as conexões
 *     entre elas são os "caminhos". Esse mapa de pontos e caminhos é um grafo.
 *   - **Vértice:** É cada "ponto" individual no nosso mapa, ou seja, cada antena.
 *   - **Adjacente (ou Vizinho):** Se duas antenas estão diretamente conectadas, elas são
 *     adjacentes ou vizinhas uma da outra.
 *   - **Pilha:** É como uma pilha de pratos. O último prato que você coloca é o primeiro
 *     que você tira. No nosso algoritmo, usamos uma pilha para lembrar quais antenas
 *     ainda precisamos explorar completamente.
 * 
 * **A Estratégia do "Explorador Curioso":**
 * 
 * 1.  **Ponto de Partida:** Começamos na antena que você escolheu (`idVerticeInicial`).
 * 
 * 2.  **Marcar e Lembrar:**
 *     - Marcamos essa antena inicial como "já visitei aqui" (para não visitarmos de novo sem querer).
 *     - Colocamos essa antena numa "lista de tarefas pendentes" (a nossa `pilha`). Essa lista
 *       nos diz: "ei, ainda tenho que ver os vizinhos desta antena!"
 * 
 * 3.  **Explorar Enquanto Houver Tarefas:**
 *     - Enquanto a nossa "lista de tarefas pendentes" (pilha) não estiver vazia, fazemos o seguinte:
 *       a. **Pegar a Tarefa Mais Recente:** Olhamos para a última antena que colocamos na lista
 *          (o topo da pilha). Vamos chamar essa de `antenaAtual`.
 *       b. **Tirar da Lista (Temporariamente):** Removemos a `antenaAtual` da lista de tarefas.
 *          Agora vamos focar nela.
 *       c. **"Visitar" de Fato:** Olhamos para as informações da `antenaAtual` (como suas coordenadas)
 *          e mostramos na tela.
 *       d. **Olhar os Vizinhos:** Agora, olhamos para todas as antenas vizinhas da `antenaAtual`.
 *       e. **Para cada Vizinho:**
 *          - Se ainda NÃO visitamos esse vizinho:
 *            - Marcamos o vizinho como "já visitei aqui".
 *            - Adicionamos esse vizinho à nossa "lista de tarefas pendentes" (pilha).
 *              Isso é importante! Ao adicionar à pilha, estamos dizendo: "Ok, encontrei um
 *              novo caminho/antena, vou explorá-lo AGORA o mais fundo possível antes de
 *              voltar para outros vizinhos da `antenaAtual` ou antenas anteriores."
 * 
 * 4.  **Por Que "Em Profundidade"?**
 *     - Porque, ao encontrar um vizinho novo e não visitado, o algoritmo imediatamente
 *       tenta explorar a partir DELE (colocando-o no topo da pilha). Ele vai "fundo"
 *       por um caminho antes de voltar (backtrack) e tentar outros caminhos que ficaram
 *       pendentes na pilha. É como seguir um corredor do labirinto até o fim antes de
 *       voltar para uma bifurcação anterior e tentar o outro corredor.
 * 
 * 5.  **Fim da Exploração:**
 *     - Quando a "lista de tarefas pendentes" (pilha) fica vazia, significa que exploramos
 *       todos os caminhos possíveis a partir da antena inicial.
 * 
 * **Em Resumo:** A DFS usa uma pilha para ir o mais fundo possível em um caminho, marcando
 * os lugares visitados. Quando não pode ir mais fundo, ela volta (graças à pilha) e tenta
 * outro caminho que ainda não foi totalmente explorado.
 */
void profundidade(Grafos grafo, int idVerticeInicial)
{
    if (grafo == NULL)
    {
        printf("Erro: O grafo fornecido é nulo.\n");
        return;
    }

    // Procura o vértice inicial no grafo
    Vertices verticeInicial = grafo->registo1;
    while (verticeInicial != NULL && verticeInicial->idVertice != idVerticeInicial)
    {
        verticeInicial = verticeInicial->seguinte;
    }

    if (verticeInicial == NULL)
    {
        printf("Erro: O vértice com ID %d não foi encontrado no grafo.\n", idVerticeInicial);
        return;
    }

    // Inicializa a pilha e o array de visitados
    int visitados[100] = {0}; // limite de 100 vértices
    Pilha pilha = NULL; 
    
    pilha = push(&pilha, idVerticeInicial); 
    visitados[idVerticeInicial] = 1;

    printf("Vértices alcançados a partir do vértice %d:\n", idVerticeInicial);

    // Realiza a busca em profundidade
    while (!vazia(pilha)) 
    {
        int idAtual = top(pilha); 
        pop(&pilha); 

        // Procura o vértice atual no grafo
        Vertices verticeAtual = grafo->registo1;
        while (verticeAtual != NULL && verticeAtual->idVertice != idAtual)
        {
            verticeAtual = verticeAtual->seguinte;
        }

        if (verticeAtual != NULL)
        {
            // Imprime as coordenadas do vértice atual
            printf("Vértice ID: %d, Coordenadas: (%d, %d)\n", verticeAtual->idVertice, verticeAtual->linha, verticeAtual->coluna);

            // Adiciona os vértices adjacentes não visitados à pilha
            Adjacentes adj = verticeAtual->adjacentes;
            while (adj != NULL)
            {
                if (!visitados[adj->idVertice])
                {
                    pilha = push(&pilha, adj->idVertice); // MODIFICADO
                    visitados[adj->idVertice] = 1;
                }
                adj = adj->seguinte;
            }
        }
    }

    printf("Busca em profundidade concluída.\n");
}


// --- Funções para a Fila usada na BFS ---

/**
 * @brief Cria e inicializa uma nova fila vazia.
 * @return Ponteiro para a nova fila criada, ou NULL se a alocação falhar.
 */
FilaBFS* criarFila() {
    FilaBFS *q = (FilaBFS*)malloc(sizeof(FilaBFS));
    if (q == NULL) {
        printf("Erro: Falha na alocação de memória para a fila.\n");
        return NULL;
    }
    q->inicio = NULL;
    q->fim = NULL;
    return q;
}

/**
 * @brief Verifica se a fila está vazia.
 * @param q Ponteiro para a fila.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int fila_vazia(FilaBFS *q) {
    if (q == NULL) return 1; // Considera uma fila não existente como vazia
    return (q->inicio == NULL);
}

/**
 * @brief Adiciona um elemento (id) ao final da fila.
 * @param q Ponteiro para a fila.
 * @param id O identificador do vértice a ser enfileirado.
 */
void enqueue(FilaBFS *q, int id) {
    if (q == NULL) {
        printf("Erro: Tentando enfileirar em uma fila não inicializada.\n");
        return;
    }
    NoDaFila *novo_no = (NoDaFila *)malloc(sizeof(NoDaFila));
    if (novo_no == NULL) {
        printf("Erro: Falha na alocação de memória para o nó da fila.\n");
        exit(1); // Ou outra forma de tratamento de erro crítico
    }
    novo_no->id = id;
    novo_no->sequinte = NULL;

    if (fila_vazia(q)) { // Se a fila está vazia
        q->inicio = novo_no;
        q->fim = novo_no;
    } else { // Adiciona ao final e atualiza o ponteiro 'fim'
        q->fim->sequinte = novo_no;
        q->fim = novo_no;
    }
}

/**
 * @brief Remove e retorna o elemento do início da fila.
 * @param q Ponteiro para a fila.
 * @return O ID do vértice desenfileirado, ou -1 se a fila estiver vazia (ou outro valor de erro).
 */
int dequeue(FilaBFS *q) {
    if (q == NULL || fila_vazia(q)) {
        // printf("Aviso: Tentando desenfileirar de uma fila vazia ou não inicializada.\n");
        return -1; // Indicador de erro/fila vazia
    }

    NoDaFila *temp = q->inicio;
    int id_removido = temp->id;

    q->inicio = q->inicio->sequinte;

    if (q->inicio == NULL) { // Se a fila ficou vazia após a remoção
        q->fim = NULL;
    }

    free(temp);
    return id_removido;
}

/**
 * @brief Libera toda a memória alocada para a fila.
 * @param q Ponteiro para o ponteiro da fila (para definir a fila como NULL após liberar).
 */
void liberarFilaBFS(FilaBFS **q_ref) {
    if (q_ref == NULL || *q_ref == NULL) {
        return;
    }
    FilaBFS *q = *q_ref;
    NoDaFila *atual = q->inicio;
    NoDaFila *proximo;
    while (atual != NULL) {
        proximo = atual->sequinte;
        free(atual);
        atual = proximo;
    }
    free(q);
    *q_ref = NULL; // Define o ponteiro da fila original como NULL
}

// --- Fim das Funções da Fila ---

/**
 * @brief Realiza uma Busca em Largura (BFS) em um grafo a partir de um vértice inicial.
 * 
 * @param grafo O grafo (conjunto de antenas e suas conexões) no qual a busca será realizada.
 * @param idVerticeInicial O ID da antena (vértice) de onde a busca deve começar.
 * 
 * ### Como Funciona a Busca em Largura (BFS) - De Forma Simples
 * 
 * Imagina que você está no centro de uma cidade (o `idVerticeInicial`) e quer
 * descobrir todas as ruas, mas de uma maneira organizada: primeiro todas as ruas
 * que estão a 1 quarteirão de distância, depois todas as que estão a 2 quarteirões,
 * e assim por diante. A Busca em Largura (BFS, do inglês "Breadth First Search")
 * faz exatamente isso.
 * 
 * **O que são essas palavras esquisitas?**
 *   - **Grafo, Vértice, Adjacente (Vizinho):** São os mesmos conceitos da DFS.
 *     O grafo é o mapa da cidade, os vértices são os cruzamentos (ou antenas),
 *     e os adjacentes são os cruzamentos diretamente conectados por uma rua.
 *   - **Fila:** Diferente da pilha (onde o último a entrar é o primeiro a sair),
 *     uma fila funciona como a fila do supermercado: o primeiro a entrar é o
 *     primeiro a sair (FIFO - First In, First Out). No nosso algoritmo, usamos
 *     uma fila para lembrar quais cruzamentos (antenas) precisamos visitar,
 *     mantendo a ordem de "níveis" de distância.
 * 
 * **A Estratégia do "Explorador Metódico por Níveis":**
 * 
 * 1.  **Ponto de Partida:** Começamos na antena que você escolheu (`idVerticeInicial`).
 * 
 * 2.  **Marcar e Enfileirar:**
 *     - Marcamos essa antena inicial como "já visitei aqui".
 *     - Colocamos essa antena numa "lista de espera para visita" (a nossa `fila`).
 * 
 * 3.  **Explorar Enquanto Houver Alguém na Fila:**
 *     - Enquanto a nossa "lista de espera" (fila) não estiver vazia, fazemos o seguinte:
 *       a. **Pegar o Próximo da Fila:** Chamamos o primeiro da fila (o que está lá há mais tempo).
 *          Vamos chamar essa de `antenaAtual`.
 *       b. **Tirar da Fila:** Removemos a `antenaAtual` da fila. Ela já foi processada.
 *       c. **"Visitar" de Fato:** Olhamos para as informações da `antenaAtual` (como suas coordenadas)
 *          e mostramos na tela.
 *       d. **Olhar os Vizinhos:** Agora, olhamos para todas as antenas vizinhas da `antenaAtual`.
 *       e. **Para cada Vizinho:**
 *          - Se ainda NÃO visitamos esse vizinho:
 *            - Marcamos o vizinho como "já visitei aqui".
 *            - Adicionamos esse vizinho ao FIM da nossa "lista de espera" (fila).
 *              Isso é crucial! Ao adicionar ao fim da fila, garantimos que todos os
 *              vizinhos do mesmo "nível" (mesma distância do início) sejam visitados
 *              antes de passarmos para os vizinhos do próximo nível.
 * 
 * 4.  **Por Que "Em Largura"?**
 *     - Porque o algoritmo explora o grafo camada por camada. Primeiro todos os vizinhos
 *       diretos do ponto inicial, depois todos os vizinhos desses vizinhos (que estão
 *       a duas conexões de distância do inicial), e assim por diante. Ele se expande
 *       "em largura" antes de ir mais "fundo".
 * 
 * 5.  **Fim da Exploração:**
 *     - Quando a "lista de espera" (fila) fica vazia, significa que exploramos
 *       todas as antenas alcançáveis a partir da antena inicial, nível por nível.
 * 
 * **Em Resumo:** A BFS usa uma fila para explorar o grafo em ondas, visitando todos
 * os vizinhos de um nível antes de passar para o próximo, sempre marcando os lugares
 * visitados para não repetir.
 */
void largura(Grafos grafo, int idVerticeInicial)
{
    if (grafo == NULL)
    {
        printf("Erro: O grafo fornecido é nulo.\n");
        return;
    }

    // Procura o vértice inicial no grafo
    Vertices verticeParaVerificar = grafo->registo1;
    int encontrado = 0;
    while (verticeParaVerificar != NULL)
    {
        if (verticeParaVerificar->idVertice == idVerticeInicial) {
            encontrado = 1;
            break;
        }
        verticeParaVerificar = verticeParaVerificar->seguinte;
    }

    if (!encontrado)
    {
        printf("Erro: O vértice com ID %d não foi encontrado no grafo '%c'.\n", idVerticeInicial, grafo->frequencia);
        return;
    }

    int visitados[100] = {0}; // Assumindo um máximo de 100 vértices. Idealmente, o tamanho seria dinâmico ou baseado no número de vértices.
    FilaBFS *fila = criarFila();
    if (fila == NULL) {
        return; // Erro na criação da fila
    }

    printf("Vértices alcançados (BFS) a partir do vértice %d no grafo '%c':\n", idVerticeInicial, grafo->frequencia);

    visitados[idVerticeInicial] = 1;
    enqueue(fila, idVerticeInicial);

    while (!fila_vazia(fila))
    {
        int idAtual = dequeue(fila);

        // Procura o vértice atual no grafo para obter seus detalhes e adjacências
        Vertices verticeAtual = grafo->registo1;
        while (verticeAtual != NULL && verticeAtual->idVertice != idAtual)
        {
            verticeAtual = verticeAtual->seguinte;
        }

        if (verticeAtual != NULL) // Deve sempre encontrar, pois só enfileiramos IDs válidos
        {
            printf("Vértice ID: %d, Freq: %c, Coordenadas: (%d, %d)\n",
                   verticeAtual->idVertice, verticeAtual->frequencia, verticeAtual->linha, verticeAtual->coluna);

            Adjacentes adj = verticeAtual->adjacentes;
            while (adj != NULL)
            {
                if (!visitados[adj->idVertice])
                {
                    visitados[adj->idVertice] = 1;
                    enqueue(fila, adj->idVertice);
                }
                adj = adj->seguinte;
            }
        } else {
            // Este caso não deveria acontecer se a lógica estiver correta
            // e os IDs no grafo e adjacências forem consistentes.
            printf("Alerta: Vértice com ID %d (da fila) não encontrado na lista de vértices do grafo.\n", idAtual);
        }
    }

    printf("Busca em largura concluída.\n");
    liberarFilaBFS(&fila); // Libera a memória da fila
}


int orientacaoVertices(Vertices p, Vertices q, Vertices r) {
    if (p == NULL || q == NULL || r == NULL) {
        // Tratar erro ou retornar um valor indicando entrada inválida
        // Para simplificar, vamos assumir que nunca serão NULL aqui,
        // pois serão chamados com vértices válidos.
        // Em um código robusto, verificações seriam necessárias.
        return -1; // Indicador de erro
    }
    // (q.coluna - p.coluna) * (r.linha - q.linha) - (q.linha - p.linha) * (r.coluna - q.coluna)
    // Usando p->coluna, p->linha etc.
    long long val = (long long)(q->coluna - p->coluna) * (r->linha - q->linha) -
                    (long long)(q->linha - p->linha) * (r->coluna - q->coluna);
    // Usar long long para evitar overflow no produto intermediário se as coordenadas forem grandes

    if (val == 0) return 0;  // Colinear
    return (val > 0) ? 1 : 2; // Horário ou Anti-horário
}


int noSegmentoVertices(Vertices p, Vertices q, Vertices r) {
    if (p == NULL || q == NULL || r == NULL) return 0;

    if (q->coluna <= (p->coluna > r->coluna ? p->coluna : r->coluna) && 
        q->coluna >= (p->coluna < r->coluna ? p->coluna : r->coluna) &&
        q->linha <= (p->linha > r->linha ? p->linha : r->linha) && 
        q->linha >= (p->linha < r->linha ? p->linha : r->linha))
        return 1; // true

    return 0; // false
}

/**
 * @brief Calcula as coordenadas do ponto de intersecção de dois segmentos de linha.
 * Pressupõe que a função segmentosVerticesSeIntersectam() já retornou verdadeiro para estes segmentos.
 * @param vA1 Primeiro vértice do primeiro segmento.
 * @param vA2 Segundo vértice do primeiro segmento.
 * @param vB1 Primeiro vértice do segundo segmento.
 * @param vB2 Segundo vértice do segundo segmento.
 * @param pontoDeInterseccao Ponteiro para a estrutura onde as coordenadas do ponto serão armazenadas.
 * @return 1 se um ponto de intersecção único foi calculado (segmentos não paralelos),
 *         0 se os segmentos são paralelos ou colineares (nenhum ponto único ou múltiplos pontos).
 */
int calcularCoordenadasPontoInterseccao(Vertices vA1, Vertices vA2, Vertices vB1, Vertices vB2, PontoFlutuante *pontoDeInterseccao) {
    if (!vA1 || !vA2 || !vB1 || !vB2 || !pontoDeInterseccao) return 0; // Verificação básica

    long long x1 = vA1->coluna, y1 = vA1->linha;
    long long x2 = vA2->coluna, y2 = vA2->linha;
    long long x3 = vB1->coluna, y3 = vB1->linha;
    long long x4 = vB2->coluna, y4 = vB2->linha;

    // Denominador para as equações paramétricas dos segmentos
    // D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    long long denominador = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (denominador == 0) {
        // Linhas são paralelas ou colineares.
        // A função segmentosVerticesSeIntersectam já tratou se há sobreposição colinear.
        // Para este cálculo, não há um *único* ponto de intersecção se são paralelas/colineares.
        return 0;
    }

    // Numerador para o parâmetro t (para o segmento vA1-vA2)
    // t_num = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)
    long long t_numerador = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);

    // Parâmetro t para o primeiro segmento (vA1vA2)
    double t = (double)t_numerador / denominador;

    // Calcula as coordenadas do ponto de intersecção usando o parâmetro t
    pontoDeInterseccao->x = (double)x1 + t * (x2 - x1);
    pontoDeInterseccao->y = (double)y1 + t * (y2 - y1);
    
    // A função segmentosVerticesSeIntersectam já garante que o ponto de intersecção
    // está dentro de ambos os segmentos se ela retornou true e o denominador não é zero.
    // Portanto, não precisamos revalidar 0 <= t <= 1 e 0 <= u <= 1 aqui.

    return 1; // Ponto de intersecção único calculado
}

int segmentosVerticesSeIntersectam(Vertices vP1, Vertices vQ1, Vertices vP2, Vertices vQ2) {
    if (vP1 == NULL || vQ1 == NULL || vP2 == NULL || vQ2 == NULL) return 0;
    // Evitar intersecção de um segmento consigo mesmo se os vértices forem os mesmos
    if ((vP1 == vP2 && vQ1 == vQ2) || (vP1 == vQ2 && vQ1 == vP2)) return 0;


    int o1 = orientacaoVertices(vP1, vQ1, vP2);
    int o2 = orientacaoVertices(vP1, vQ1, vQ2);
    int o3 = orientacaoVertices(vP2, vQ2, vP1);
    int o4 = orientacaoVertices(vP2, vQ2, vQ1);

    // Caso Geral
    if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0) {
         if (o1 != o2 && o3 != o4)
            return 1;
    }

    // Casos Especiais (Colineares)
    if (o1 == 0 && noSegmentoVertices(vP1, vP2, vQ1)) return 1;
    if (o2 == 0 && noSegmentoVertices(vP1, vQ2, vQ1)) return 1;
    if (o3 == 0 && noSegmentoVertices(vP2, vP1, vQ2)) return 1;
    if (o4 == 0 && noSegmentoVertices(vP2, vQ1, vQ2)) return 1;

    return 0; // Não se intersectam
}


/**
 * @brief Encontra e lista intersecções entre segmentos de linha formados por pares de antenas
 * de dois grafos com frequências distintas, incluindo as coordenadas do ponto de intersecção.
 * @param todosGrafos Ponteiro para a lista de todos os grafos.
 * @param freqA Frequência do primeiro grafo.
 * @param freqB Frequência do segundo grafo.
 */
void encontrarInterseccoesSegmentosDetalhado(Grafos todosGrafos, char freqA, char freqB) {
    if (freqA == freqB) {
        printf("As frequências devem ser distintas.\n");
        return;
    }

    Grafos grafoA = todosGrafos;
    while (grafoA != NULL && grafoA->frequencia != freqA) {
        grafoA = grafoA->sequinte;
    }

    Grafos grafoB = todosGrafos;
    while (grafoB != NULL && grafoB->frequencia != freqB) {
        grafoB = grafoB->sequinte;
    }

    if (grafoA == NULL) {
        printf("Erro: Grafo com frequência '%c' não encontrado.\n", freqA);
        return;
    }
    if (grafoB == NULL) {
        printf("Erro: Grafo com frequência '%c' não encontrado.\n", freqB);
        return;
    }

    printf("\nVerificando intersecções de segmentos (com coordenadas) entre antenas do grafo '%c' e grafo '%c':\n", freqA, freqB);
    int interseccoesEncontradas = 0;
    PontoFlutuante pontoInter;

    Vertices vA1 = grafoA->registo1;
    while (vA1 != NULL) {
        Vertices vA2 = vA1->seguinte;
        while (vA2 != NULL) {
            // Segmento do Grafo A: (vA1) --- (vA2)

            Vertices vB1 = grafoB->registo1;
            while (vB1 != NULL) {
                Vertices vB2 = vB1->seguinte;
                while (vB2 != NULL) {
                    // Segmento do Grafo B: (vB1) --- (vB2)

                    if (segmentosVerticesSeIntersectam(vA1, vA2, vB1, vB2)) {
                        printf("Intersecção detectada:\n");
                        printf("  Segmento Grafo '%c': Antena ID %d (%d,%d) -- Antena ID %d (%d,%d)\n",
                               freqA, vA1->idVertice, vA1->coluna, vA1->linha,
                               vA2->idVertice, vA2->coluna, vA2->linha);
                        printf("  Segmento Grafo '%c': Antena ID %d (%d,%d) -- Antena ID %d (%d,%d)\n",
                               freqB, vB1->idVertice, vB1->coluna, vB1->linha,
                               vB2->idVertice, vB2->coluna, vB2->linha);

                        if (calcularCoordenadasPontoInterseccao(vA1, vA2, vB1, vB2, &pontoInter)) {
                            printf("  Ponto de Intersecção: (%.2f, %.2f)\n\n", pontoInter.x, pontoInter.y);
                        } else {
                            // Isso ocorreria se segmentosVerticesSeIntersectam detectou uma sobreposição colinear.
                            // Nesses casos, não há um *único* ponto de intersecção pela fórmula usada.
                            printf("  Tipo de Intersecção: Sobreposição colinear (múltiplos pontos de intersecção).\n\n");
                        }
                        interseccoesEncontradas++;
                    }
                    vB2 = vB2->seguinte;
                }
                vB1 = vB1->seguinte;
            }
            vA2 = vA2->seguinte;
        }
        vA1 = vA1->seguinte;
    }

    if (interseccoesEncontradas == 0) {
        printf("Nenhuma intersecção de segmentos encontrada entre os grafos '%c' e '%c'.\n", freqA, freqB);
    } else {
        printf("Total de %d intersecções de segmentos detectadas.\n", interseccoesEncontradas);
    }
}




/*
// Arvore Binaria de Procura
int altura (ABP a)
{
    if (a == NULL)
        return 0;
    else
    {
        int altEsq = altura(a->esq);
        int altDir = altura(a->dir);
        
        if (altEsq > altDir)
        {
            return altEsq + 1;
        }
        else
        {
            return altDir + 1;
        }
    }

}
*/

/*
// listar todos os registos presentes num determinado nível
void listarNivel(ABP a, int nivel)
{
    if (a == NULL)
        return;
    if (nivel == 1)
    {
        printf("%d ", a->elem);
    }
    else
    {
        listarNivel(a->esq, nivel - 1);  // nivel - 1 para descer um nível
        listarNivel(a->dir, nivel - 1);
    }
}
*/