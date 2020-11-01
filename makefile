CFLAGS=-g -Wall -Werror -Wconversion -Wtype-limits -pedantic -std=c99 -O0
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
OUTPUT=lista_se

all: lista_se valgrind

lista_se: lista.c pruebas.c
	gcc *.c $(CFLAGS) -o $(OUTPUT)

valgrind: lista_se
	valgrind $(VFLAGS) ./$(OUTPUT)

debug: lista_se
	gdb -tui $(OUTPUT)
