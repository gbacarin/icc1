#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct musica {
	char *nome;
	char *artista;
	short unsigned int duracao;
} musica;

typedef struct playlist {
	char *nomePlaylist;
	short int qtdMusicas;
	musica *musicasPlaylist;
} playlist;

musica adicionarMusica();
void imprimirPlaylist(playlist lst, int musicaAtual);
void freeStuff(playlist *plst);
char *readLine();

int main() {
	int op, musicaAtual = 0;
	playlist myPlaylist; // cria a nova playlist e inicializa ela
	myPlaylist.nomePlaylist = readLine();
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
			printf("Musica %s de %s adicionada com sucesso.\n", myPlaylist.musicasPlaylist[nMus].nome,
																myPlaylist.musicasPlaylist[nMus].artista);
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
	} while(op != 5);

	//free(myPlaylist.musicasPlaylist);
	//free(myPlaylist.nomePlaylist);
	freeStuff(&myPlaylist);

	return 0;
}

musica adicionarMusica() { // cria nova musica e preenche ela com dados de entrada
	musica novaMusica;
	scanf("%*[\r\n]s");
	novaMusica.nome = readLine();
	novaMusica.artista = readLine();
	scanf("%hd", &novaMusica.duracao);
	
	return novaMusica;
}

void imprimirPlaylist(playlist lst, int musicaAtual) { // imprime a playlist conforme especificado
	printf("---- Playlist: %s ----\n", lst.nomePlaylist);
	printf("Total de musicas: %d\n", lst.qtdMusicas);
	printf("\n");

	for(int i = 0; i < lst.qtdMusicas; i++) {
		if(i == musicaAtual)
			printf("=== NOW PLAYING ===\n");
		printf("(%d). '%s'\n", i+1, lst.musicasPlaylist[i].nome);
		printf("Artista: %s\n", lst.musicasPlaylist[i].artista);
		printf("Duracao: %hd segundos\n", lst.musicasPlaylist[i].duracao);
		printf("\n");
	}
}

void freeStuff(playlist *plst) {
	int qtdMusicas = plst->qtdMusicas;
	for(int i = 0; i < qtdMusicas; i++) {
		free(plst->musicasPlaylist[i].nome);
		free(plst->musicasPlaylist[i].artista);
		//free(plst->musicasPlaylist[i].duracao);
	}
	free(plst->musicasPlaylist);
	free(plst->nomePlaylist);
}

char *readLine() {
	char entrada;
	int tamanho = 0;
	char *texto = malloc(0 * sizeof(char));
	do {
		scanf("%c", &entrada);
		tamanho = tamanho + 1;
		texto = realloc(texto, tamanho * sizeof(char)); // vai aumentar o tamanho da alocação em 1
		if(texto != NULL) { // caso a alocação tenha sido bem sucedida
			if(entrada == '\n')
				texto[tamanho - 1] = '\0';
			else
				texto[tamanho - 1] = entrada;
		}
		else {
			printf("Task failed successfully!\n");
			exit(1);
		}
	} while(entrada != '\n');

	return texto;
}