#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"
#include "spotyfom.h"
#include "musica.h"

struct desc_pilha* CriaPilha(){
	struct desc_pilha *descritor = (struct desc_pilha*)malloc(sizeof(struct desc_pilha));
	descritor->topo = NULL;
	descritor->tamanho = 0;
	return descritor;
}

void PUSH(struct desc_pilha *descritor, struct musica *mus){
	struct nodo_pilha *elemento = (struct nodo_pilha*)malloc(sizeof(struct nodo_pilha));
	elemento->info = mus;
	elemento->prox = NULL;

	elemento->prox = descritor->topo;
	descritor->topo = elemento;

	(descritor->tamanho)++;

}

struct nodo_pilha* POP(struct desc_pilha *descritor){
	struct nodo_pilha *aux = descritor->topo;

	if(descritor->tamanho == 0){
		printf("\nPilha vazia!!!\n");
		return NULL;
	}

	descritor->topo = descritor->topo->prox;
	(descritor->tamanho)--;
	return aux;
}

struct nodo_pilha* TOP(struct desc_pilha *descritor){

	if(descritor->tamanho == 0){
		printf("\nPilha vazia!!!\n");
		return NULL;
	}

	return descritor->topo;
}

void EMPTY(struct desc_pilha *descritor){

	if(descritor->tamanho == 0){
		printf("\nPilha vazia!!!\n");
		return;
	}

	while(descritor->topo != NULL){
		descritor->topo = descritor->topo->prox;
		(descritor->tamanho)--;
	}

	printf("\nPilha esvaziada com sucesso!!!\n");
}

void imprime_pilha(struct desc_pilha *descritor){
	struct nodo_pilha *aux = descritor->topo;
	int x=0;

	if(descritor->tamanho == 0){
		printf("\nPilha vazia!!!\n");
		return;
	}

	while(descritor->tamanho >= 0 && aux!=NULL){
		imprime_elemento(aux->info);
		aux = aux->prox;
		x++;
	}
}

