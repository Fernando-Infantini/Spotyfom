comp:
	gcc lse.c -c -g
	gcc fila.c -c -g
	gcc pilha.c -c -g
	gcc spotyfom.c -c -g
	gcc main.c -o spotyfom spotyfom.o lse.o pilha.o fila.o -g

clean:
	rm lse.o
	rm fila.o
	rm pilha.o
	rm spotyfom.o
