#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "spotyfom.h"
#include "musica.h"

struct desc_queue* CriaQueue(){
	struct desc_queue *descritor = (struct desc_queue*)malloc(sizeof(struct desc_queue));
	descritor->head = NULL;
	descritor->tail = NULL;
	descritor->tamanho = 0;
	return descritor;
}

void ENQUEUE(struct desc_queue *descritor){
	struct nodo_queue *elemento = (struct nodo_queue*)malloc(sizeof(struct nodo_queue));
	elemento->info = preenche();

	if(descritor->tamanho == 0){
		elemento->prox = NULL;
		descritor->tail = elemento;
		descritor->head = elemento;
	}

	else{
		elemento->prox = NULL;
		descritor->tail->prox = elemento;
		descritor->tail = elemento;
	}
	(descritor->tamanho)++;

}

struct nodo_queue* DEQUEUE(struct desc_queue *descritor){
	struct nodo_queue *aux = descritor->head;

	if(descritor->tamanho == 0){
		printf("\nFila vazia!!!\n");
		return NULL;
	}

	descritor->head = descritor->head->prox;
	(descritor->tamanho)--;
	return aux;
}

void queue_EMPTY(struct desc_queue *descritor){

	if(descritor->tamanho == 0){
		printf("\nFila vazia!!!\n");
		return;
	}

	while(descritor->head != NULL){
		descritor->head = descritor->head->prox;
		(descritor->tamanho)--;
	}
	descritor->tail = NULL;

	printf("\nFila esvaziada com sucesso!!!\n");
}

void ShowQueue(struct desc_queue *descritor){
	struct nodo_queue *aux = descritor->head;
	int x=0;

	if(descritor->tamanho == 0){
		printf("\nFila vazia!!!\n");
		return;
	}

	while(descritor->tamanho >= 0 && aux!=NULL){
		imprime_elemento(aux->info);
		aux = aux->prox;
		x++;
	}
}

int lenght(struct desc_queue * descritor){
	return descritor->tamanho;
}
