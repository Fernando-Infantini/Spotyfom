comp:
	gcc codigos/lista.c -c -g -Iheaders
	gcc codigos/fila.c -c -g -Iheaders
	gcc codigos/pilha.c -c -g -Iheaders
	gcc codigos/spotyfom.c -c -g -Iheaders
	gcc main.c -o spotyfom spotyfom.o lista.o pilha.o fila.o -g -Iheaders

clean:
	rm lista.o
	rm fila.o
	rm pilha.o
	rm spotyfom.o
