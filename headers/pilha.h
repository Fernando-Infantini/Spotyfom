#ifndef PILHA_H
#define PILHA_H

#include "spotyfom.h"
#include "musica.h"

struct nodo_pilha{
	struct nodo_pilha *prox;
	struct musica *info;
};

struct desc_pilha{
	struct nodo_pilha *topo;
	int tamanho;
};

struct desc_pilha* CriaPilha();
void PUSH(struct desc_pilha *descritor); //insere
struct nodo_pilha* POP(struct desc_pilha *descritor); //remove 1
struct nodo_pilha* TOP(struct desc_pilha *descritor); //retorna 1
void EMPTY(struct desc_pilha *descritor);
void imprime_pilha(struct desc_pilha *descritor);

#endif
