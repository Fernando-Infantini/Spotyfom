#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lse.h"
#include "fila.h"
#include "pilha.h"
#include "spotyfom.h"
#include "musica.h"

struct musica* preenche(){ // funcao de preencher a struct musica das atividades, nao sera usada mas foi transferida para ca para evitar conflitos

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

void imprime_elemento(struct musica *musga){  //recebe struct musica e imprime seus campos na tela
	printf("Nome: %s\n",musga->titulo);
	printf("Artista: %s\n",musga->artista);
	printf("Letra: %s\n",musga->letra);
	printf("Codigo: %i\n",musga->codigo);
	printf("Execucoes: %i\n\n",musga->execucoes);
};

void ler_arquivo(struct desc *descritor_lse, char nome[]){

	FILE *arq = fopen(nome,"r");

	if(arq==NULL){
		printf("\nErro ao abrir arquivo!!!\n");
		return;
	}

	struct musica* mus = (struct musica*)malloc(sizeof(struct musica));
	char lixo[256];

	int n = 0;

	fscanf(arq,"%i\n", &n);  //Descobre numero de elementos

	for(int x=0;x<n;x++){
		fscanf(arq, "%[^;];%d;%[^;];%[^;];%[^\n]", mus->artista, &mus->codigo, mus->titulo, mus->letra, lixo);  // le os elementos eliminando o campo de execucoes
		Insere(descritor_lse, mus, x); // insersao lista simplismente encadeada
	}

	printf("\nArquivo carregado com sucesso!!!\n");

	fclose(arq);
}

void backup(struct desc *acervo, char nome[]){
	FILE *arq = fopen(nome,"w");

	if(arq==NULL){
		printf("\nErro ao abrir arquivo!!!\n");
		return;
	}

	struct nodo *aux = acervo->lista;

	fprintf(arq,"%i\n", acervo->tamanho); // insere numero de musicas na primeira linha

	for(int x=0;x<acervo->tamanho;x++){
		if(aux == NULL){ // verifica se ocorreu algum erro e aux e nulo
			printf("\nERRO AO SALVAR ACERVO!!!\n\n");
			fclose(arq);
			return;
		}
		fprintf(arq, "%s;%d;%s;%s;%i", aux->info->artista, aux->info->codigo, aux->info->titulo, aux->info->letra, aux->info->execucoes); //insere informacoes da musica
		aux = aux->prox; //busca proxima musica da lista
	}

	printf("\nArquivo salvo com sucesso!!!\n");

	fclose(arq);
}

void ler_backup(struct desc *acervo, char nome[]){

	FILE *arq = fopen(nome,"r");

	if(arq==NULL){
		printf("\nErro ao abrir arquivo!!!\n");
		return;
	}

	struct musica* mus = (struct musica*)malloc(sizeof(struct musica));

	int n = 0;

	fscanf(arq,"%i\n", &n);  //Descobre numero de elementos

	for(int x=0;x<n;x++){
		fscanf(arq, "%[^;];%d;%[^;];%[^;];%i\n", mus->artista, &mus->codigo, mus->titulo, mus->letra, &mus->execucoes);  // le os elementos eliminando o campos, incluindo execucoes
		Insere(acervo, mus, x); // insersao lista simplismente encadeada
	}

	printf("\nArquivo carregado com sucesso!!!\n");

	fclose(arq);
}

void execucao(struct musica *mus){
	(mus->execucoes++);
}



























