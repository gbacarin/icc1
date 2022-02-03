/* Bloco 3 - ASCII Artista
Alunp Gabriel Bacarin N 10873351

o programa tem um quirk que eu não consegui resolver: eu preciso necessariamente colocar o \0 na última posição da matriz
caso contrário, ele imprime um caractere vazio que faz com que a saída fique diferente do runcodes
eu tentei trocar esse caractere por \0 mas não funcionou. o jeito que eu contornei isso pra não bugar a função de enquadrar arte
foi não adicionar esse último \n no arquivo ascii que ele gera
*/

#include<stdio.h>
#include<stdlib.h>

char *readLine(int *tamanho) { // função para ler uma string do stdin
	char entrada;
	*tamanho = 0;
	char *texto = malloc(0 * sizeof(char));
	do {
		entrada = fgetc(stdin);

		*tamanho = *tamanho + 1;
		texto = realloc(texto, *tamanho * sizeof(char)); // vai aumentar o tamanho da alocação em 1
		if(texto != NULL) { // caso a alocação tenha sido bem sucedida
			if(entrada == '\n') {
				texto[*tamanho - 1] = '\0';				
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

char **lerImagem(FILE *arquivo, int *nLinhas, int *nColunas) { // a partir do arquivo, aloca e preenche uma matriz com os caracteres lidos
	int i = 0, j = 0;
	char entrada;

	char **matriz = malloc((i + 1) * sizeof(void *));
	matriz[i] = malloc((j + 1) * sizeof(char));

	do {
		entrada = fgetc(arquivo);
		if(entrada == '\n') { //nova linha da matriz
			matriz[i][j] = entrada;
			i++;
			j = 0;
			matriz = realloc(matriz, (i + 1) * sizeof(void *));
			matriz[i] = realloc(matriz[i], (j + 1) * sizeof(char));
		}
		else if(entrada == EOF) { //fim da matriz
			matriz[i][j] = '\n';
			//matriz[i] = realloc(matriz[i], (j - 1) * sizeof(char));
		}
		else { //entrada é um caractere qualquer
			matriz[i][j] = entrada;
			j++;
			matriz[i] = realloc(matriz[i], (j + 1) * sizeof(char));
		}

	} while(entrada != EOF);

	*nLinhas = i + 1;
	*nColunas = j + 1;

	return matriz;
}

void imprimirMatriz(char **matriz, int nLinhas, int nColunas) { // imprime a matriz tendo suas informações como parâmentros
	for(int i = 0; i < nLinhas; i++) {
		for(int j = 0; j < nColunas; j++) {
			printf("%c", matriz[i][j]);
		}
	}
}

char **aplicarPaintBucket(char **matriz, int nLinhas, int nColunas, int posX, int posY, char cor, char corDeFundo) {
	//função recursiva que sai verificando a vizinhança de cada ponto, e se for um ponto que precisa ser preenchido, faz a recursão para
	//preencher esse ponto
	if(matriz[posX][posY] == corDeFundo) { //ponto está com a cor de fundo e deve ser preenchido com a nova cor
		matriz[posX][posY] = cor;

		//verifica a posição acima do ponto atual
		if((posX - 1) != -1 && matriz[posX - 1][posY] == corDeFundo) {
			matriz = aplicarPaintBucket(matriz, nLinhas, nColunas, (posX - 1), posY, cor, corDeFundo);
		}
		//verifica a posição à esquerda do ponto atual
		if((posY - 1) != -1 && matriz[posX][posY - 1] == corDeFundo) {
			matriz = aplicarPaintBucket(matriz, nLinhas, nColunas, posX, (posY - 1), cor, corDeFundo);
		}
		//verifica a posição abaixo do ponto atual
		if((posX + 1) != (nLinhas) && matriz[posX + 1][posY] == corDeFundo) {
			matriz = aplicarPaintBucket(matriz, nLinhas, nColunas, (posX + 1), posY, cor, corDeFundo);
		}
		//verifica a posição à direita do ponto atual
		if((posY + 1) != nColunas && matriz[posX][posY + 1] == corDeFundo) {
			matriz = aplicarPaintBucket(matriz, nLinhas, nColunas, posX, (posY + 1), cor, corDeFundo);
		}
		return matriz;
	}
	else {
		return matriz;
	}
}

void escreverImagem(FILE *arquivoNovo, char **matriz, int nLinhas, int nColunas) { // escreve no arquivo os conteudos da matriz char por char
	int i, j;
	for(i = 0; i < nLinhas; i++) {
		for(j = 0; j < nColunas; j++) {
			if((i == (nLinhas - 1)) && (j == (nColunas - 1))) { // caso seja o último caractere da matriz, o \n, retorna sem colocar ele
				return;
			}
			else {
				fprintf(arquivoNovo, "%c", matriz[i][j]);
			}			
		}
	}
}

void enquadra_arte(char *nome_do_arquivo_da_arte, int  altura_do_quadro, int  largura_do_quadro);

int main() { //abre o arquivo de onde a imagem vai ser lida, recebe as instruções de pintura, chama a função de pintura e escreve o novo arquivo
	int tamanhoNomeArte = 0, nLinhas = 0, nColunas = 0, nInstrucoes;
	char *nomeArte = readLine(&tamanhoNomeArte);

	FILE *arquivoOriginal = fopen(nomeArte, "r");
	if(!arquivoOriginal) {
		printf("Erro ao abrir arquivo\n");
		exit(1);
	}	
	//cria uma matriz e chama a função que a preenche
	char **matriz = lerImagem(arquivoOriginal, &nLinhas, &nColunas);
	//fecha o arquivo aberto
	fclose(arquivoOriginal);

	//se prepara para receber as instruções de colorir
	scanf("%d", &nInstrucoes);
	scanf("%*[\r\n]s");

	printf("Arte inicial:\n");
	imprimirMatriz(matriz, nLinhas, nColunas);

	char cor, corDeFundo;
	int posX, posY;

	for(int i = 0; i < nInstrucoes; i++) {
		//recebe as instruções
		scanf("%c %d %d", &cor, &posX, &posY);
		scanf("%*[\r\n]s");
		corDeFundo = matriz[posX][posY];
		printf("\n");
		printf("Arte apos a etapa %d:\n", i);
		matriz = aplicarPaintBucket(matriz, nLinhas, nColunas, posX, posY, cor, corDeFundo);
		imprimirMatriz(matriz, nLinhas, nColunas);
	}

	//salvar arquivo com a arte
	FILE *arquivoNovo = fopen(nomeArte, "w");
	escreverImagem(arquivoNovo, matriz, nLinhas, nColunas);
	fclose(arquivoNovo);
	printf("\n");
	printf("Arte enquadrada:\n");
	enquadra_arte(nomeArte, (nLinhas), (nColunas - 1));


	//desaloca o nome e a matriz
	free(nomeArte);
	for(int j = 0; j < nLinhas; j++) {
		free(matriz[j]);
	}
	free(matriz);

	return 0;
}


void enquadra_arte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro
) {
	FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}