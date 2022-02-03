#include<stdio.h>
#include<stdlib.h>

char * read_line(int * tamanho, char * texto) {
	char entrada;

	do {
		scanf("%c", &entrada);
		* tamanho = * tamanho + 1;
		texto = realloc(texto, *tamanho * sizeof(char)); // vai aumentar o tamanho da alocação em 1
		if(texto != NULL) { // caso a alocação tenha sido bem sucedida
			if(entrada == '\n')
				texto[*tamanho - 1] = '\0';
			else
				texto[*tamanho - 1] = entrada;
		}
		else {
			printf("Task failed successfully!\n");
			exit(1);
		}
	} while(entrada != '\n');

	return texto;
}

void imprimirLinha(char * texto, int inicio, int fim) {
	for(int i = inicio; i <= fim; i++) {
		printf("%c", texto[i]);
	}
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);
	scanf("%*[\r\n]s");
	int stops[n]; // posição do fim de cada linha no texto
	int tamanho = 0; // tamanho do texto atual

	char * texto = calloc(0, sizeof(char));

	for(int i = 0; i < n; i++) {
		read_line(&tamanho, texto);
		stops[i] = tamanho - 1;
	}

	int validas;
	scanf("%d", &validas);
	int indice;

	for(int i = 0; i < validas; i++) {
		scanf("%d", &indice);
		if(indice == 0)
			imprimirLinha(texto, 0, stops[indice] - 1); // imprime a linha desde o início até chegar no primeiro \0
		else
			imprimirLinha(texto, stops[indice - 1] + 1, stops[indice] - 1); // imprime a linha a partir do final da anterior
												// esse +1 é para pular o \0 da linha anterior
												// e o -1 é para ignorar o \0 da linha atual
	}
	free(texto);
	return 0;
}