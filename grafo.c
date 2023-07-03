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

// Cria um novo grafo alocando mem�ria para a estrutura do grafo e inicializando cada posi��o do vetor como NULL
Graph* createGraph(int numVertices)
{
	Graph* newGraph = (Graph*)malloc(sizeof(Graph));
	if (newGraph == NULL)
	{
		return NULL; // Retorna NULL se a mem�ria n�o puder ser alocada
	}

	for (int i = 0; i < numVertices; i++)
	{
		newGraph->vetor[i] = NULL; // Inicializa cada posi��o do vetor do grafo como NULL
	}

	return newGraph;
}

// Configura o grafo com as arestas fornecidas, inserindo os n�s correspondentes em cada lista encadeada
Graph* setGraph(Graph* graph, Edge vet[], int tamVetor)
{
	int verticeIni;
	int verticeFi;

	for (int i = 0; i < tamVetor; i++)
	{
		verticeIni = vet[i].verticeInicial;
		verticeFi = vet[i].verticeFinal;

		graph->vetor[verticeIni] = insereLista(graph->vetor[verticeIni], verticeIni, verticeFi);
		// Insere um novo n� na lista encadeada correspondente ao v�rtice inicial
		// O novo n� � inserido no in�cio da lista e aponta para o n� atual
		// O v�rtice inicial � usado para acessar a lista encadeada correta dentro do vetor do grafo

		if (graph->vetor[verticeIni] == NULL)
		{
			return NULL; // Retorna NULL se a mem�ria n�o puder ser alocada
		}
	}

	return graph;
}

// Insere um novo n� na lista encadeada, no in�cio da lista, e retorna o endere�o do novo n�
Node* insereLista(Node* currentNode, int verticeInicial, int verticeFinal)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // Aloca mem�ria para um novo n�
	if (newNode == NULL)
	{
		return NULL; // Retorna NULL se a mem�ria n�o puder ser alocada
	}

	newNode->verticePontaFinal = verticeFinal; // Define o v�rtice final do novo n�
	newNode->prox = currentNode; // Faz o novo n� apontar para o n� atual (insere no in�cio da lista)

	return newNode;
}

// Imprime o grafo, percorrendo todas as posi��es do vetor e imprimindo os v�rtices iniciais e finais de cada n�
void printGraph(Graph* graph, int numTotalVertices)
{
	for (int i = 0; i < numTotalVertices; i++)
	{
		Node* newNode = graph->vetor[i]; // Cria um novo n� e atribui a ele o endere�o da posi��o "i" do vetor

		while (newNode != NULL)
		{
			printf("(%d -> %d)   ", i, newNode->verticePontaFinal); // Imprime o v�rtice inicial (i) e o v�rtice final de cada n�
			newNode = newNode->prox; // Avan�a para o pr�ximo n� da lista
		}
	}
	printf("\n");
}

// Verifica se uma aresta existe no grafo de forma iterativa
int isEdgeIt(Graph* graph, int primeiroVertice, int ultVertice)
{
	if (graph == NULL)
	{
		return FALSE; // Retorna FALSE se o grafo for NULL, indicando que n�o h� arestas
	}

	if (primeiroVertice < 0 || primeiroVertice >= TAM || ultVertice < 0 || ultVertice >= TAM)
	{
		return FALSE; // Retorna FALSE se o primeiro ou o �ltimo v�rtice estiverem fora do intervalo permitido
	}

	Node* currentNode = graph->vetor[primeiroVertice];

	while (currentNode != NULL)
	{
		if (currentNode->verticePontaFinal == ultVertice)
		{
			return TRUE; // Retorna TRUE se o v�rtice final de algum n� for igual ao �ltimo v�rtice
		}
		currentNode = currentNode->prox; // Avan�a para o pr�ximo n� da lista
	}

	return FALSE; // Se percorrer todos os n�s e n�o encontrar a aresta, retorna FALSE
}

// Verifica se uma aresta existe no grafo de forma recursiva
int isEdgeRec(Graph* graph, int primeiroVertice, int ultVertice)
{
	Node* currentNode = graph->vetor[primeiroVertice];
	if (currentNode == NULL)
	{
		return FALSE; // Retorna FALSE se o n� inicial for NULL, indicando que n�o h� arestas
	}

	return isEdgeRecAux(currentNode, ultVertice);
}

// Fun��o auxiliar para a verifica��o recursiva de arestas
int isEdgeRecAux(Node* node, int ultimoVertice)
{
	if (node == NULL)
	{
		return FALSE; // Retorna FALSE se o n� for NULL, indicando o final da lista
	}

	if (node->verticePontaFinal == ultimoVertice)
	{
		return TRUE; // Retorna TRUE se o v�rtice final do n� for igual ao �ltimo v�rtice
	}

	return isEdgeRecAux(node->prox, ultimoVertice); // Chama a fun��o recursivamente com o pr�ximo n�
}

// Libera a mem�ria alocada para o grafo
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
