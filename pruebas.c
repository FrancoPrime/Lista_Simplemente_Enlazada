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

void prueba_insertar_elementos_secuencia(){
  lista_t* lista = lista_crear();
  for(size_t i=0;i<10;i++)
  {
    lista_insertar(lista, (void*)i);
  }
  int resultado = lista_insertar(lista, (void*)4);
  pa2m_afirmar(resultado == EXITO && lista_elementos(lista) == 11, "Insertar nodos secuenciales");
  void* elemento = lista_elemento_en_posicion(lista, 3);
  pa2m_afirmar(elemento == (void*)3, "Los elementos son correctos al añadir secuencialmente");
  lista_destruir(lista);
}

void prueba_insertar_elementos_aleatorio(){
  lista_t* lista = lista_crear();
  for(size_t i=0;i<10;i++)
  {
    lista_insertar(lista, (void*)i);
  }
  int resultado = lista_insertar_en_posicion(lista, (void*)99, 3);
  pa2m_afirmar(resultado == EXITO && lista_elementos(lista) == 11, "Insertar nodo aleatorio");
  void* elemento = lista_elemento_en_posicion(lista, 3);
  pa2m_afirmar(elemento == (void*)99, "Los elementos son correctos al añadir aleatoriamente");
  lista_destruir(lista);
}

int main(){
  pa2m_nuevo_grupo("Creación de lista");
  prueba_crear_lista();
  pa2m_nuevo_grupo("Inserción secuencial y aleatoria");
  prueba_insertar_elementos_secuencia();
  prueba_insertar_elementos_aleatorio();
  return 0;
}
