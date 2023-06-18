nomePrograma=main

objs=main.o setaMapa.o analisaTabuleiro.o progride.o operadores.o

CFLAGS := -Wall -std=c99 -lm

all: $(nomePrograma)

$(nomePrograma): $(objs)
	gcc -o $(nomePrograma) $(objs) $(CFLAGS)

setaMapa.o: setaMapa.c
	gcc -c setaMapa.c $(CFLAGS)

analisaTabuleiro.o: analisaTabuleiro.c
	gcc -c analisaTabuleiro.c $(CFLAGS)

progride.o: progride.c
	gcc -c progride.c $(CFLAGS)

operadores.o: operadores.c
	gcc -c operadores.c $(CFLAGS)


clean:
	rm -f $(objs) *~

purge: clean
	-rm -f $(nomePrograma)

