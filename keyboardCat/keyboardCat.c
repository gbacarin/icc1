#include<stdio.h>

int main() {
	char sequencia[49];
	int entrada[1000];
	int tamanho;

	for(int i = 0; i < 48; i++) {
		scanf("%c ", &sequencia[i]);
	}
	scanf("%c", &sequencia[48]);

	scanf("%i", &tamanho);

	for(int i = 0; i < tamanho - 1; i++) {
		scanf("%i ", &entrada[i]);
	}
	scanf("%i", &entrada[tamanho - 1]);

	for(int i = 0; i < tamanho; i++) {
		if(sequencia[entrada[i]] == 'E')
			printf("\n");
		else if(sequencia[entrada[i]] == '_')
			printf(" ");
		else
			printf("%c", sequencia[entrada[i]]);
	}

	return 0;
}