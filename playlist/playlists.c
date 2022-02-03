/*Bloco 3 - exercício 1 - Sistema de gerenciamento de Playlists
Aluno: G. Bacarin, n 10873351

a intenção do programa é gerenciar playlists usando arquivos para salva-las de forma persistente.

a música sendo atualmente tocada é controlada por índice
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct musica {
	int tamanhoNome;
	char *nome;
	int tamanhoArtista;
	char *artista;
	int duracao;
} musica;

typedef struct playlist {
	int tamanhoNomePlaylist;
	char *nomePlaylist;
	int qtdMusicas;
	musica *musicasPlaylist;
} playlist;


musica adicionarMusica();
void imprimirPlaylist(playlist lst, int musicaAtual);
void escreverPlaylist(playlist lst);
playlist lerPlaylist();
char *readLine();
void binaryToNum(char *binFilename);

int main() {
	int op, musicaAtual = 0;
	playlist myPlaylist; // cria a nova playlist e inicializa ela
	myPlaylist.tamanhoNomePlaylist = 0;
	myPlaylist.nomePlaylist = readLine(&myPlaylist.tamanhoNomePlaylist);
	myPlaylist.qtdMusicas = 0;
	myPlaylist.musicasPlaylist = calloc(0, sizeof(musica));

	do {
		scanf("%d", &op);

		if(op == 1) { // adicionar nova música ao fim da playlist
			if(myPlaylist.qtdMusicas == 15) {
				printf("Playlist cheia!\n");
				continue;
			}
			int nMus = myPlaylist.qtdMusicas;
			myPlaylist.musicasPlaylist = realloc(myPlaylist.musicasPlaylist, (nMus+1) * sizeof(musica));
			myPlaylist.musicasPlaylist[nMus] = adicionarMusica();
			printf("Musica %.*s de %.*s adicionada com sucesso.\n", myPlaylist.musicasPlaylist[nMus].tamanhoNome, myPlaylist.musicasPlaylist[nMus].nome,
																myPlaylist.musicasPlaylist[nMus].tamanhoArtista, myPlaylist.musicasPlaylist[nMus].artista);
			myPlaylist.qtdMusicas = myPlaylist.qtdMusicas + 1;
		}
		if(op == 2) { // mostrar todas as músicas da playlist
			imprimirPlaylist(myPlaylist, musicaAtual);
		}
		if(op == 3) { // ir para a próxima musica
			if(musicaAtual < myPlaylist.qtdMusicas) {
				musicaAtual++;
			}
		}
		if(op == 4) { // voltar para a música anterior
			if(musicaAtual != 0) {
				musicaAtual--;
			}
		}
		if(op == 5) { // salvar playlist atual em arquivo
			escreverPlaylist(myPlaylist);
		}
		if(op == 6) { // abrir uma playlist a partir de um arquivo
			myPlaylist = lerPlaylist();
			musicaAtual = 0;			
		}

	} while(op != 7);

	//desaloca tudo que foi usado na heap na main
	for(int i = 0; i < myPlaylist.qtdMusicas; i++) {
		free(myPlaylist.musicasPlaylist[i].nome);
		free(myPlaylist.musicasPlaylist[i].artista);
	}
	free(myPlaylist.musicasPlaylist);
	free(myPlaylist.nomePlaylist);

	return 0;
}

musica adicionarMusica() { // cria nova musica e preenche ela com dados de entrada
	musica novaMusica;
	scanf("%*[\r\n]s");
	novaMusica.nome = readLine(&novaMusica.tamanhoNome);
	novaMusica.artista = readLine(&novaMusica.tamanhoArtista);
	scanf("%d", &novaMusica.duracao);
	
	return novaMusica;
}

void imprimirPlaylist(playlist lst, int musicaAtual) { // imprime a playlist conforme especificado
	printf("---- Playlist: %.*s ----\n", lst.tamanhoNomePlaylist, lst.nomePlaylist);
	printf("Total de musicas: %d\n", lst.qtdMusicas);
	printf("\n");

	for(int i = 0; i < lst.qtdMusicas; i++) {
		if(i == musicaAtual)
			printf("=== NOW PLAYING ===\n");
		printf("(%d). '%.*s'\n", i+1, lst.musicasPlaylist[i].tamanhoNome, lst.musicasPlaylist[i].nome);
		printf("Artista: %.*s\n", lst.musicasPlaylist[i].tamanhoArtista, lst.musicasPlaylist[i].artista);
		printf("Duracao: %d segundos\n", lst.musicasPlaylist[i].duracao);
		printf("\n");
	}
}

void escreverPlaylist(playlist lst) { // grava a playlist atual em um arquivo binário
	int tamanhoNomeArquivo = 0;
	scanf("%*[\r\n]s");
	char *nomeArquivo = readLine(&tamanhoNomeArquivo);
	FILE *arquivoPlaylist = fopen(nomeArquivo, "wb");

	fwrite((&lst.tamanhoNomePlaylist), sizeof(int), 1, arquivoPlaylist);
	fwrite(lst.nomePlaylist, sizeof(char), lst.tamanhoNomePlaylist, arquivoPlaylist);
	fwrite(&lst.qtdMusicas, sizeof(int), 1, arquivoPlaylist);
	for(int i = 0; i < lst.qtdMusicas; i++) {
		fwrite((&lst.musicasPlaylist[i].tamanhoNome), sizeof(int), 1, arquivoPlaylist);
		fwrite(lst.musicasPlaylist[i].nome, sizeof(char), lst.musicasPlaylist[i].tamanhoNome, arquivoPlaylist);
		fwrite((&lst.musicasPlaylist[i].tamanhoArtista), sizeof(int), 1, arquivoPlaylist);
		fwrite(lst.musicasPlaylist[i].artista, sizeof(char), lst.musicasPlaylist[i].tamanhoArtista, arquivoPlaylist);
		fwrite(&lst.musicasPlaylist[i].duracao, sizeof(int), 1, arquivoPlaylist);
	}
	printf("Playlist %.*s salva com sucesso.\n", tamanhoNomeArquivo, nomeArquivo);
	fclose(arquivoPlaylist);	
	binaryToNum(nomeArquivo);
	free(nomeArquivo);
}

playlist lerPlaylist() { // carrega em uma nova playlist a partir de um arquivo
	int tamanhoNomeArquivo = 0;
	scanf("%*[\r\n]s");
	char *nomeArquivo = readLine(&tamanhoNomeArquivo);
	FILE *arquivoPlaylist = fopen(nomeArquivo, "rb"); //abre o arquivo para leitura

	if(!arquivoPlaylist) {
		printf("Arquivo %.*s nao existe.\n", tamanhoNomeArquivo, nomeArquivo);
		exit(0);
	}
	playlist lida; //cria a playlist que será retornada

	fread(&lida.tamanhoNomePlaylist, sizeof(int), 1, arquivoPlaylist);
	lida.nomePlaylist = malloc(lida.tamanhoNomePlaylist * sizeof(char));
	fread(lida.nomePlaylist, sizeof(char), lida.tamanhoNomePlaylist, arquivoPlaylist);
	fread(&lida.qtdMusicas, sizeof(int), 1, arquivoPlaylist);

	musica bufferMusica;
	//inicializa o vetor 
	lida.musicasPlaylist = malloc(0 * sizeof(musica));

	for(int i = 0; i < lida.qtdMusicas; i++) { //lê cada música que vai sendo adicionada
		lida.musicasPlaylist = realloc(lida.musicasPlaylist, (i + 1) * sizeof(musica));
		fread(&bufferMusica.tamanhoNome, sizeof(int), 1, arquivoPlaylist);
		bufferMusica.nome = malloc(bufferMusica.tamanhoNome * sizeof(char));
		fread(bufferMusica.nome, sizeof(char), bufferMusica.tamanhoNome, arquivoPlaylist);		
		fread(&bufferMusica.tamanhoArtista, sizeof(int), 1, arquivoPlaylist);
		bufferMusica.artista = malloc(bufferMusica.tamanhoArtista * sizeof(char));
		fread(bufferMusica.artista, sizeof(char), bufferMusica.tamanhoArtista, arquivoPlaylist);
		fread(&bufferMusica.duracao, sizeof(int), 1, arquivoPlaylist);
		
		lida.musicasPlaylist[i] = bufferMusica;
	}
	printf("Playlist %.*s carregada com sucesso.\n", tamanhoNomeArquivo, nomeArquivo);

	fclose(arquivoPlaylist);
	binaryToNum(nomeArquivo);
	return lida;
}

char *readLine(int *tamanho) {
	char entrada;
	*tamanho = 0;
	char *texto = malloc(0 * sizeof(char));
	do {
		scanf("%c", &entrada);
		if(entrada == '\n')
			return texto;
		*tamanho = *tamanho + 1;
		texto = realloc(texto, *tamanho * sizeof(char)); // vai aumentar o tamanho da alocação em 1
		if(texto != NULL) { // caso a alocação tenha sido bem sucedida
			if(entrada == '\n') {
				*tamanho = *tamanho - 1;
			}
			else
				texto[*tamanho - 1] = entrada;
		}
		else {
			printf("Task failed successfully!\n");
			free(texto);
			exit(1);
		}
	} while(entrada != '\n');

	return texto;
}

void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}
