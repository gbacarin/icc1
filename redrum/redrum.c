/*Bloco 3 - REDRUM
Aluno: Gabriel Bacarin N 10873351*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char *readLine(int *tamanho) {
	char entrada;
	*tamanho = 0;
	char *texto = malloc(0 * sizeof(char));
	do {
		entrada = fgetc(stdin);

		*tamanho = *tamanho + 1;
		texto = realloc(texto, *tamanho * sizeof(char)); // vai aumentar o tamanho da alocação em 1
		if(texto != NULL) { // caso a alocação tenha sido bem sucedida
			if(entrada == '\n') {
				if(texto[*tamanho - 2] == '.') { //verifica se o ponto está no fim da frase, e, se estiver, desconsidera ele
					texto[*tamanho - 2] = '\0';
					*tamanho = *tamanho - 1;
					texto = realloc(texto, *tamanho * sizeof(char));
				} 
				else {
					texto[*tamanho - 1] = '\0';
				}				
			}
			else
				texto[*tamanho - 1] = entrada;
		}
		else { //realloc não funcionou
			printf("Task failed successfully!\n");
			free(texto);
			exit(1);
		}
	} while(entrada != '\n');

	return texto;
}

char *limparAlfabeto(char *fraseOriginal, int *tamanhoFraseSemEspecial) {
	int i, tamanhoOriginal = *tamanhoFraseSemEspecial;
	*tamanhoFraseSemEspecial = 0;
	char *fraseAlterada = malloc(0 * sizeof(char));

	for(i = 0; i < tamanhoOriginal; i++) {
		if((fraseOriginal[i] >= 97 && fraseOriginal[i] <= 122) || (fraseOriginal[i] >= 48 && fraseOriginal[i] <= 57) || fraseOriginal[i] == '\0') {
			//letras														números											fim de string
			*tamanhoFraseSemEspecial = *tamanhoFraseSemEspecial + 1;
			fraseAlterada = realloc(fraseAlterada, *tamanhoFraseSemEspecial * sizeof(char));
			if(fraseAlterada == NULL) {
				printf("Task failed successfully!\n");
				exit(1);
			}
			fraseAlterada[*tamanhoFraseSemEspecial - 1] = fraseOriginal[i];
		}
	}
	return fraseAlterada;
}

int verificarPalindromo(char caracteres[], int inicio, int fim) {
	// se inicio = fim, os caracteres são palíndromos, menor caso
	if(inicio == fim) {
		return 1;
	}

	if(caracteres[inicio] != caracteres[fim]) { // se os caracteres em certa hora são diferentes, eles não são palíndromos
		return 0;
	}

	if(inicio < fim + 1) { // checa se a string fora os caracteres do incio e do fim são palíndromos
		return verificarPalindromo(caracteres, inicio + 1, fim - 1);
	}

	return 1;
}

int main() {
	int tamanhoFraseOriginal = 0;
	char *fraseOriginal = readLine(&tamanhoFraseOriginal); 
	//tamanho frase original volta incluindo o \0
	for(int i = 0; i < tamanhoFraseOriginal - 1; i++) {
		fraseOriginal[i] = tolower(fraseOriginal[i]);
	}
	int tamanhoFraseSemEspecial = tamanhoFraseOriginal;
	char *fraseSemEspecial = limparAlfabeto(fraseOriginal, &tamanhoFraseSemEspecial);
	tamanhoFraseOriginal--;
	tamanhoFraseSemEspecial--;

	int palindromoIndireto = 0, palindromoDireto = 0;
	//executar função recursiva para ver se é palindromo na frase sem caracteres especiais
	palindromoIndireto = verificarPalindromo(fraseSemEspecial, 0, tamanhoFraseSemEspecial - 1);
	//executar para ver se com os caracteres especiais a frase também é palíndroma
	palindromoDireto = verificarPalindromo(fraseOriginal, 0, tamanhoFraseOriginal - 1);

	if(palindromoIndireto == 0) {
		printf("Nao eh um palindromo\n");
	}
	else if(palindromoIndireto == 1 && palindromoDireto == 0) {
		printf("Palindromo indireto\n");
	}
	else if(palindromoIndireto == 1 && palindromoDireto == 1) {
		printf("Palindromo direto\n");
	}

	free(fraseOriginal);
	free(fraseSemEspecial);

	return 0;
}