#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musica.h"
#include "lse.h"
#include "fila.h"
#include "pilha.h"
#include "spotyfom.h"

int main(){

	struct desc* descritor = CriaLista();

	ler_arquivo(descritor);

	Imprime_Lista(descritor);

	return 0;
}

