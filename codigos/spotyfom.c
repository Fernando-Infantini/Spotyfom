#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lista.h"
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
		fscanf(arq, "%[^;];%i;%[^;];%[^;];%[^\n]\n", mus->artista, &mus->codigo, mus->titulo, mus->letra, lixo);  // le os elementos eliminando o campo de execucoes
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
		fprintf(arq, "%s;%d;%s;%s;%i\n", aux->info->artista, aux->info->codigo, aux->info->titulo, aux->info->letra, aux->info->execucoes); //insere informacoes da musica
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

	int y=0;
	fscanf(arq,"%i\n", &y);  //Descobre numero de elementos

	for(int x=0;x<y;x++){
		fscanf(arq, "%[^;];%d;%[^;];%[^;];", mus->artista, &mus->codigo, mus->titulo, mus->letra);  // le os elementos eliminando o campos, incluindo execucoes
		int n = fscanf(arq, "%i\n", &mus->execucoes);

		if(n != 1){
			printf("\nEstrutura do arquivo invalida\n");
			acervo->lista = NULL;
			acervo->tamanho = 0;
			return;
		}

		Insere(acervo, mus, x); // insersao lista simplismente encadeada
	}

	printf("\nArquivo carregado com sucesso!!!\n");

	fclose(arq);
}

void execucao(struct musica *mus){

	// Recebe o ponteiro da struct musica e incrementa sua execucao em 1
	// por ser o endereco muda o valor em todo lugar em que a struct foi passada
	(mus->execucoes++);
}

void cria_playlist_aleatoria(struct desc *acervo, struct desc_queue *aleatoria){
	int num = 0, y=0;
	struct nodo *aux;

	// seta o descritor da fila como null por precaucao
	aleatoria->head = NULL;
	aleatoria->tail = NULL;
	aleatoria->tamanho = 0;

	// gerar uma seed aleatoria baseada no tempo de execucao para escolha aleatória
	srand(time(NULL));

	// recebe do usuario quantas musicas ele deseja na playlist
	printf("\nDigite numero de musicas na playlist: ");
	setbuf(stdin,NULL);
	scanf("%i",&num);
	printf("\n");

	if(num > 0){
		for(int x=0;x<num;x++){
			// gera valor aleatorio para posicao a ser buscada no acervo
			y = (rand() % acervo->tamanho);

			// coloca aux no inicio do acervo
			aux = acervo->lista;

			// busca posicao aleatoria
			while(y>0){
				aux=aux->prox;
				y--;
			}

			// enfilera a musica buscada na playlist
			ENQUEUE(aleatoria,aux->info);
		}

		printf("Playlist aleatoria criada com sucesso!!!\nconteudo:\n\n");

		//apresenta ao usuario a sua plylist
		ShowQueue(aleatoria);

	}
	else printf("\nValor invalido, deve ser maior que 0!!!\n");
}

void executa_aleatoria(struct desc_queue *ale){

	struct nodo_queue *aux;

	// executa playlist ate nao sobrar nada
	while(ale->head != NULL){

		// desenfilera fila e salva conteudo temporariamente em aux para execurar e apresentar ao usuario
		aux = DEQUEUE(ale);
		execucao(aux->info);
		printf("\n");
		imprime_elemento(aux->info);
	}

	printf("\nPlaylist executada com sucesso!!!\n");

	// a operacao anterior ja deixa a cabeca e cauda em NULL e tamanho em 0
	// feito por precaucao
	ale->head = NULL;
	ale->tail = NULL;
	ale->tamanho = 0;
}

void cria_playlist_usuario(struct desc *acervo, struct desc_pilha *user){

	// criacao das variaveis da funcao
	user->topo = NULL;
	user->tamanho = 0;
	int x = 0, y = 0;
	char temp[255];
	struct nodo *aux;

	// menu para escolher forma de insercao
	printf("\n\n==========BUSCA==========\n1.Nome\n2.Codigo\n Digite opcao: ");
	setbuf(stdin,NULL);
	scanf("%i",&x);

	switch(x){
		case 1:
			while(x != 0){

				// recebe nome da musica a ser buscada
				printf("\nDigite nome da musica: ");
				setbuf(stdin,NULL);
				scanf("%[^\n]s",temp);
				temp[strcspn(temp, "\n")] = '\0';

				// seta variaveis a serem utilizadas para o valor desejado
				y = 0;
				aux = acervo->lista;

				while(y == 0 && aux !=NULL){

					// Busca a musica desejada no acervo e empilha na playlist
					if(strcasecmp(temp,aux->info->titulo) == 0){
						y = 1;
						PUSH(user, aux->info);

						printf("\nMusica adicionada com sucesso!!!\n");

					}
					aux = aux->prox;
				}

				// Informa se a musica nao foi encontrada
				if(y = 0) printf("\nEsta musica nao esta no acervo\n");

				// pergunta de o usuario deseja por mais musicas na playlist
				printf("\nDeseja adicionar mais musicas(sim=1 nao=0)? ");
				setbuf(stdin,NULL);
				scanf("%i",&x);
			}

			// apresenta a playlist criada
			if(user->topo != NULL){
				printf("\n\nMusicas da playlist criada: \n\n");
				imprime_pilha(user);
			}

			// informa se nada foi feito
			else printf("\n\nNenhuma musica foi adicionada!!!\n");

			break;
		case 2:
			while(x != 0){

				// o mesmo que foi feito com o nome, mas agora com o codigo da musica
				printf("\nDigite codigo da musica: ");
					setbuf(stdin,NULL);
					scanf("%i",&x);

					y = 0;
					aux = acervo->lista;

					while(y == 0 && aux !=NULL){
						if(x == aux->info->codigo){
							y = 1;
							PUSH(user, aux->info);

							printf("\nMusica adicionada com sucesso!!!\n");
						}
						aux = aux->prox;
					}

					if(y = 0) printf("\nEsta musica nao esta no acervo\n");

					printf("\nDeseja adicionar mais musicas(sim=1 nao=0)? ");
					setbuf(stdin,NULL);
					scanf("%i",&x);
				}

			if(user->topo != NULL){
				printf("\n\nMusicas da playlist criada: \n\n");
				imprime_pilha(user);
			}
			else printf("\n\nNenhuma musica foi adicionada!!!\n");

			break;
		default:
			printf("\n\nOPCAO INVALIDA!!!\n\n");
			return;
			break;
	}
}

void executa_usuario(struct desc_pilha *user){

	struct nodo_pilha *aux;

	// esvazia a playlist com POP salvando temporariamente seu conteudo para executar a musica ate chegar a NULL
	// no final de cada loop mostra na tela a musica tocada
	while(user->topo != NULL){
		aux = POP(user);
		execucao(aux->info);
		printf("\n");
		imprime_elemento(aux->info);
	}

	printf("\nPlaylist executada com sucesso!!!\n");

	user->topo = NULL;
	user->tamanho = 0;

}

void relatorio_acervo(struct desc *acervo, char nome[]){

	FILE *arq = fopen(nome,"w");

	if(arq == NULL){
		printf("\n\nErro ao abrir arquivo!!");
		return;
	}

	struct nodo *aux = acervo->lista; //auxiliar para percorrer acervo

	// Informa quantas musicas existem no acervo
	fprintf(arq,"Tamanho do acervo = %i\n\nMusicas:\n",acervo->tamanho);

	while(aux != NULL){

		// escreve as informacoes da musica no arquivo
		fprintf(arq,"\nTitulo: %s\nArtista: %s\nLetra: %s\nCodigo: %i\nExecucoes: %i\n", aux->info->titulo, aux->info->artista, aux->info->letra, aux->info->codigo, aux->info->execucoes);
		aux = aux->prox;
	}

	printf("\nRelatorio criado com sucesso!!!\n");
}

void relatorio_playlists(struct desc_pilha *user, struct desc_queue *ale, char nome[]){
	FILE *arq = fopen(nome,"w");

	if(arq == NULL){
		printf("\n\nErro ao abrir arquivo!!");
		return;
	}

	//auxiliares para percorrer playlists
	struct nodo_pilha *aux_user = user->topo;
	struct nodo_queue *aux_ale = ale->head;

	if(user->topo != NULL){ //informa a playlist que sera escrita e se existem elementos
		fprintf(arq,"Playlist do usuario:\n");

		while(aux_user != NULL){

			//escreve informacoes das musicas
			fprintf(arq,"\nTitulo: %s\nArtista: %s\nLetra: %s\nCodigo: %i\nExecucoes: %i\n", aux_user->info->titulo, aux_user->info->artista, aux_user->info->letra, aux_user->info->codigo, aux_user->info->execucoes);
			aux_user = aux_user->prox;
		}
	}
	else fprintf(arq,"Playlist do usuario vazia\n\n");


	//mesma logica do bloco anterior
	if(ale->head != NULL){
		fprintf(arq,"\n\nPlaylist aleatoria:\n");

		while(aux_ale != NULL){
			fprintf(arq,"\nTitulo: %s\nArtista: %s\nLetra: %s\nCodigo: %i\nExecucoes: %i\n", aux_ale->info->titulo, aux_ale->info->artista, aux_ale->info->letra, aux_ale->info->codigo, aux_ale->info->execucoes);
			aux_ale = aux_ale->prox;
		}
	}
	else fprintf(arq,"\n\nPlaylist aleatoria vazia\n\n");

	printf("\nRelatorio criado com sucesso!!!\n");

	fclose(arq);
}

int ler_opcao_segura() {
    char buffer[100];
    int valor;

    fgets(buffer, sizeof(buffer), stdin);

    // Tenta converter para int e verifica se deu certo
    if (sscanf(buffer, "%d", &valor) == 1) {
        return valor;
    } else {
        return -1;  // Valor inválido (ex: letra, símbolo, etc.)
    }
}
