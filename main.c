#include <stdio.h>

void imprime_matriz(unsigned int n, unsigned int X[n][n])
{
	int i,j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d\t", X[i][j]);
		}
		printf("\n");
	}
}

void matriz_de_arquivo(unsigned int n, unsigned int adjacencias[n][n], char* caminho)
{
	int i, j;
	
	FILE *f;
  	f = fopen(caminho, "r");
	
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; j++)
		{
			if (!fscanf(f, "%d", &adjacencias[i][j])) 
           		break;
		}	
	}

	fclose(f);

}

void push(unsigned int n, unsigned int* cabeca, unsigned int* cauda, unsigned int fila[n], unsigned int valor)
{
	// caso da fila cheia
	if ( (*cauda - *cabeca) == (n - 1) )
	{
		printf("Fila cheia!\n");
	} else
	{
		// caso da fila vazia
		if (*cabeca > *cauda)
		{
			*cabeca = 0;
			*cauda = 0;
		} else 
		{
			*cauda = *cauda + 1;		
		}
		fila[*cauda % n] = valor;
	}
	
}

int pop(unsigned int n, unsigned int* cabeca, unsigned int* cauda, unsigned int fila[n])
{
	unsigned int retorno;
	
	if (*cabeca > *cauda)
	{
		printf("Fila vazia!\n");
		return -1;
	}
	
	retorno = fila[*cabeca % n];
	*cabeca = *cabeca + 1;
	return retorno;
}

void busca_em_largura(unsigned int n, unsigned int adjacencias[n][n], unsigned int raiz)
{
	unsigned int enfileirado[n];
	unsigned int i, atual;
	unsigned int cabeca = 0;
	unsigned int cauda = -1;
	unsigned int fila[n];
	
	for (i = 0; i < n; i++)
	{
		enfileirado[i] = 0;
	}

	push(n, &cabeca, &cauda, fila, raiz);
	enfileirado[raiz] = 1;
	
	// enquanto existem elementos na fila
	while ((atual = pop(n, &cabeca, &cauda, fila)) != -1)
	{
		// imprime o elemento atual
		printf("%d\t", atual);
		
		for (i = 0; i < n; i++)
		{
			// se i possui uma aresta e ainda nao foi enfileirado, adicione na fila e marque como enfileirado
			if (adjacencias[i][atual] > 0 && enfileirado[i] == 0)
			{
				push(n, &cabeca, &cauda, fila, i);
				enfileirado[i] = 1;
			}
		}
	}
}

void busca_em_profundidade(unsigned int n, unsigned int adjacencias[n][n], unsigned int raiz, unsigned int visitado[n])
{
	unsigned int i;

	printf("%d\t", raiz);
	visitado[raiz] = 1;

	for (i = 0; i < n; i++)
	{
		// se i possui uma aresta e ainda nao foi visitado, visite
		if (adjacencias[i][raiz] > 0 && visitado[i] == 0)
		{
			busca_em_profundidade(n, adjacencias, i, visitado);
		}
	}
	
}

int main()
{
	
	unsigned int n = 5;
	unsigned int adjacencias[n][n];
	unsigned int visitado[n];
	unsigned int i;

	for (i = 0; i < n; i++)
		visitado[i] = 0;
	
	matriz_de_arquivo(n, adjacencias, "instancia1.txt");
	
	imprime_matriz(n, adjacencias);
	
	printf("\nBusca em largura: ");
	busca_em_largura(n, adjacencias, 3);
	
	printf("\nBusca em profundidade: ");
	busca_em_profundidade(n, adjacencias, 3, visitado);
	
	return 0;
}

