/*=== TRABALHO 2 - ADMIRAVEL MUNDO CAOTICO ===
no trabalho, são feitas verificações de posições em torno de cada célula. vou me referir a cada posição
conforme o número dela a seguir

regra de Moore
1 2 3
4 x 6
7 8 9

regra de von Neumann
    1
    2
3 4 x 6 7
    8
    9
*/

#include<stdio.h>
#include<stdlib.h>

void imprimirMatriz(int linhas, int colunas, char **matrizBase) {
	for(int i = 0; i < linhas; i++) {
		for(int j = 0; j < colunas; j++) {
			printf("%c", matrizBase[i][j]);
		}
		printf("\n");
	}
}

void copiarMatriz(int linhas, int colunas, char **matrizCopiar, char **matrizCopiada) {
	for (int i = 0; i < linhas; i++) {
		for(int j = 0; j < colunas; j++) {
			matrizCopiar[i][j] = matrizCopiada[i][j];
		}
	}
}

void limparMatriz(int linhas, char **matriz) {
	for(int i = linhas - 1; i >= 0; i--) {
		free(matriz[i]);
	}
	free(matriz);
}

void sair() {
	printf("Dados de entrada apresentam erro.\n");
	exit(1);
}

char **aplicarMoore(int linhas, int colunas, char **matrizBase);
char **aplicarNeumann(int linhas, int colunas, char **matrizBase);

int main() {
	int linhas, colunas, geracoes;
	char tipoVizinhanca;

	scanf("%d %d", &linhas, &colunas);
	if(linhas <= 0 || colunas <= 0)
		sair();

	scanf("%d", &geracoes);
	if(geracoes <= 0)
		sair();

	scanf("%*[\r\n ]s");
	scanf("%c", &tipoVizinhanca);
	if(tipoVizinhanca != 'M' && tipoVizinhanca != 'N')
		sair();

	// alocar a matriz dinamicamente
	char **matrizBase = malloc(linhas * sizeof(void *));
	for(int i = 0; i < linhas; i++) {
		matrizBase[i] = malloc(colunas * sizeof(char));
	}

	// ler a matriz
	for(int i = 0; i < linhas; i++) {
		for(int j = 0; j < colunas; j++) {
			scanf(" %c", &matrizBase[i][j]);
		}
	}

	for(int i = 0; i < geracoes; i++) {
		if(tipoVizinhanca == 'M') {
			//aplicar regra de Moore
			matrizBase = aplicarMoore(linhas, colunas, matrizBase);
		}
		else {
			//aplicar regra de von Neumann
			matrizBase = aplicarNeumann(linhas, colunas, matrizBase);
		}
	}
	// imprime resultado final
	imprimirMatriz(linhas, colunas, matrizBase);
	limparMatriz(linhas, matrizBase);

	return 0;
}


char **aplicarMoore(int linhas, int colunas, char **matrizBase) {
	int qtdVizinhos;
	//cria uma matriz onde as mudanças acontecem
	char **matrizCopia = malloc(linhas * sizeof(void *));
	for(int i = 0; i < linhas; i++) {
		matrizCopia[i] = malloc(colunas * sizeof(char));
	}
	// deixa a matriz copia igual a matriz base
	copiarMatriz(linhas, colunas, matrizCopia, matrizBase);
	//percorrendo a matriz base e aplicando as mudanças na matriz cópia
	for(int i = 0; i < linhas; i++) {
		for(int j = 0; j < colunas; j++) {
			qtdVizinhos = 0;
			int m, n; // vão receber as coordenadas de cada posição em módulo
			// verifica posição 1
			m = (i - 1 + linhas) % linhas; n = (j - 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 2
			m = (i - 1 + linhas) % linhas; n = (j + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 3
			m = (i - 1 + linhas) % linhas; n = (j + 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 4
			m = (i + linhas) % linhas; n = (j - 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 6
			m = (i + linhas) % linhas; n = (j + 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 7
			m = (i + 1 + linhas) % linhas; n = (j - 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 8
			m = (i + 1 + linhas) % linhas; n = (j + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 9
			m = (i + 1 + linhas) % linhas; n = (j + 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;

			if(qtdVizinhos < 2) { // morre de solidão
				matrizCopia[i][j] = '.';
			}
			if(qtdVizinhos > 3) { // morre de superpopulação
				matrizCopia[i][j] = '.';
			}
			if(qtdVizinhos == 3) { // célula nasce
				matrizCopia[i][j] = 'x';
			}
		}
	}
	return matrizCopia;
}

char **aplicarNeumann(int linhas, int colunas, char **matrizBase) {
	int qtdVizinhos;
	//cria uma matriz onde as mudanças acontecem
	char **matrizCopia = malloc(linhas * sizeof(void *));
	for(int i = 0; i < linhas; i++) {
		matrizCopia[i] = malloc(colunas * sizeof(char));
	}
	// deixa a matriz copia igual a matriz base
	copiarMatriz(linhas, colunas, matrizCopia, matrizBase);
	//percorrendo a matriz base e aplicando as mudanças na matriz cópia
	for(int i = 0; i < linhas; i++) {
		for(int j = 0; j < colunas; j++) {
			qtdVizinhos = 0;
			int m, n; // vão receber as coordenadas de cada posição em módulo
			// verifica posição 1
			m = (i - 2 + linhas) % linhas; n = (j + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 2
			m = (i - 1 + linhas) % linhas; n = (j + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 3
			m = (i + linhas) % linhas; n = (j - 2 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 4
			m = (i + linhas) % linhas; n = (j - 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 6
			m = (i + linhas) % linhas; n = (j + 1 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 7
			m = (i + linhas) % linhas; n = (j + 2 + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 8
			m = (i + 1 + linhas) % linhas; n = (j + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;
			// verifica posição 9
			m = (i + 2 + linhas) % linhas; n = (j + colunas) % colunas;
			if(matrizBase[m][n] == 'x')
				qtdVizinhos++;

			if(qtdVizinhos < 2) { // morre de solidão
				matrizCopia[i][j] = '.';
			}
			if(qtdVizinhos > 3) { // morre de superpopulação
				matrizCopia[i][j] = '.';
			}
			if(qtdVizinhos == 3) { // célula nasce
				matrizCopia[i][j] = 'x';
			}
		}
	}
	return matrizCopia;
}