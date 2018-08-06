#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void armazena_matriz(char* caminho, unsigned int n, unsigned int X[n][n])
{
	int i,j;
	FILE *f = fopen(caminho, "w");
	
	if (f == NULL)
	{
    	printf("Error opening file!\n");
    	exit(1);
	}
		
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			fprintf(f, "%d\t", X[i][j]);
		}
		fprintf(f, "\n");
	}
	
	fclose(f);
	
}

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

int convert_int(char* s)
{
	int resultado = 0;
	int i, len;
	len = strlen(s);

	for(i=0; i < len; i++)
	{
		resultado = resultado * 10 + ( s[i] - '0' );
	}
	
	return resultado;

}

unsigned int sorteia_peso()
{
	// sorteia o peso da aresta entre 1 e 100
	return 1 + (rand() % 100);
}

int main( int argc, char *argv[ ] )
{
	unsigned int i, j, sorteio, peso, soma_linha, vertice_aleatorio;
	// quantidade de vértices
	unsigned int n = convert_int(argv[1]);
	
	// probabilidade de existir uma aresta entre dois vertices quaisquer
	unsigned int probabilidade = convert_int(argv[2]);
	
	unsigned int adjacencias[n][n];
	
	char* caminho = argv[3];
	
	srand(time(0));
	
	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			if (i == j)
			{
				adjacencias[i][j] = 0;
			} else
			{
				// sorteia numero entre 0 e 100
				sorteio = rand() % 100;
				
				// decide se cria ou nao aresta
				if (sorteio <= probabilidade)
				{
					// sorteia o peso da aresta entre 1 e 100
					peso = sorteia_peso();
					
					// preenche adjacencia nos dois lados
					adjacencias[i][j] = peso;
					adjacencias[j][i] = peso;
				}
				else
				{
					// caso não haja aresta coloca 0
					adjacencias[i][j] = 0;
					adjacencias[j][i] = 0;
				}
			}
		}
	}
	
	//verifica se existe vertice sem nenhuma aresta
	for (i = 0; i < n; i++)
	{
		soma_linha = 0;
		for (j = 0; j < n; j++)
		{
			soma_linha += adjacencias[i][j];
		}
		
		// caso nao possua arestas
		if (soma_linha == 0)
		{
			// sorteia um vertice aleatorio, diferente de si proprio
			do
			{
				vertice_aleatorio = rand() % n;
			} while (vertice_aleatorio == i);
			
			peso = sorteia_peso();
			adjacencias[i][vertice_aleatorio] = peso;
			adjacencias[vertice_aleatorio][i] = peso;
		}
	}
	
	imprime_matriz(n, adjacencias);
	armazena_matriz(caminho, n, adjacencias);
	
	return 0;
}
