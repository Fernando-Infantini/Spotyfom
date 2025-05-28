#ifndef SPOTYFOM_H
#define SPOTYFOM_H

#include "musica.h"

struct desc;

struct musica* preenche();
void imprime_elemento(struct musica *musga);
void ler_arquivo(struct desc *descritor_lse, char nome[]);
void backup(struct desc *acervo, char nome[]);

#endif
