#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lse.h"
#include "fila.h"
#include "pilha.h"
#include "spotyfom.h"
#include "musica.h"

struct musica* preenche(){

	struct musica *musga = (struct musica*)malloc(sizeof(struct musica));

	printf("Digite nome da musica: ");
	setbuf(stdin, NULL);
	do fgets(musga->titulo,255,stdin); while(!strcmp(musga->titulo,"\n\0"));

	printf("Digite nome do artista: ");
	setbuf(stdin, NULL);
	do fgets(musga->artista,255,stdin); while(!strcmp(musga->artista,"\n\0"));

	printf("Digite letra da musica: ");
	do fgets(musga->letra,255,stdin); while(!strcmp(musga->letra,"\n\0"));

	printf("Digite o codigo da musica: ");
	setbuf(stdin, NULL);
	scanf("%i",&musga->codigo);

	printf("Digite o numero de execucoes da musica: ");
	setbuf(stdin, NULL);
	scanf("%i",&musga->execucoes);
	printf("\n\n");
	return musga;
}

void imprime_elemento(struct musica *musga){
	printf("Nome: %s\n",musga->titulo);
	printf("Artista: %s\n",musga->artista);
	printf("Letra: %s\n",musga->letra);
	printf("Codigo: %i\n",musga->codigo);
	printf("Execucoes: %i\n\n",musga->execucoes);
};

void ler_arquivo(struct desc *descritor_lse){

	FILE *arq = fopen("musicas.txt","r");

	struct musica* mus = (struct musica*)malloc(sizeof(struct musica));
	char lixo[256];


	int n = 0;

	fscanf(arq,"%i\n", &n);

	for(int x=0;x<n;x++){
		fscanf(arq, "%[^;];%d;%[^;];%[^;];%s\n", mus->artista, &mus->codigo, mus->titulo, mus->letra, lixo);
		Insere(descritor_lse, mus, x);
	}

	fclose(arq);
}

































