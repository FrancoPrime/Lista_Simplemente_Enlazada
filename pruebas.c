#include <stdio.h>
#include "lista.h"
#include "pa2mm.h"
#define EXITO 0
#define ERROR -1

void prueba_crear_lista(){
  lista_t* lista = lista_crear();
  pa2m_afirmar(lista != NULL, "Crear una lista");
  lista_destruir(lista);
}

void prueba_insertar_elementos(){
  lista_t* lista = lista_crear();
  lista_insertar(lista, (void*)2);
  int resultado = lista_insertar(lista, (void*)4);
  pa2m_afirmar(resultado == EXITO, "Insertar elementos");
  pa2m_afirmar(lista_elementos(lista) == 2, "Contador de elementos");
  lista_destruir(lista);
}

int main(){
  pa2m_nuevo_grupo("Creación de lista e inserción");
  prueba_crear_lista();
  prueba_insertar_elementos();
  return 0;
}
