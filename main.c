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

void busca_em_largura(unsigned int n, unsigned int adjacencias[n][n], unsigned int raiz)
{
	printf("imprime vertices usando busca em largura, a partir do vertice raiz\n");
}

void busca_em_profundidade(unsigned int n, unsigned int adjacencias[n][n], unsigned int raiz)
{
	printf("imprime vertices usando busca em profundidade, a partir do vertice raiz\n");
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

int main()
{
	
	unsigned int n = 5;
	unsigned int adjacencias[n][n];
	
	matriz_de_arquivo(n, adjacencias, "instancia1.txt");
	
	imprime_matriz(n, adjacencias);
	busca_em_largura(n, adjacencias, 3);
	busca_em_profundidade(n, adjacencias, 3);
	
	unsigned int cabeca = 0;
	unsigned int cauda = -1;
	unsigned int fila[n];
	
	// teste da fila
	push(n, &cabeca, &cauda, fila, 7);
	push(n, &cabeca, &cauda, fila, 2);
	push(n, &cabeca, &cauda, fila, 9);
	push(n, &cabeca, &cauda, fila, 8);
	push(n, &cabeca, &cauda, fila, 5);
	push(n, &cabeca, &cauda, fila, 11);
	push(n, &cabeca, &cauda, fila, 22);
	
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	
	push(n, &cabeca, &cauda, fila, 11);
	push(n, &cabeca, &cauda, fila, 22);
	
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
	printf("%d\n", pop(n, &cabeca, &cauda, fila));
		
	return 0;
}

