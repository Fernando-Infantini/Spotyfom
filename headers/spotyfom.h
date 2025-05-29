#ifndef SPOTYFOM_H
#define SPOTYFOM_H

#include "musica.h"

struct desc;
struct desc_queue;
struct desc_pilha;

struct musica* preenche();
void imprime_elemento(struct musica *musga);
void ler_arquivo(struct desc *descritor_lse, char nome[]);
void backup(struct desc *acervo, char nome[]);
void ler_backup(struct desc *acervo, char nome[]);
void execucao(struct musica *mus);
void cria_playlist_aleatória(struct desc *acervo, struct desc_queue *aleatoria);
void executa_aleatoria(struct desc_queue *ale);

#endif
