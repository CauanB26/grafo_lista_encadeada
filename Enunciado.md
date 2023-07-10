Grafo Dirigido como lista encadeada


Passo a passo da questão:

Passo 1)
Definir as seguintes estruturas:

•Node (que contém o vértice ponta final da aresta, o valor do peso e o ponteiro para o próximo Node)

•Graph (que contém um vetor estático de ponteiros para Node)

•Edge (que especifica uma aresta com o vértice inicial, o vértice final e o peso).

Passo 2)
Criar e testar as seguintes funções:

•Função createGraph para simplesmente criar o grafo, sem inicializá-lo.

•Função inicializarGraph para inicializar o grafo com um vetor de ponteiros para NULL. Essa função recebe
o grafo e o número de vértices.

•Função setGraph para montar o grafo. Essa função recebe um ponteiro para Graph, o vetor de arestas (edges1, que será
mostrado mais adiante no enunciado) e o tamanho desse vetor.

•Função printGraph que imprime o grafo, dados um ponteiro para Graph e o número total de vértices.

•Função que testa se dois vértices dados são uma aresta do grafo dirigido. Essa função recebe um ponteiro para Graph 
e os dois vértices, e retorna verdadeiro ou falso. Faça uma versão iterativa isEdgeIt e outra recursiva isEdgeRec.

•Função popularity que, dado um ponteiro para Graph, o número de vértices e um vértice específico, retorna a soma dos 
pesos das arestas que chegam a esse vértice. Essa soma pode ser interpretada como sendo um índice de popularidade.

•Função freeGraph, que libera a memória do graph e dos nodes.

Passo 3)
Adicione na main o seguinte vetor de arestas:

Edge edges1[] ={ {0,1}, {1,2}, {2,0}, {2,1}, {3,1}, {4,2} };
