#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musica.h"
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "spotyfom.h"

int main(){

	// cria variaveis que serao utilizadas
	int op = 1;
	char tempc[256] = {'\0'};

	// cria descritores do acervo e playlists
	struct desc* acervo = CriaLista();
	struct desc_queue *playlist_aleatoria = CriaQueue();
	struct desc_pilha *playlist_usuario = CriaPilha();

	while(op != 0){

		// menu informando opcoes ao usuario
		printf("\n\n==========MENU==========\n1.Ler acervo\n2.Playlist\n3.Buscas\n4.Imprimir acervo\n5.Relatorios\n6.Back-up\n7.Ler back-up\n Digite opcao: ");
		setbuf(stdin,NULL);
		op = ler_opcao_segura();

		switch(op){
			case 1:

				// verifica se o acervo já foi carregadp
				if(acervo->lista == NULL){
					printf("\nDigite nome do arquivo: ");
					setbuf(stdin,NULL);
					scanf("%[^\n]s", tempc);
					ler_arquivo(acervo, tempc);
				}

				//verifica se o usuario deseja sobreescrever o arquivo
				else{
					printf("\nAcervo já carregado, deseja sobreescrever acervo?(1=sim 0=nao) ");
					setbuf(stdin,NULL);
					op = ler_opcao_segura();
					if(op==0){
						op = 99;
					}
					else{

						// apaga acervo atual
						while(acervo->tamanho > 0){
							Remove(acervo,0);
						}

						acervo->tamanho=0;
						acervo->fim=NULL;
						acervo->lista=NULL;

						printf("\nAcervo apagado\n");

						// carrega novo acervo
						printf("\nDigite nome do arquivo: ");
						setbuf(stdin,NULL);
						scanf("%[^\n]s", tempc);
						ler_arquivo(acervo, tempc);
					}
				}
				break;
			case 2:

				// verifica se acervo foi carregado
				if(acervo->lista!=NULL){

					// menu com opcoes das playlists
					printf("\n==========PLAYLISTS==========\n*Criar uma playlist ira sobreescrever uma já existente do mesmo tipo se existente*\n\n1.Criar playlist aleatória\n2.Criar playlist por escolhas\n3.Tocar playlist aleatoria\n4.Tocar playlist usuario\n Digite opcao: ");
					setbuf(stdin,NULL);
					op = ler_opcao_segura();
					printf("\n");

					switch(op){
						case 1:
							cria_playlist_aleatoria(acervo,playlist_aleatoria);
							break;
						case 2:
							cria_playlist_usuario(acervo, playlist_usuario);
							break;
						case 3:

							// verifica se existe alguma musica na playlist e executa se afirmativo
							if(playlist_aleatoria->head != NULL){
								executa_aleatoria(playlist_aleatoria);
							}
							else printf("\nPlaylist aleatória vazia");
							break;
						case 4:

							// verifica se existe alguma musica na playlist e executa se aformativo
							if(playlist_usuario != NULL){
								executa_usuario(playlist_usuario);
							}
							else printf("\nPlaylist do usuario vazia!!!");
							break;
						case 0:
							op = 99;
						default:
							printf("\n\nOPCAO INVALIDA!!!");
							op = 99;
							break;
					}
				}
				else printf("\nAcervo vazio, carregue um aqruivo primeiro!!!\n");

				break;
			case 3:

				// verifica se o acervo foi carregado
				if(acervo->lista != NULL){

					// menu das buscas onde as funcoes apenas percorrem a lista em busca dos nomes/valores pedidos dentro delas
					printf("\n\n==========BUSCAS==========\n1.Titulo\n2.Artista\n3.Codigo\n Digite opcao: ");
					setbuf(stdin,NULL);
					op = ler_opcao_segura();
					printf("\n");

					switch(op){
						case 1:
							Consulta_Titulo(acervo);
							break;
						case 2:
							Consulta_Artista(acervo);
							break;
						case 3:
							Consulta_Codigo(acervo);
							break;
						default:
							printf("\n\nOPCAO INVALIDA!!!");
							op = 99;
							break;
					}
				}
				else printf("\n\nAcervo vazio!!!");

				break;
			case 4:

				// imprime todo o acervo se carregado

				if(acervo != NULL) Imprime_Lista(acervo);
				else printf("\nAcervo vazio!!!\n");

				break;
			case 5:

				// Menu dos relatorios
				printf("\n==========RELATORIOS==========\n1.Relatorio acervo\n2.Relatorio playlists\n Digite opcao: ");
				setbuf(stdin,NULL);
				op = ler_opcao_segura();

				switch(op){
					case 1:

						// verifica se o acervo foi carregado
						if(acervo->lista != NULL){

							// pede o nome do arquivo e envia com acervo para funcao que cria o relatorio
							printf("\nDigite nome do arquivo para salvar o relatorio: ");
							setbuf(stdin,NULL);
							scanf("%[^\n]s",tempc);

							relatorio_acervo(acervo, tempc);
						}
						else printf("\nAcervo vazio, carregue para utilizar funcao!!!\n");
						break;
					case 2:

						// recolhe o nome do arquivo a ser salvo e envia para funcao que faz a sua escrita
						printf("\nDigite nome do arquivo para salvar o relatorio: ");
						setbuf(stdin,NULL);
						scanf("%[^\n]s",tempc);

						relatorio_playlists(playlist_usuario, playlist_aleatoria, tempc);
						break;
					default:
						op=99;
						printf("\nOPCAO INVALIDA!!!\n");
						break;
				}

				break;
			case 6:

				// verifica se o acervo foi carregado e envia ele e o nome pedido ao usuario para a funcao re realiza a escrita do arquivo com execucoes
				if(acervo->lista != NULL){
					printf("\nDigite nome do arquivo: ");
					setbuf(stdin,NULL);
					scanf("%[^\n]s", tempc);
					backup(acervo, tempc);
				}
				else printf("\nAcervo nao foi carregado!");

				break;
			case 7:
				if(acervo->lista == NULL){
					printf("\nDigite nome do arquivo: ");
					setbuf(stdin,NULL);
					scanf("%[^\n]s", tempc);
					ler_backup(acervo, tempc);
				}
				else printf("\nAcervo já carregado!");
				break;
			case 0:
				printf("\n\nSaindo...\n");
				break;
			default:
				printf("\n\nOPCAO INVALIDA!!!\n");
				break;
		}
	}

	return 0;
}
