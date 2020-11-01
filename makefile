CFLAGS=-Wall -Werror -Wconversion -std=c99 -g -O0
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
OUTPUT=lista_se

all: lista_se valgrind

lista_se: lista.c pruebas.c
	gcc *.c $(CFLAGS) -o $(OUTPUT)

valgrind: lista_se
	valgrind $(VFLAGS) ./$(OUTPUT)

debug: lista_se
	gdb -tui $(OUTPUT)
