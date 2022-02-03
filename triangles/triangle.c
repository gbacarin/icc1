#include<stdio.h>
#include<stdlib.h>

int main() {
	int n, nEspacos, nCaracteres; // eh possivel suprimir nEspacos e nCaracteres por operacoes nos fors, mas fica menos legivel
	char caracter;
	scanf("%d %c", &n, &caracter); // le a entrada padrao
	
	if(n > 25 || n <= 0) { // se a entrada for inválida
		printf("Altura invalida\n");
		exit(1); // exit parando a execucao
	}

	nEspacos = (n) - 1; // o numero de espacos na primeira linha é igual ao numero de linhas -1

	for(int i = 1; i <= n; i++) { // para n linhas
		for(int j = nEspacos; j > 0; j--) { // enquanto j for maior que o numero de espacos
			printf(" "); // imprima espaco
		}
		nEspacos--; // a proxima linha tera menos um espaco em relacao a atual
		nCaracteres = (i * 2) - 1; // o numero de caracteres por linha pode ser encontrado como 2 * o numero da linha - 1
		for(int j = 0; j < nCaracteres; j++) { // imprimindo caracteres nCaracteres vezes
			printf("%c", caracter);
		}
		printf("\n");
	}

	return 0;
}