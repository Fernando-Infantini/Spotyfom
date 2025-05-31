#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "spotyfom.h"
#include "musica.h"

struct desc *CriaLista(){
	struct desc *descritor = (struct desc*)malloc(sizeof(struct desc));
	descritor->tamanho = 0;
	descritor->lista = NULL;
	descritor->fim = NULL;

	return descritor;
};

void Insere_Inicio(struct desc *descritor, struct musica* mus){
	struct nodo *elemento = (struct nodo*)malloc(sizeof(struct nodo));
	elemento->info = (struct musica*)malloc(sizeof(struct musica));

	*elemento->info = *mus;


	if(descritor->tamanho==0){
		descritor->lista = elemento;
		descritor->fim = elemento;
		elemento->prox=NULL;
		elemento->ant = NULL;
	}
	else{
		elemento->prox = descritor->lista;
		elemento->ant = NULL;
		descritor->lista = elemento;
	}
	(descritor->tamanho)++;
};

void Insere_Meio(struct desc *descritor, int posicao, struct musica* mus){
	struct nodo *elemento = (struct nodo*)malloc(sizeof(struct nodo));
	elemento->info = (struct musica*)malloc(sizeof(struct musica));
	struct nodo *aux = descritor->lista;

	*elemento->info = *mus;


	int x=0;

	while(x<posicao-1){
		aux = aux->prox;
		x++;
	}
	elemento->prox=aux->prox;
	elemento->ant = aux->ant;
	aux->prox = elemento;

	(descritor->tamanho)++;

};

void Insere_Fim(struct desc *descritor, struct musica* mus){
    struct nodo *elemento = (struct nodo*)malloc(sizeof(struct nodo));
    elemento->info = (struct musica*)malloc(sizeof(struct musica));
    *elemento->info = *mus;
    elemento->prox = NULL;

    if (descritor->tamanho == 0) {
        elemento->ant = NULL;
        descritor->lista = elemento;
        descritor->fim = elemento;
    } else {
        elemento->ant = descritor->fim;
        descritor->fim->prox = elemento;
        descritor->fim = elemento;
    }

    (descritor->tamanho)++;
};

void Insere(struct desc *descritor, struct musica* mus, int pos){
	if (pos < 0 || pos > descritor->tamanho) {
		printf("\n\nPOSICAO INVALIDA!!!\n\n");
		return;
	}
	if (pos == 0) {
		Insere_Inicio(descritor,mus);
	} else if (pos == descritor->tamanho) {
		Insere_Fim(descritor,mus);
	} else {
		Insere_Meio(descritor, pos, mus);
	}
};

void Remove(struct desc *descritor, int pos){
	struct nodo *aux = descritor->lista;
	struct nodo *ant;

	if(descritor->tamanho < pos || pos < 0){
		printf("\n\nPOSICAO INVALIDA!!!\n\n");
		return;
	}
	else if(pos == 0){
		descritor->lista=aux->prox;
		(descritor->tamanho)--;
	}
	else if(pos>0){
		for(int x=0;x<pos;x++){
			ant=aux;
			aux=aux->prox;
		}
		ant->prox=aux->prox;
		(descritor->tamanho)--;
	}
};

void Consulta_Titulo(struct desc *descritor){
	char temp[256];
	struct nodo *aux= descritor->lista;

	printf("Digite o titulo da musica: ");
	setbuf(stdin, NULL);
	do fgets(temp,255,stdin); while(!strcmp(temp,"\n\0"));
	temp[strcspn(temp, "\n")] = '\0';

	while(aux!=NULL){
		if(strcasecmp(aux->info->titulo,temp)==0){
			imprime_elemento(aux->info);
		}
		aux=aux->prox;
	}
};

void Consulta_Artista(struct desc *descritor){
	char temp[256];
	struct nodo *aux= descritor->lista;

	printf("Digite o artista da musica: ");
	setbuf(stdin, NULL);
	do fgets(temp,255,stdin); while(!strcmp(temp,"\n\0"));
	temp[strcspn(temp, "\n")] = '\0';

	while(aux!=NULL){
		if(strcasecmp(aux->info->artista,temp)==0){
			imprime_elemento(aux->info);
		}
		aux=aux->prox;
	}
};

void Consulta_Letra(struct desc *descritor){
	char temp[256];
	struct nodo *aux= descritor->lista;

	printf("Digite a letra da musica: ");
	setbuf(stdin, NULL);
	do fgets(temp,255,stdin); while(!strcmp(temp,"\n\0"));
	temp[strcspn(temp, "\n")] = '\0';

	while(aux!=NULL){
		if(strcasecmp(aux->info->letra,temp)==0){
			imprime_elemento(aux->info);
		}
		aux=aux->prox;
	}
};

void Consulta_Codigo(struct desc *descritor){
	int temp=0;
	struct nodo *aux= descritor->lista;

	printf("Digite o codigo da musica: ");
	setbuf(stdin, NULL);
	scanf("%i",&temp);

	while(aux!=NULL){
		if(aux->info->codigo==temp){
			imprime_elemento(aux->info);
		}
		aux=aux->prox;
	}
};

void Consulta_Execucoes(struct desc *descritor){
	int temp=0;
	struct nodo *aux= descritor->lista;

	printf("Digite o numero de execucoes da musica: ");
	setbuf(stdin, NULL);
	scanf("%i",&temp);

	while(aux!=NULL){
		if(aux->info->execucoes==temp){
			imprime_elemento(aux->info);
		}
		aux=aux->prox;
	}
};

void Imprime_Lista(struct desc *descritor){
	struct nodo *aux = descritor->lista;
	while(aux != NULL){
		imprime_elemento(aux->info);
		aux = aux->prox;
	}
};

void Imprime_Posicao(struct desc *descritor){
	int pos=0, x=0;
	struct nodo *aux = descritor->lista;

	printf("\nDigite posicao: ");
	scanf("%i",&pos);

	if(pos >=descritor->tamanho) return;

	while(pos > x){
		aux=aux->prox;
		x++;
	}
	imprime_elemento(aux->info);
}
