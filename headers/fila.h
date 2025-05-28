#include "spotyfom.h"
#include "musica.h"

struct nodo_queue{
	struct nodo_queue *prox;
	struct musica *info;
};

struct desc_queue{
	struct nodo_queue *head;
	struct nodo_queue *tail;
	int tamanho;
};

struct desc_queue* CriaQueue();
void ENQUEUE(struct desc_queue *descritor); //insere
struct nodo_queue* DEQUEUE(struct desc_queue *descritor); //remove 1
void queue_EMPTY(struct desc_queue *descritor);
void ShowQueue(struct desc_queue *descritor);
int lenght(struct desc_queue * descritor);
