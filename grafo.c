#include <stdio.h>
#include <stdlib.h>

#define TAM 6
#define TRUE 1
#define FALSE 0

typedef struct node Node;
struct node
{
	int verticePontaFinal;
	Node* prox;
};

typedef struct graph Graph;
struct graph
{
	Node* vetor[TAM];
};

typedef struct edge Edge;
struct edge
{
	int verticeInicial;
	int verticeFinal;
};

Graph* createGraph(int numVertices);
Graph* setGraph(Graph* graph, Edge vet[], int tamVetor);
Node* insereLista(Node* currentNode, int verticeInicial, int verticeFinal);
void printGraph(Graph* graph, int numTotalVertices);
int isEdgeIt(Graph* graph, int primeiroVertice, int ultVertice);
int isEdgeRec(Graph* graph, int primeiroVertice, int ultVertice);
int isEdgeRecAux(Node* node, int ultimoVertice);
void freeGraph(Graph* graph);

int main(void)
{
	Edge edges1[] = { {0,1}, {1,2}, {2,0}, {2,1}, {3,1}, {4,2} };
	Graph* graph = createGraph(6);
	if (graph == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		exit(1);
	}
	graph = setGraph(graph, edges1, TAM);
	if (graph == NULL)
	{
		printf("Erro ao alocar memoria.\n");
		exit(1);
	}
	printf("GRAPH:\n");
	printGraph(graph, 6);

	printf("TESTE DE ARESTAS:\n");
	printf("(2 -> 0) uma aresta?:\n");
	if (isEdgeIt(graph, 2, 0) == FALSE)
	{
		printf("Interativa: NAO\n");
	}
	else if (isEdgeIt(graph, 2, 0) == TRUE)
	{
		printf("Interativa: SIM\n");
	}
	if (isEdgeRec(graph, 2, 0) == FALSE)
	{
		printf("Recursiva: NAO\n");
	}
	else if (isEdgeRec(graph, 2, 0) == TRUE)
	{
		printf("Recursiva: SIM\n");
	}

	printf("(2 -> 4) uma aresta?:\n");
	if (isEdgeIt(graph, 2, 4) == FALSE)
	{
		printf("Interativa: NAO\n");
	}
	else if (isEdgeIt(graph, 2, 4) == TRUE)
	{
		printf("Interativa: SIM\n");
	}
	if (isEdgeRec(graph, 2, 4) == FALSE)
	{
		printf("Recursiva: NAO\n");
	}
	else if (isEdgeRec(graph, 2, 4) == TRUE)
	{
		printf("Recursiva: SIM\n");
	}

	freeGraph(graph);

	return 0;
}

// Cria um novo grafo alocando memória para a estrutura do grafo e inicializando cada posição do vetor como NULL
Graph* createGraph(int numVertices)
{
	Graph* newGraph = (Graph*)malloc(sizeof(Graph));
	if (newGraph == NULL)
	{
		return NULL; // Retorna NULL se a memória não puder ser alocada
	}

	for (int i = 0; i < numVertices; i++)
	{
		newGraph->vetor[i] = NULL; // Inicializa cada posição do vetor do grafo como NULL
	}

	return newGraph;
}

// Configura o grafo com as arestas fornecidas, inserindo os nós correspondentes em cada lista encadeada
Graph* setGraph(Graph* graph, Edge vet[], int tamVetor)
{
	int verticeIni;
	int verticeFi;

	for (int i = 0; i < tamVetor; i++)
	{
		verticeIni = vet[i].verticeInicial;
		verticeFi = vet[i].verticeFinal;

		graph->vetor[verticeIni] = insereLista(graph->vetor[verticeIni], verticeIni, verticeFi);
		// Insere um novo nó na lista encadeada correspondente ao vértice inicial
		// O novo nó é inserido no início da lista e aponta para o nó atual
		// O vértice inicial é usado para acessar a lista encadeada correta dentro do vetor do grafo

		if (graph->vetor[verticeIni] == NULL)
		{
			return NULL; // Retorna NULL se a memória não puder ser alocada
		}
	}

	return graph;
}

// Insere um novo nó na lista encadeada, no início da lista, e retorna o endereço do novo nó
Node* insereLista(Node* currentNode, int verticeInicial, int verticeFinal)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // Aloca memória para um novo nó
	if (newNode == NULL)
	{
		return NULL; // Retorna NULL se a memória não puder ser alocada
	}

	newNode->verticePontaFinal = verticeFinal; // Define o vértice final do novo nó
	newNode->prox = currentNode; // Faz o novo nó apontar para o nó atual (insere no início da lista)

	return newNode;
}

// Imprime o grafo, percorrendo todas as posições do vetor e imprimindo os vértices iniciais e finais de cada nó
void printGraph(Graph* graph, int numTotalVertices)
{
	for (int i = 0; i < numTotalVertices; i++)
	{
		Node* newNode = graph->vetor[i]; // Cria um novo nó e atribui a ele o endereço da posição "i" do vetor

		while (newNode != NULL)
		{
			printf("(%d -> %d)   ", i, newNode->verticePontaFinal); // Imprime o vértice inicial (i) e o vértice final de cada nó
			newNode = newNode->prox; // Avança para o próximo nó da lista
		}
	}
	printf("\n");
}

// Verifica se uma aresta existe no grafo de forma iterativa
int isEdgeIt(Graph* graph, int primeiroVertice, int ultVertice)
{
	if (graph == NULL)
	{
		return FALSE; // Retorna FALSE se o grafo for NULL, indicando que não há arestas
	}

	if (primeiroVertice < 0 || primeiroVertice >= TAM || ultVertice < 0 || ultVertice >= TAM)
	{
		return FALSE; // Retorna FALSE se o primeiro ou o último vértice estiverem fora do intervalo permitido
	}

	Node* currentNode = graph->vetor[primeiroVertice];

	while (currentNode != NULL)
	{
		if (currentNode->verticePontaFinal == ultVertice)
		{
			return TRUE; // Retorna TRUE se o vértice final de algum nó for igual ao último vértice
		}
		currentNode = currentNode->prox; // Avança para o próximo nó da lista
	}

	return FALSE; // Se percorrer todos os nós e não encontrar a aresta, retorna FALSE
}

// Verifica se uma aresta existe no grafo de forma recursiva
int isEdgeRec(Graph* graph, int primeiroVertice, int ultVertice)
{
	Node* currentNode = graph->vetor[primeiroVertice];
	if (currentNode == NULL)
	{
		return FALSE; // Retorna FALSE se o nó inicial for NULL, indicando que não há arestas
	}

	return isEdgeRecAux(currentNode, ultVertice);
}

// Função auxiliar para a verificação recursiva de arestas
int isEdgeRecAux(Node* node, int ultimoVertice)
{
	if (node == NULL)
	{
		return FALSE; // Retorna FALSE se o nó for NULL, indicando o final da lista
	}

	if (node->verticePontaFinal == ultimoVertice)
	{
		return TRUE; // Retorna TRUE se o vértice final do nó for igual ao último vértice
	}

	return isEdgeRecAux(node->prox, ultimoVertice); // Chama a função recursivamente com o próximo nó
}

// Libera a memória alocada para o grafo
void freeGraph(Graph* graph)
{
	for (int i = 0; i < TAM; i++)
	{
		Node* currentNode = graph->vetor[i];

		while (currentNode != NULL)
		{
			Node* nextNode = currentNode->prox;
			free(currentNode);
			currentNode = nextNode;
		}
	}

	free(graph);
	printf(">>> Grafo liberado com sucesso!\n");
}
