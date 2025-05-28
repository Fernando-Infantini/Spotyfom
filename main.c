#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musica.h"
#include "lse.h"
#include "fila.h"
#include "pilha.h"
#include "spotyfom.h"

int main(){

	int op = 1;
	char tempc[256] = {'\0'};

	struct desc* acervo = CriaLista();

	while(op != 0){
		printf("\n\n==========MENU==========\n1.Ler acervo\n2.Playlist\n3.Buscas\n4.Imprimir acervo\n5.Relatorio\n6.Back-up\n7.Ler back-up\n Digite opcao: ");
		setbuf(stdin,NULL);
		scanf("%i",&op);

		switch(op){
			case 1:

				if(acervo->lista == NULL){
					printf("\nDigite nome do arquivo: ");
					setbuf(stdin,NULL);
					scanf("%[^\n]s", tempc);
					ler_arquivo(acervo, tempc);
				}
				else printf("\nAcervo já carregado!");

				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 0:
				printf("\n\nSaindo...");
				break;
			default:
				printf("\n\nOPCAO INVALIDA!!!");
				break;
		}
	}







	return 0;
}

