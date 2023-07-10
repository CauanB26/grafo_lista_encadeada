#include <stdio.h>
#include <stdlib.h>

#define TAM 6
#define TRUE 1
#define FALSE 0

typedef struct node Node;
struct node
{
	int verticePontaFinal;
	float valorPeso;
	Node* prox;
};

typedef struct graph Graph;
struct graph
{
	Node* vet[TAM];
};

typedef struct edge Edge;
struct edge
{
	int verticeInicial;
	int verticeFinal;
	float peso;
};

Graph* createGraph();
void initializeGraph(Graph* graph, int numTotalVertices);
Graph* setGraph(Graph* graph, Edge vet[], int tamVet);
Node* setGraphAux(Node* currentNode, int primeiroVertice, int ultimoVertice, float peso);
void printGraph(Graph* graph, int numTotalVertices);
int isEdgeIt(Graph* graph, int primeiroVertice, int segundoVertice);
int isEdgeItRec(Graph* graph, int primeiroVertice, int segundoVertice);
int isEdgeItRecAux(Node* currentNode, int segundoVertice);
float popularity(Graph* graph, int numVertices, float verticeEspecifico);
void freeGraph(Graph* graph);


int main(void)
{
	Edge edges1[] = { {0,1,0.3}, {1,2,0.8}, {2,0,0.4}, {2,1,0.5}, {3,1,0.7}, {4,2,1.0} };
	Graph* graph = createGraph();
	if (graph == NULL)
	{
		printf("Erro ao criar o grafo.\n");
		exit(1);
	}
	int verificaEdge;

	initializeGraph(graph, 6);
	graph = setGraph(graph, edges1, TAM);
	if (graph == NULL)
	{
		printf("Erro ao criar o grafo.\n");
		exit(1);
	}

	printf("GRAPH:\n");
	printGraph(graph, 6);

	printf("\n\nTESTES DE ARESTAS:\n");

	printf("(2 -> 0) uma aresta?:\n");
	verificaEdge = isEdgeIt(graph, 2, 0);
	if (verificaEdge == TRUE)
	{
		printf("Interativa: SIM\n");
	}
	else
	{
		printf("Interativa: NAO\n");
	}
	verificaEdge = isEdgeItRec(graph, 2, 0);

	if (verificaEdge == TRUE)
	{
		printf("Recursiva: SIM\n");
	}
	else
	{
		printf("Recursiva: NAO\n");
	}

	printf("(2 -> 4) uma aresta?:\n");

	verificaEdge = isEdgeIt(graph, 2, 4);
	if (verificaEdge == TRUE)
	{
		printf("Interativa: SIM\n");
	}
	else
	{
		printf("Interativa: NAO\n");
	}
	verificaEdge = isEdgeItRec(graph, 2, 4);

	if (verificaEdge == TRUE)
	{
		printf("Recursiva: SIM\n");
	}
	else
	{
		printf("Recursiva: NAO\n");
	}

	printf("\nPopularidade de cada vertice:\n");
	

	//Para facilar a compreensão testei todos os vértices possiveis como "verticeEspecifico"
	printf("Popularidade de 0 = %.1f\n", popularity(graph, 6, 0));
	printf("Popularidade de 1 = %.1f\n", popularity(graph, 6, 1));
	printf("Popularidade de 2 = %.1f\n", popularity(graph, 6, 2));
	printf("Popularidade de 3 = %.1f\n", popularity(graph, 6, 3));
	printf("Popularidade de 4 = %.1f\n", popularity(graph, 6, 4));

	printf("\n");
	freeGraph(graph);
	printf("\n");

	return 0;
}

Graph* createGraph()
{
	Graph* newGraph = (Graph*)malloc(sizeof(Graph)); //Cria o grafo
	if (newGraph == NULL)
	{
		return NULL;
	}
	return newGraph;
}

void initializeGraph(Graph* graph, int numTotalVertices)
{
	for (int i = 0; i < numTotalVertices; i++)
	{
		graph->vet[i] = NULL;
	}
}

Graph* setGraph(Graph* graph, Edge vet[], int tamVet)
{
	int primeiroVertice;
	int ultimoVertice;
	float peso;

	for (int i = 0; i < tamVet; i++)
	{
		primeiroVertice = vet[i].verticeInicial;
		ultimoVertice = vet[i].verticeFinal;
		peso = vet[i].peso;
		
		graph->vet[primeiroVertice] = setGraphAux(graph->vet[primeiroVertice], primeiroVertice, ultimoVertice, peso);
		if (graph->vet[primeiroVertice] == NULL)
		{
			return NULL;
		}
	}
	return graph;
}

Node* setGraphAux(Node* currentNode, int primeiroVertice, int ultimoVertice, float peso)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return NULL;
	}
	newNode->verticePontaFinal = ultimoVertice;
	newNode->valorPeso = peso;
	newNode->prox = currentNode;
	return newNode;
}

void printGraph(Graph* graph, int numTotalVertices)
{
	for (int i = 0; i < numTotalVertices; i++)
	{
		Node* currentNode = graph->vet[i];

		while (currentNode != NULL)
		{
			printf("(%d -> %d, %.1f)   ", i, currentNode->verticePontaFinal, currentNode->valorPeso);
			currentNode = currentNode->prox;
		}

	}

}

int isEdgeIt(Graph* graph, int primeiroVertice, int segundoVertice)
{
	if (graph == NULL)
	{
		return FALSE;
	}

	if (primeiroVertice < 0 || primeiroVertice > TAM || segundoVertice < 0 || segundoVertice > TAM)
	{
		return FALSE;
	}

	for (int i = 0; i < TAM; i++)
	{
		Node* currentNode = graph->vet[i];
		while (currentNode != NULL)
		{
			if (currentNode->verticePontaFinal == segundoVertice)
			{
				return TRUE;
			}
			currentNode = currentNode->prox;
		}
	}
	return FALSE;
}

int isEdgeItRec(Graph* graph, int primeiroVertice, int segundoVertice)
{
	if (graph == NULL)
	{
		return FALSE;
	}

	Node* currentNode = graph->vet[primeiroVertice];
	return isEdgeItRecAux(currentNode, segundoVertice);
}

int isEdgeItRecAux(Node* currentNode, int segundoVertice)
{
	if (currentNode == NULL)
	{
		return FALSE;
	}
	if (currentNode->verticePontaFinal == segundoVertice)
	{
		return TRUE;
	}

	return isEdgeItRecAux(currentNode->prox, segundoVertice);
}

float popularity(Graph* graph, int numVertices, float verticeEspecifico)
{
	float somaPesos = 0.0;

	for (int i = 0; i < numVertices; i++)
	{
		Node* currentNode = graph->vet[i];
		while (currentNode != NULL)
		{
			if (currentNode->verticePontaFinal == verticeEspecifico)
			{
				somaPesos = somaPesos + currentNode->valorPeso;
			}
			currentNode = currentNode->prox;
		}
	}
	return somaPesos;
}

void freeGraph(Graph* graph)
{
	for (int i = 0; i < TAM; i++)
	{
		Node* currentNode = graph->vet[i];

		while (currentNode != NULL)
		{
			Node* nextNode = currentNode->prox;
			free(currentNode);
			currentNode = nextNode;
		}
	}
	free(graph);
	printf(">>>Grafo liberado com sucesso!");
}
