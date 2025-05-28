#ifndef LSE_H
#define LSE_H

#include "spotyfom.h"
#include "musica.h"

struct nodo{
	struct nodo *prox;
	struct musica *info;
};

struct desc{
	struct nodo *lista;
	int tamanho;
};


struct desc *CriaLista();
void Insere_Inicio(struct desc *descritor, struct musica* mus);
void Insere_Meio(struct desc *descritor, int posicao, struct musica* mus);
void Insere_Fim(struct desc *descritor, struct musica* mus);
void Insere(struct desc *descritor, struct musica* mus, int pos);
void Remove(struct desc *descritor);
void Consulta_Titulo(struct desc *descritor);
void Consulta_Artista(struct desc *descritor);
void Consulta_Letra(struct desc *descritor);
void Consulta_Codigo(struct desc *descritor);
void Consulta_Execucoes(struct desc *descritor);
void Imprime_Lista(struct desc *descritor);
void Imprime_Posicao(struct desc *descritor);

#endif
